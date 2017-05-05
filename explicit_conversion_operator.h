#include <string>

class Test
{
public:
    Test() {}

    explicit Test(int n) {}

    operator int() {
        return 100;
    }

    explicit operator std::string () {
        return "explicit";
    }
};


int main () {
    Test ot { 9 };

    int i = ot;
#if 0
    std::string str = ot; //error: conversion from 'Test' to non-scalar type 'std::__cxx11::string {aka std::__cxx11::basic_string<char>}' requested
#endif
    std::string exstr = static_cast<std::string>(ot);
}
