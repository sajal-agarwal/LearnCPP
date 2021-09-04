#pragma once

#include <iostream>

class Test {
public:
    Test()
    {
        std::cout << "Constructed!\n";
    }

    Test(const Test& o)
    {
        std::cout << "Copied!\n";
    }

    Test(Test&& o) noexcept
    {
        std::cout << "Moved!";
    }

    ~Test()
    {
        std::cout << "Destructed!\n";
    }

    int foo() { return 1; }
};


int main() {
    /*
    * Below call does not create any Test object
    * nor it invokes the foo() method. It is purely
    * compile time thing for compiler to deduce the
    * type for 'ot'.
    */
    decltype(std::declval<Test>().foo()) ot;

#if 0 // For above reason below code is not valid
    Test ot2(std::declval<Test>());

    ot2.foo();
#endif
}
