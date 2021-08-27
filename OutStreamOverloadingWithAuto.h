#pragma once
#include <iostream>
#include <sstream>

/*
* Here by defining 'operator<<' with auto we made
* it a generic method which works with all the
* streams - output stream, string stream, etc.
*/
class Test
{
    double m_data{ 3.1415 };
public:
    friend auto& operator<<(auto& os, const Test& t)
    {
        os << t.m_data;
        return os;
    }
};

int main()
{
    std::cout << Test{} << '\n';

    std::stringstream ss;
    ss << Test{};
    std::cout << ss.str() << '\n';
}