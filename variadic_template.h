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
    constexpr size_t noOfParam = sizeof...(Args);   //auto does not work here in vs2015
    std::cout << "No of args: "<<noOfParam << std::endl;

    std::cout << "Args before incr:\n";

    using expander = int[];

    expander{0, (std::cout << args << ' ', 0)...};

    foo(++args...);

    std::cout << "\n\nArgs after incr:\n";

    int parmaArr[noOfParam] = {args...};
    for (int i = 0; i < noOfParam; i++)
        std::cout << parmaArr[i] << ' ';
}

template<typename... Args>
void callAnyFunc(void(*f)(Args...), Args...args) {
    if (nullptr != f) {     //this fails to compile in vs2015
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

int main () {
#if 0    //This fails to compile in vs2015
    callAnyFunc2(std::move(sqrt_int), 4);
    std::cout << callAnyFunc2([](double x) { return x*x; }, 4.3) << std::endl;
    int(*fp)(int);
    fp = nullptr;
    std::cout << callAnyFunc2(fp, 4.3);
#endif
    func(3, 29, 45);
}
