#pragma once

#include <iostream>
#include <array>
#include <utility>

#define USE_USER_DEFINED_LESS 1

template<size_t N>
bool isP(std::array<char, N> &inStr, size_t bi, size_t ei) {
    for (size_t i = bi, j = ei; i < j; ++i, --j)
        if (inStr[i] != inStr[j]) return false;
    return true;
}

//dp solution for size
template<size_t N>
size_t dp_lps(std::array<char, N> &inStr, size_t bi, size_t ei, size_t(&m)[N][N]) {
    if (0 != m[bi][ei])
        return m[bi][ei];

    if (isP(inStr, bi, ei)) m[bi][ei] = (ei - bi + 1);
    else m[bi][ei] = std::max(dp_lps(inStr, bi + 1, ei, m), dp_lps(inStr, bi, ei - 1, m));

    return m[bi][ei];
}

//dp solution for sub array
//-------------------------
//the default less operator does work because std::max requires an explicit less functor
//to be passed otherwise it goes for the <operator function instead so if below functor
//is explicitly passed the std::max function will use it orelse it will go for default
//<operator function in this case the default <operator function for std::pair
#if !USE_USER_DEFINED_LESS 
namespace std {
    template<>
    struct less<std::pair<size_t, size_t>> {
        constexpr bool operator()(const std::pair<size_t, size_t>& p1, const std::pair<size_t, size_t>& p2) const {
            return std::less<size_t>()((p1.first - p1.second), (p2.first - p2.second));
        }
    };
}
#endif // 0

#if USE_USER_DEFINED_LESS
struct lps_less {
    bool operator() (const std::pair<size_t, size_t>& p1, const std::pair<size_t, size_t>& p2) {
        return std::less<size_t>()((p1.first - p1.second), (p2.first - p2.second));
    }
};
#endif // 0

template<size_t N>
std::pair<size_t, size_t> dp_lps(std::array<char, N> &inStr, size_t bi, size_t ei, std::pair<size_t, size_t>(&m)[N][N]) {
    if ((0 != m[bi][ei].first) || (0 != m[bi][ei].second))
        return m[bi][ei];

    if (isP(inStr, bi, ei)) m[bi][ei] = std::make_pair(ei + 1, bi + 1);
    else m[bi][ei] = std::max(dp_lps(inStr, bi + 1, ei, m), dp_lps(inStr, bi, ei - 1, m)
#if USE_USER_DEFINED_LESS
        , lps_less()
#endif
    );

    return m[bi][ei];
}

//recursive solution
template<size_t N>
size_t r_lps(std::array<char, N> &inStr, size_t bi, size_t ei) {
    if (isP(inStr, bi, ei))
        return (ei - bi + 1);

    return std::max(r_lps(inStr, bi + 1, ei), r_lps(inStr, bi, ei - 1));
}

//recursive solution
template<size_t N>
void r_lenOfLargestPossiblePalindrom(std::array<char, N> &inStr, size_t bi, size_t ei
	, size_t &maxlen, size_t len = 0) {
	if (bi == ei) {
		len += 1;
		if (maxlen < len)
			maxlen = len;
		return;

	}
	if ((1 + bi) == ei) {
		len += 2;
		if (maxlen < len)
			maxlen = len;
		return;
	}

	if (inStr[bi] == inStr[ei])
		r_lenOfLargestPossiblePalindrom(inStr, bi + 1, ei - 1, maxlen, len + 2);

	r_lenOfLargestPossiblePalindrom(inStr, bi + 1, ei, maxlen, 0);
	r_lenOfLargestPossiblePalindrom(inStr, bi, ei - 1, maxlen, 0);
}

template<size_t N>
size_t lps(std::array<char, N> &&inStr) {
#if 0
    return r_lps(inStr, 0, N - 1);
#endif
#if 0
    size_t m[N][N]{ 0 };
    return dp_lps(inStr, 0, N - 1, m);
#endif
#if 0
	std::pair<size_t, size_t> m[N][N];
	auto range = dp_lps(inStr, 0, N - 1, m);
	for (size_t i = range.second - 1; i < range.first; ++i)
		std::cout << inStr[i];
	std::cout << '\n';
	return (range.first - range.second + 1);
#endif

	size_t maxlen = 0;

	r_lenOfLargestPossiblePalindrom(inStr, 0, N - 1, maxlen);

	return maxlen;
}

int main() {
    std::cout << lps(std::array<char, 9>{ 'm', 'a', 'b', 'm', 'o', 'm', 'b', 'a', 'd' });
}

