#pragma once

#include<iostream>

//Lambda combiner with move
template<typename... B>
struct LambdaCombiner : B... {
public:
    LambdaCombiner(B... b) : B(std::move(b))... {}

    using B::operator()...;
};

//Lambda combiner with perfact forwarding
template<typename... B>
class LambdaMerger : B... {
public:
    template<typename... T>
    LambdaMerger(T&&... t) : B(std::forward<T>(t))...{}

    using B::operator()...;
};

//Explicit class template arguments type detection guide
template<typename... T>
LambdaMerger(T...)->LambdaMerger<std::decay_t<T>...>;

template<typename... B>
LambdaMerger<B...> make_lambda_merger(B&&... b) {
    return LambdaMerger<B...>(std::forward<B>(b)...);
}

int main() {
    auto l1 = [] { return 5; };
    auto l2 = [](int x) { return 3 * x; };
    LambdaCombiner lc(l1, l2, [](int a, int b) { return a + b; });
    std::cout << "Result of lc(): " << lc() << '\n';
    std::cout << "Result of lc(2): " << lc(2) << '\n';
    std::cout << "Result of lc(2, 5): " << lc(2, 5) << '\n';

    const auto l3 = [] { return 5; };
    const auto l4 = [](int x) { return 3 * x; };
    LambdaMerger lm(l3, l4, [](int a, int b) { return a + b; });
    std::cout << "Result of lm(): " << lm() << '\n';
    std::cout << "Result of lm(2): " << lm(2) << '\n';
    std::cout << "Result of lm(2, 5): " << lm(2, 5) << '\n';
}
