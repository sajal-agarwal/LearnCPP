#pragma once

#include<iostream>
#include <vector>
#include<type_traits>
#include<algorithm>

template<typename I, typename...T>
std::enable_if_t<std::is_constructible_v<I, size_t> && std::conjunction_v<std::is_constructible<T, size_t>...>, bool>
removeElements(std::vector<int> &v, size_t offset, I index, T... indexes) {
    auto actualIndex = index - offset;
    if (actualIndex < 0 || actualIndex >= v.size()) return false;
    v.erase(v.begin() + actualIndex);
    if (!removeElements(v, ++offset, indexes...)) return false;
    return true;
}

bool removeElements(std::vector<int> v, size_t offset) {
    return true;
}

/*
* Another way to achieve same behavior using fold expression
*/
template<typename...T>
std::enable_if_t<(std::is_integral_v<T> &&...), bool> removeElements(std::vector<int>& v, T...t) {
    size_t offset = 0, pos = 0;
    return ((pos = t - offset++, (pos < v.size()) && v.erase(v.begin() + pos) <= v.end()) &&...);
}

int main() {
    //Remove at gives indexes
    std::vector<int> v{ 1, 2, 3, 4, 5, 6, 7, 8 };
    if (!removeElements(v, 0, 1, 2, 5, 9))
        puts("Failed to remove some of the elements!");

    //Remove based on callback
    v.erase(std::remove_if(v.begin(), v.end(),
        [](const int &elem) { return (elem == 0); })
        , v.end());
    
    return 0;
}
