#pragma once
#include<iostream>
#include<algorithm>
#include<array>

#if 0
template<size_t N1, size_t N2>
void rec_lenOfLargestCommonSubString(std::array<char, N1> &s1,
    std::array<char, N2> &s2,
    size_t &maxLen,
    size_t i1 = 0,
    size_t i2 = 0,
    size_t len = 0) {
    if (len > maxLen) maxLen = len;

    if (i1 == N1 || i2 == N2) return;

    if (s1[i1] == s2[i2])
        rec_lenOfLargestCommonSubString(s1, s2, maxLen, i1 + 1, i2 + 1, len + 1);
    else {
        rec_lenOfLargestCommonSubString(s1, s2, maxLen, i1, i2 + 1, 0);
        rec_lenOfLargestCommonSubString(s1, s2, maxLen, i1 + 1, i2, 0);
    }
}
#endif // 0


template<size_t N1, size_t N2>
size_t rec_lenOfLargestCommonSubString(std::array<char, N1> &s1,
    std::array<char, N2> &s2,
    size_t i1 = 0,
    size_t i2 = 0,
    size_t len = 0) {
    if (i1 == N1 || i2 == N2) return len;

    if (s1[i1] == s2[i2])
        return rec_lenOfLargestCommonSubString(s1, s2, i1 + 1, i2 + 1, len + 1);

    return std::max({ rec_lenOfLargestCommonSubString(s1, s2, i1, i2 + 1, 0),
        rec_lenOfLargestCommonSubString(s1, s2, i1 + 1, i2, 0), len });
}

template<size_t N1, size_t N2>
size_t dp_lenOfLargestCommonSubString(std::array<char, N1> &s1,
    std::array<char, N2> &s2,
    size_t(&m)[N1 + 1][N2 + 1],
    size_t i1 = 0,
    size_t i2 = 0,
    size_t len = 0) {
    return 1;
}

template<size_t N1, size_t N2>
size_t lenOfLargestCommonSubString(std::array<char, N1> &&s1, std::array<char, N2> &&s2) {
#if 0
    size_t maxLen = 0;
    rec_lenOfLargestCommonSubString(s1, s2, maxLen);
    return maxLen;
#endif
#if 0
    return rec_lenOfLargestCommonSubString(s1, s2);
#endif
#if 1	//NOT WORKING
    size_t m[N1 + 1][N2 + 1]{ 0 };
    for (int i = 0; i < (N1 + 1); ++i)
        for (int j = 0; j < (N2 + 1); ++j)
            m[i][j] = 9999;
    return dp_lenOfLargestCommonSubString(s1, s2, m);
#endif // 0

}

int main() {
    std::cout << lenOfLargestCommonSubString(std::array<char, 8>{'k', 'l', 'a', 'b', 'c', 'd', 'e', 'g'}
    , std::array<char, 8>{'p', 'a', 'u', 'b', 'c', 'd', 'e', 'f'}) << '\n';
}