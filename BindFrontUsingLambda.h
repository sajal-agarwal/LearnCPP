#pragma once
#include<iostream>


template<typename Func, typename ...Args>
auto bindFront(Func &&func, Args&&...args) {
    /* Type shoudl not be specified in lambdda capture
       func in 'func = std::forward<Func>(func)' and
       args in '...args = std::forward<Args>(args)'
       can be named anything, just imagin a type before
       there names and below will make sense
    */
    return [func = std::forward<Func>(func), ...args = std::forward<Args>(args)](auto&& ...params) {
        return func(args..., std::forward<decltype(params)>(params)...);
    };
}

int add(const int a, const int b, const int c) {
    return (a + b + c);
}

int main() {
    std::cout << bindFront(add, 2, 3)(6) << '\n';
}
