#pragma once

#include <string>
#include <vector>
#include <map>
#include <memory>

enum TokenKind
{
    Integer,
    Word,
    LBracket,
    RBracket,
    LParen,
    RParen,
    Comma,
    Colon,
    Eof,
};

struct Token
{
    TokenKind kind;
    int int_val;
    std::string string_val;

    Token(TokenKind kind, int val);
    Token(TokenKind kind, std::string val);
};

class Lexer
{
    std::string all;
    size_t index;

public:
    Lexer(std::string const &all);

    class Exception : public std::exception
    {
        char ch;
        std::string msg;

    public:
        Exception(char ch);
        virtual char const *what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override;
    };

    Token lex();

    std::vector<Token> lex_all();
};

struct File
{
    struct Object;

    struct Value
    {
        enum class Kind
        {
            Integer,
            Object
        };

        Kind kind;
        int int_val;
        std::unique_ptr<File::Object> object_val;
    };

    struct Object
    {
        std::string name;
        std::vector<Value> params;
    };

    struct Property
    {
        std::string name;
        int value;
    };

    struct Part
    {
        std::string title;
        std::vector<Object> objects;
        std::map<std::string, int> properties;
    };

    std::vector<Part> parts;
};

class Parser
{
    std::vector<Token> tokens;
    int index;

public:
    Parser(std::vector<Token> const &tokens);

    bool parse_value(File::Value &value);
    bool parse_object(File::Object &obj);
    bool parse_property(File::Property &prop);
    bool parse_line(File::Part &current_part);
    bool parse_part(File::Part &part);
    bool parse_file(File &file);
};