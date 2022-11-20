#include "level_parser.hpp"

#include <sstream>

Token::Token(TokenKind kind, int val) : kind{kind}, int_val{val} {}

Token::Token(TokenKind kind, std::string val) : kind{kind}, string_val{val} {}

Lexer::Lexer(std::string const &all) : all{all}, index{0} {}

Lexer::Exception::Exception(char ch) : ch{ch}, msg{}
{
    std::stringstream ss{};
    ss << "Unexpected character '" << ch << "'.";
    msg = ss.str();
}

char const *Lexer::Exception::what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW
{
    return msg.data();
}

Token Lexer::lex()
{
    if (index >= all.length())
    {
        return {TokenKind::Eof, 0};
    }
    char c = all[index++];
    switch (c)
    {
    case ' ':
    case '\n':
    case '\t':
    case '\r':
        return lex();
    case '[':
        return {TokenKind::LBracket, 0};
    case ']':
        return {TokenKind::RBracket, 0};
    case '(':
        return {TokenKind::LParen, 0};
    case ')':
        return {TokenKind::RParen, 0};
    case ',':
        return {TokenKind::Comma, 0};
    case ':':
        return {TokenKind::Colon, 0};
    default:
        break;
    }
    auto int_test = [](char c)
    { return c >= '0' && c <= '9'; };
    if (int_test(c))
    {
        std::string buffer{};
        buffer += c;
        while (index + 1 < all.length() && int_test(all[index]))
        {
            buffer += all[index++];
        }
        return {TokenKind::Integer, std::stoi(buffer)};
    }
    auto ident_test = [](char c)
    { return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'); };
    if (ident_test(c))
    {
        std::string buffer{};
        buffer += c;
        while (index + 1 < all.length() && ident_test(all[index]))
        {
            buffer += all[index++];
        }
        return {TokenKind::Word, std::move(buffer)};
    }
    throw Exception(c);
}

std::vector<Token> Lexer::lex_all()
{
    std::vector<Token> tokens{};
    while (true)
    {
        Token tok = lex();
        tokens.push_back(tok);
        if (tok.kind == TokenKind::Eof)
        {
            return tokens;
        }
    }
}

Parser::Parser(std::vector<Token> const &tokens) : tokens{tokens}, index{0} {}

bool Parser::parse_value(File::Value &value)
{
    int start = index;
    if (tokens[index].kind == TokenKind::Integer)
    {
        value.kind = File::Value::Kind::Integer;
        value.int_val = tokens[index++].int_val;
        return true;
    }
    else if (tokens[index].kind == TokenKind::LBracket)
    {
        index++;
        std::vector<File::Value> values{};
        while (tokens[index].kind != TokenKind::RBracket)
        {
            File::Value value;
            if (!parse_value(value))
            {
                index = start;
                return false;
            }
            values.push_back(std::move(value));
            if (tokens[index].kind == TokenKind::Comma)
            {
                index++;
            }
        }
        index++;
        value.kind = File::Value::Kind::List;
        value.list_val = std::move(values);
        return true;
    }
    else
    {
        File::Object obj;
        if (parse_object(obj))
        {
            value.kind = File::Value::Kind::Object;
            value.object_val = std::make_unique<File::Object>(std::move(obj));
            return true;
        }
    }
    return false;
}

bool Parser::parse_object(File::Object &obj)
{
    std::string name;
    std::vector<File::Value> params;
    int start = index;
    if (tokens[index].kind != TokenKind::Word)
    {
        index = start;
        return false;
    }
    name = tokens[index++].string_val;
    if (tokens[index++].kind != TokenKind::LParen)
    {
        index = start;
        return false;
    }
    while (tokens[index].kind != TokenKind::RParen)
    {
        File::Value value;
        if (!parse_value(value))
        {
            index = start;
            return false;
        }
        params.push_back(std::move(value));
        if (tokens[index].kind == TokenKind::Comma)
        {
            index++;
        }
    }
    index++;
    obj.name = std::move(name);
    obj.params = std::move(params);
    return true;
}

bool Parser::parse_property(File::Property &prop)
{
    std::string name;
    File::Value val;
    int start = index;
    if (tokens[index].kind != TokenKind::Word)
    {
        index = start;
        return false;
    }
    name = tokens[index++].string_val;
    if (tokens[index++].kind != TokenKind::Colon)
    {
        index = start;
        return false;
    }
    if (!parse_value(val))
    {
        index = start;
        return false;
    }
    prop.name = std::move(name);
    prop.value = std::move(val);
    return true;
}

bool Parser::parse_line(File::Part &current_part)
{
    File::Object obj;
    if (parse_object(obj))
    {
        current_part.objects.push_back(std::move(obj));
        return true;
    }
    File::Property prop;
    if (parse_property(prop))
    {
        current_part.properties.emplace(prop.name, std::move(prop.value));
        return true;
    }
    return false;
}

bool Parser::parse_part(File::Part &part)
{
    int start = index;
    if (tokens[index++].kind != TokenKind::LBracket)
    {
        index = start;
        return false;
    }
    if (tokens[index].kind != TokenKind::Word)
    {
        index = start;
        return false;
    }
    part.title = tokens[index++].string_val;
    if (tokens[index++].kind != TokenKind::RBracket)
    {
        index = start;
        return false;
    }

    while (parse_line(part))
    {
    }
    return true;
}

bool Parser::parse_file(File &file)
{
    File::Part part;
    while (parse_part(part))
    {
        file.parts.push_back(std::move(part));
    }
    return tokens[index].kind == TokenKind::Eof;
}