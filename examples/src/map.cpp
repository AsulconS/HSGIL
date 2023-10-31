#include <HSGIL/system/dstr/map.hpp>

#include <iostream>

template <typename T>
void value(T&)
{
    std::cout << "lvalue" << std::endl;
}

template <typename T>
void value(T&&)
{
    std::cout << "rvalue" << std::endl;
}

template <typename T>
void foo(T&& arg)
{
    value(gil::hsgil_forward<T>(arg));
}

int main()
{
    int x;
    foo(x);
    foo(std::move(x));
    foo(gil::hsgil_move(x));
    foo(4);

    return 0;
}
