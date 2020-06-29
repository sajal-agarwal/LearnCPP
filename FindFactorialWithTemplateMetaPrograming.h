#pragma once
#include<iostream>

/* Factorial with template meta programin
*/
template<size_t N>
struct Factorial {
    const static size_t value = N * Factorial<N - 1>::value;
};

template<>
struct Factorial<0> {
    const static size_t value = 1;
};

/* Factorial with variable template
*/
template<size_t N>
size_t factorial = N * factorial<N - 1>;

template<>
size_t factorial<0> = 1;


int main() {
    std::cout << "Factorial of 5 is " << Factorial<5>::value << '\n';
    std::cout << "Factorial of 5 is " << factorial<5> << '\n';
}
