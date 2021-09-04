#pragma once
#include <iostream>


template<size_t N>
struct PrintTuple
{
    template<typename T>
    PrintTuple(T&& t)
    {
        PrintTuple<N - 1>{ std::forward<T>(t) };
        std::cout << (N > 1 ? ", " : "") << std::get<N - 1>(t) << ' ';
    }
};

template<>
struct PrintTuple <0>
{
    template<typename T>
    PrintTuple([[maybe_unused]] T&& t)
    {
    }
};

template<typename T>
void printTuple(T&& t)
{
    PrintTuple<std::tuple_size_v<T>>{ std::forward<T>(t) };
}

/*
* Another implementation using just the struct
* with templatized constructor
*/
struct Print_Tuple
{
    template<typename T>
    Print_Tuple(T&& t)
    {
        print(std::forward<T>(t));
    }

    template<typename T, size_t N = std::tuple_size_v<T>>
    void print(T&& t)
    {
        if constexpr (N > 0)
        {
            print<T, N - 1>(std::forward<T>(t));
            std::cout << (N > 1 ? ", " : "") << std::get<N - 1>(t) << ' ';
        }
    }
};


int main()
{
    printTuple(std::make_tuple(12, 4.5, "C++"));
}

