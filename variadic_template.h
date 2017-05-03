#include<iostream>
#include<string>
#include <functional>

template<typename... Args>
void foo(Args... args){

}

int sqrt_int(int x) {
    return x*x;
}

template<typename... Args>
void func(Args... args){
    auto noOfParam = sizeof...(Args);
#if 1
    std::cout <<noOfParam << std::endl;
    foo(++args...);

    //{std::cout << args ;}... ;
#endif
#if 1

    int parmaArr[noOfParam] = {args...};

    std::cout << "Parameters:" << std::endl;
    for (int i = 0; i < noOfParam; i++)
        std::cout << parmaArr[i] << std::endl;
#endif
}

template<typename... Args>
void callAnyFunc(void(*f)(Args...), Args...args) {
    if (nullptr != f) {
        f(args...);
    }
}

template<typename _Fn, typename... Args>
auto callAnyFunc2(_Fn&& f, Args&&... args) {
    if (nullptr != f) {
        return f(args...);
    }
#if 0
    // below line give error if this function is called more then once with different parameter
    return 0; //error: inconsistent deduction for auto return type: 'double' and then 'int'
#endif
}


#if 0
#include<variadic_template.h>

int main () {
    callAnyFunc2(std::move(sqrt_int), 4);
    std::cout << callAnyFunc2([](double x) { return x*x;}, 4.3) << std::endl;
    int(*fp)(int);
    fp = nullptr;
    std::cout << callAnyFunc2(fp, 4.3);
}
#endif
