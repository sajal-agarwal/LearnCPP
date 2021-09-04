#pragma once
#include <iostream>


class X
{
public:
    X() = default;

    X(const X&)
    {
        std::cout << "COPY\n";
    }

    X(X&&) noexcept
    {
        std::cout << "MOVE\n";
    }

    X& operator=(const X& x)
    {
        std::cout << "COPY ASSIGNMENT\n";
        return *this;
    }

    X& operator=(X&&) noexcept
    {
        std::cout << "MOVE ASSIGNMENT\n";
        return *this;
    }
};

struct Test
{
    X m_x;

    void foo(X& x)
    {
        m_x = std::forward<X&>(x);
    }

    void foo(X&& x)
    {
        m_x = std::forward<X&&>(x);
    }
};

int main()
{
    X x1;
    Test t;
    t.foo(x1); // COPY
    t.foo(X{}); // MOVE
    /*
    * Why??
    * Unlike std::move std::forward have variations one
    * which accepts references and other which accepts
    * rvalue references and the return type of both the
    * fuctions is same Ty&& but in case Ty is reference
    * let sat T& and in other case Ty is rvalue reference
    * let say T&& so in first case Ty&& becomes T& &&
    * which collapes to T& and in other case Ty&& becomes
    * T&& && which collapes to T&& and hence the version
    * of forward which is invoked for reference value
    * returns a referece and the version of forward which
    * accepts a rvalue reference returns a rvalue reference.
    * This phenomenon is used to achieve perfect forwarding
    * using templates. Below is the list of collapsing rules:
    * X & & collapses to X &
    * X & && collapses to X &
    * X && & collapses to X &
    * X && && collapses to X &&
    */
}
