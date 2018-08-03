#pragma once
#include<iostream>
#include<algorithm>
#include<array>
#include<string>

#if 0
template<size_t N1, size_t N2>
size_t rec_lenOfLargestCommonSubSequence(std::array<char, N1> &s1,
    std::array<char, N2> &s2,
    size_t i1 = 0,
    size_t i2 = 0,
    size_t len = 0) {
    if (i1 == N1 || i2 == N2) return len;

    if (s1[i1] == s2[i2])
        return rec_lenOfLargestCommonSubSequence(s1, s2, i1 + 1, i2 + 1, len + 1);

    return std::max(rec_lenOfLargestCommonSubSequence(s1, s2, i1, i2 + 1, len),
        rec_lenOfLargestCommonSubSequence(s1, s2, i1 + 1, i2, len));
}
#endif // 0


#if 1
template<size_t N1, size_t N2>
size_t rec_lenOfLargestCommonSubSequence(std::array<char, N1> &s1,
    std::array<char, N2> &s2,
    size_t i1 = 0,
    size_t i2 = 0) {
    if (i1 == N1 || i2 == N2) return 0;

    if (s1[i1] == s2[i2])
        return 1 + rec_lenOfLargestCommonSubSequence(s1, s2, i1 + 1, i2 + 1);

    return std::max(rec_lenOfLargestCommonSubSequence(s1, s2, i1, i2 + 1),
        rec_lenOfLargestCommonSubSequence(s1, s2, i1 + 1, i2));
}
#endif

template<size_t N1, size_t N2>
size_t rec_findLargestCommonSubSequence(std::array<char, N1> &s1,
	std::array<char, N2> &s2,
	std::string &maxArr,
	std::string arr = "",
	size_t i1 = 0,
	size_t i2 = 0) {
	if (i1 == N1 || i2 == N2) {
		if (arr.size() > maxArr.size())
			maxArr = arr;
		return 0;
	}

	if (s1[i1] == s2[i2]) {
		arr.push_back(s1[i1]);
		return 1 + rec_findLargestCommonSubSequence(s1, s2, maxArr, arr, i1 + 1, i2 + 1);
	}

	return std::max(rec_findLargestCommonSubSequence(s1, s2, maxArr, arr, i1, i2 + 1),
		rec_findLargestCommonSubSequence(s1, s2, maxArr, arr, i1 + 1, i2));
}

template<size_t N1, size_t N2>
size_t dp_lenOfLargestCommonSubSequence(std::array<char, N1> &s1,
    std::array<char, N2> &s2,
    size_t(&m)[N1 + 1][N2 + 1],
    size_t i1 = 0,
    size_t i2 = 0) {
	if (-1 != m[i1][i2])
		return m[i1][i2];

	size_t tmp = 0;

	if (i1 == N1 || i2 == N2) tmp = 0;
	else if (s1[i1] == s2[i2])
		tmp = 1 + dp_lenOfLargestCommonSubSequence(s1, s2, m, i1 + 1, i2 + 1);
	else
		tmp = std::max(dp_lenOfLargestCommonSubSequence(s1, s2, m, i1, i2 + 1),
			dp_lenOfLargestCommonSubSequence(s1, s2, m, i1 + 1, i2));

	m[i1][i2] = tmp;

	return tmp;
}

template<size_t N1, size_t N2>
size_t lenOfLargestCommonSubSequence(std::array<char, N1> &&s1, std::array<char, N2> &&s2) {
#if 0
    return rec_lenOfLargestCommonSubSequence(s1, s2);
#endif
#if 1
	size_t m[N1 + 1][N2 + 1];
	for (int i = 0; i < N1 + 1; ++i)
		for (int j = 0; j < N2 + 1; ++j)
			m[i][j] = -1;
		
    return dp_lenOfLargestCommonSubSequence(s1, s2, m);
#endif
}

template<size_t N1, size_t N2>
size_t dp_findLargestCommonSubSequence(std::array<char, N1> &s1,
	std::array<char, N2> &s2,
	std::pair<size_t, std::string> (&m)[N1 + 1][N2 + 1], //for more memory efficient solution string can be replaced with char
	size_t i1 = 0,
	size_t i2 = 0) {
	if (-1 != m[i1][i2].first)
		return m[i1][i2].first;

	size_t tmp = 0;

	if (i1 == N1 || i2 == N2) tmp = 0;
	else if (s1[i1] == s2[i2]) {
		tmp = 1 + dp_findLargestCommonSubSequence(s1, s2, m, i1 + 1, i2 + 1);
		m[i1][i2] = std::make_pair(tmp, "*");
	}
	else {
		auto l1 = dp_findLargestCommonSubSequence(s1, s2, m, i1, i2 + 1);
		auto l2 = dp_findLargestCommonSubSequence(s1, s2, m, i1 + 1, i2);
		if (l1 > l2) {
			tmp = l1;
			m[i1][i2] = std::make_pair(tmp, "S1");
		}
		else {
			tmp = l2;
			m[i1][i2] = std::make_pair(tmp, "S2");
		}
	}
	
	return tmp;
}


template<size_t N1, size_t N2>
std::string findLargestCommonSubSequence(std::array<char, N1> &&s1, std::array<char, N2> &&s2) {
	std::string lcs;
#if 0
	rec_findLargestCommonSubSequence(s1, s2, lcs);
#endif // 0
	std::pair<size_t, std::string> m[N1 + 1][N2 + 1];
	for (int i = 0; i < N1 + 1; ++i)
		for (int j = 0; j < N2 + 1; ++j)
			m[i][j].first = -1;

	dp_findLargestCommonSubSequence(s1, s2, m);

	int i = 0;
	int j = 0;
	while ((i < N1) && (j < N2)) {
		if ("S2" == m[i][j].second)
			++i;
		else if ("S1" == m[i][j].second)
			++j;
		else lcs.push_back(s1[i++]);
	}

	return lcs;
}

template<size_t N>
void true_dp_printLargestPalindromicSequence(std::array<char, N> &arr, size_t(&m)[N][N]) {
	for (int i = 0; i < N; ++i)
		m[i][i] = 1;

	for (int i = 0; i < N - 1; ++i)
		m[i][i + 1] = (arr[i] == arr[i + 1]);

	size_t maxLen = 1, start = 0, end = 0;
	for (int s = 2; s < N; ++s) {
		for (int i = 0, j = s; j < N; ++i, ++j) {
			if (m[i + 1][j - 1] && (arr[i] == arr[j])) {
				m[i][j] = m[i + 1][j - 1] + 2;
				if (m[i][j] > maxLen) {
					maxLen = m[i][j];
					start = i;
					end = j;
				}
			}
		}
	}

	for (int i = start; i <= end; ++i)
		std::cout << arr[i];

	std::cout << '\n';
}

template<size_t N>
void printLargestPalindromicSequence(std::array<char, N> &&arr) {
	size_t m[N][N] = { 0 };
	true_dp_print_lpsst(arr, m);
}

int main() {
    std::cout << findLargestCommonSubSequence(
        std::array<char, 11>{'h', 'i', 'p', 'a', 'b', 'm', 'n', 'c', 'd', 'e', 'g'}
    , std::array<char, 9>{'y', 'a', 'b', 'k', 'c', 'd', 'e', 'f', 'g'}) << '\n';
}

#if 0
int main() {
	printLargestPalindromicSequence(std::array<char, 14>{'b', 'a', 'n', 'a', 'n', 'a', 'k', 'b', 'a', 'n', 'a', 'n', 'a', 'b'});
}
#endif // 0
