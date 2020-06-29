#pragma once
#include<tuple>
#include<iostream>


template<size_t I, typename Tuple>
struct PrintTuple {
    static void print(const Tuple &t) {
        PrintTuple<I - 1, Tuple>::print(t);
        std::cout << std::get<I>(t) << ' ';
    }
};

template<typename Tuple>
struct PrintTuple<0, Tuple> { 
    static void print(const Tuple& t) {
        std::cout << std::get<0>(t) << ' ';
    }
};

template<typename ... Args>
void printTuple(const std::tuple<Args...> &t) {
    PrintTuple<sizeof...(Args) - 1, std::tuple<Args...>>::print(t);
}

int main() {
    printTuple(std::make_tuple(2, 3.1415, "C++17"));
}