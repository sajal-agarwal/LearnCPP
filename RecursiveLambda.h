#pragma once
#include<iostream>


int fib(const int n) {
    auto _fib = [](auto _fib, const int n) {
        if (n < 2)
            return 1;

        return _fib(_fib, n - 1) + _fib(_fib, n - 2);
    };

    return _fib(_fib, 5);
}

int main() {
    std::cout << fib(5);
}
