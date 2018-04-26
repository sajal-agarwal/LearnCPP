#pragma once

#include <iostream>

class Test {
public:
    Test() {}
    Test(const Test& o) {}
    Test(Test&& o) {}
    ~Test() {}

    int foo() { return 1; }
};


int main() {
    decltype(std::declval<Test>().foo()) ot;

    //Test ot2(std::declval<Test>());

    //ot2.foo();
}
