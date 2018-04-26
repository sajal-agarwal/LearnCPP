#pragma once

#include <iostream>
#include <array>
#include <unordered_map>
#include <map>

#if 0
namespace std {
    template<>
    struct hash<std::pair<size_t, int>> {
        size_t operator()(const std::pair<size_t, int>& key) const
        {
            return (std::hash<size_t>()(key.first) + std::hash<int>()(key.second));
        }
    };
}
#endif // 0

//Below is the more generalized specialization to support std::pair<> of any genric types
namespace std {
    template<typename T1, typename T2>
    struct hash<std::pair<T1, T2>> {
        size_t operator()(const std::pair<size_t, int>& key) const
        {
            return (std::hash<T1>()(key.first) ^ std::hash<T2>()(key.second));
        }
    };
}

template<size_t N>
size_t dp_numOfSetsWithEqualSum(std::array<unsigned, N> &arr, size_t sum, int index, std::unordered_map<std::pair<size_t, int>, size_t> &t) {
    auto it = t.find(std::make_pair(sum, index));
    if (it != t.end()) {
        std::cout << "sum = " << sum << " index = " << index << '\n';
        return it->second;
    }

    if (0 == sum)
        return 1;

    if (0 > sum)
        return 0;

    if ((N - 1) < index)
        return 0;

    size_t count = 0;

    if (arr[index] > sum)
        count = dp_numOfSetsWithEqualSum(arr, sum, index + 1, t);
    else
        count = (dp_numOfSetsWithEqualSum(arr, sum - arr[index], index + 1, t) + dp_numOfSetsWithEqualSum(arr, sum, index + 1, t));

    t[std::make_pair(sum, index)] = count;

    return count;
}

template<size_t N>
size_t dp_numOfSetsWithEqualSum(std::array<unsigned, N> &arr, size_t sum, int index, std::map<std::pair<size_t, int>, size_t> &t) {
    auto it = t.find(std::make_pair(sum, index));
    if (it != t.end()) {
        std::cout << "sum = " << sum << " index = " << index << '\n';
        return it->second;
    }


    if (0 == sum)
        return 1;

    if (0 > sum)
        return 0;

    if ((N - 1) < index)
        return 0;

    size_t count = 0;

    if (arr[index] > sum)
        count = dp_numOfSetsWithEqualSum(arr, sum, index + 1, t);
    else
        count = (dp_numOfSetsWithEqualSum(arr, sum - arr[index], index + 1, t) + dp_numOfSetsWithEqualSum(arr, sum, index + 1, t));

    t[std::make_pair(sum, index)] = count;

    return count;
}

template<size_t N>
size_t rec_numOfSetsWithEqualSum(std::array<unsigned, N> &arr, size_t sum, int index) {
    std::cout << "sum = " << sum << " index = " << index << '\n';

    if (0 == sum) return 1;

    if (0 > sum) return 0;

    if (index > (N - 1)) return 0;

    if (arr[index] > sum)
        return rec_numOfSetsWithEqualSum(arr, sum, index + 1);
    else
        return (rec_numOfSetsWithEqualSum(arr, sum - arr[index], index + 1)
            + rec_numOfSetsWithEqualSum(arr, sum, index + 1));
}


template<size_t N>
size_t numOfSetsWithEqualSum(std::array<unsigned, N> arr, size_t sum) {
    std::unordered_map<std::pair<size_t, int>, size_t> t;
    auto count = dp_numOfSetsWithEqualSum(arr, sum, 0, t);
    return count;
}

int main() {
    std::hash<std::string> h;
    std::array<unsigned, 20> arr{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 };
    std::cout << "----------------------------------------\n"
        "Number of sets with equal sum = " << numOfSetsWithEqualSum(arr, 16) << std::endl;
}
