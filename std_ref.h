#pragma once
#include <functional>
#include <iostream>

void f(int& n1, int& n2, const int& n3)
{
    std::cout << "In function: " << n1 << ' ' << n2 << ' ' << n3 << '\n';
    ++n1; // increments the copy of n1 stored in the function object
    ++n2; // increments the main()'s n2
          // ++n3; // compile error
}


void f2(int &x) {
    x = 6;
}

#if 1
void f2(int x) {
    x = 7;
}
#endif // 0


void f3(int &x) {
    ((void(*)(int))(&f2))(x);
}

template <typename ...Args>
void foo(Args&& ...val) {
    //f2(std::forward<std::decay<Args...>::type>(val...));
    f2(std::forward<std::decay<Args>::type>(val)...);
}

int main()
{
    int x = 8;
    foo(x);
    std::cout << x << '\n';
    //foo(7);
#if 1
    int n1 = 1, n2 = 2, n3 = 3;
    std::function<void()> bound_f = std::bind(f, n1, std::ref(n2), std::cref(n3));
    n1 = 10;
    n2 = 11;
    n3 = 12;
    std::cout << "Before function: " << n1 << ' ' << n2 << ' ' << n3 << '\n';
    bound_f();
    std::cout << "After function: " << n1 << ' ' << n2 << ' ' << n3 << '\n';
#endif // 0

}
