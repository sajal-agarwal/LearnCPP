#pragma once
#include <iostream>


template<typename T, size_t...I, typename...Args>
T& print_tpl(T& strm, std::index_sequence<I...>, const std::tuple<Args...>& x)
{
    return ((strm << ((I == 0) ? "" : ", ") << std::get<I>(x)), ...);
}

template<typename...Args>
auto& operator<<(auto&& strm, const std::tuple<Args...>& x)
{
    print_tpl(std::forward<decltype(strm)>(strm),
        std::make_index_sequence<std::tuple_size_v<std::tuple<Args...>>>(),
        x);
    return strm;
}

int main()
{
    std::cout << std::make_tuple(136, "C++", 3.1415) << '\n';
}