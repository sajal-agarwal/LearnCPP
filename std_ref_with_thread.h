#pragma once
#include <iostream>
#include <string>
#include <thread>
#include <chrono>

void do_something(std::string &str)
{
    std::this_thread::sleep_for(std::chrono::seconds{ 1 }); // doing something
    str = "This is the output message from the function.";
}

template<typename T>
std::enable_if_t<std::is_same_v<std::decay_t<T>, std::string>> do_some(T&& str)
{
    std::string localStr = std::forward<T>(str);
    std::cout << "str = " << str << '\n';
}

struct Arg
{
    int i = 1;
    int  get()&& { return i; } // call to this overload is rvalue
    int& get()& { return i; } // call to this overload is lvalue
};

int main()
{
    std::string str{ "Function execution in progress..." };
    std::thread t1{ do_something, std::ref(str) }; // here not using std::ref will
                                                   // will result in error
    std::cout << str << '\n';
    t1.join();
    std::cout << str << '\n';

    //--------------------------------------------------------------------
    do_some(std::string{"test"});
    const auto str1 = std::forward<std::string&>(str); // this will not move as std::string & && -> std::string &
    const auto str2 = std::forward<const std::string&>(str1); // thiw will not move as const std::string & &&
                                                              // -> const std::string & same is tru for below
    auto str3 = std::forward<std::string>(str); // this will move as retutn type is std::string &&
    auto str4 = std::forward<std::string>(std::string{"XiX"}); // this will move as retutn type
                                                               // is std::string && && -> std::string &&
                                                               // these are colapsing rules
    do_some(str);
    std::cout << str << '\n';
}
