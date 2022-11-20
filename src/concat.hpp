#pragma once
#include <string>
#include <sstream>

template <typename ...T>
inline std::string concat(T... args)
{
    std::stringstream ss{};
    ((ss << args),...);
    return ss.str();
}
