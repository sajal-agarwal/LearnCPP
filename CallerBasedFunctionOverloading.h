#pragma once
#include <iostream>


class Demo
{
    int i{ 9 };
public:
    ~Demo()
    {
        i = -1;
    }

    int& get() &
    {
        return i;
    }

    int get() &&
    {
        return i;
    }

    int& get_i()
    {
        return i;
    }
};

int main()
{
    Demo d{};
    d.get_i() = 4; // ok: will update 'i' to 4
    d.get() = 5; // ok: will call ref version of get()  and update 'i' to 5

    int& x_tmp_ref = Demo{}.get_i();
    x_tmp_ref = 7; // not ok: we don't get an error and even program run
                   // fine but this is dangling reference as the temporary
                   // object is delete at this line. To avoid these kinds
                   // of calls we can make sure that this function only
                   // gets called from a lvalue type object not rvalue
                   // to do that we can have get() fuction like overloads.

    int x = Demo{}.get(); // ok: will call the rvalue ref version of get()
                          // as being called from rvalue type object
}