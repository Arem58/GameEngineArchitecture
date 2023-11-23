#pragma once
#include <iostream>
// Un macro para el compilador que imprime la variable y su valor
#define vprint(var) print(#var ":", var)

inline void print()
{
    std::cout << std::endl;
}

inline void print(auto value, bool isLast = true)
{
    std::cout << value;
    if (isLast)
    {
        std::cout << std::endl;
    }
}

inline void print(auto first, auto... args)
{
    print(first, false);
    if constexpr (sizeof...(args) > 0)
    {
        std::cout << ' ';
        print(args...);
    }
    else
    {
        std::cout << std::endl;
    }
}