#pragma once

#include <iostream>
#include <type_traits>

auto sum2(int a1, int a2) {
    std::cout << "a1 = " << a1 << '\n';
    std::cout << "a2 = " << a2 << '\n';

    int sum = 0;
    if (a1 > a2)
        sum = a1 + a2 + 1;
    else
        sum = a1 + a2;

    return sum;
}

int main() {

    auto print = [](auto &&val) mutable {
        if (std::is_same<std::decay<decltype(val)>::type, float>::value) {
            std::cout << "It's a float!" << " || value : " << val << '\n';
        }
        else std::cout << "type name : " << typeid(val).name() << " || value : " << val << '\n';
    };

    float f = 8.9f;
    print(2);
    print("Hello");
    print(f);

    std::cout << "Sum = " << sum2(3, 8) << '\n';

    auto sum_lambda = [](auto &&a, auto &&b) { return a + b; };

    std::cout << "Lambda Sum = " << sum_lambda(2, 4.6f) << '\n';
}
