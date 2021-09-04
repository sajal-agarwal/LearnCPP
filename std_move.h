#pragma once
#include <iostream>
#include <string>

/*
* std::move does not move anything
* it only return a rvalue reference of
* the object which is passed to it.
*/
struct X
{
    std::string m_str;

    void foo(std::string&& str)
    {
        m_str = str; // this does not move, below does
        m_str = std::move(str); // std::forwad is better here
    }
};

int main()
{
    std::string str1{ "test string" };
#if 0 // error: str1 is not rvalue
    foo(str1);
#endif
    X x;
    x.foo(std::move(str1));
    /*
    * Above works as std::move returns rvalue reference
    * but will it move str1 to x.m_str, NO. Why??
    * You see the return type of std::move made sure that
    * the X::foo gets called but inside the function X::foo
    * str is a named parameter and lvalue not rvalue so
    * at the first line of the function when we made the
    * assignment the std::string::operator=(const string&)
    * is called not the move assignment.
    * So we wish to move str1 to x.m_str we need to use
    * std::move (or better forward) here that will ensure
    * that move assignment operator get called. [check out
    * next line]
    * std::move can only move things if it is followed by
    * a move assignment or copy constructor and if your
    * class does not have any of those then this will result
    * in copy assignment or construction
    * std::move always returns a rvalue reference weather
    * we pass a rvalue or a lvalue same is not true for
    * forward.
    */
}
