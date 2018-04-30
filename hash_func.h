#pragma once
#include <iostream>

//genaric hash combiner function
template <typename T, typename... Rest>
inline void hash_combine(std::size_t& seed, const T& v, Rest... rest) {
    std::hash<T> hasher;
    seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    hash_combine(seed, rest...);
}

inline void hash_combine(std::size_t& seed) { }

//genaric hash specilization for std::pair
namespace std {
    template<typename T1, typename T2>
    struct hash<std::pair<T1, T2>> {
        size_t operator()(const std::pair<size_t, int>& key) const {
            std::size_t seed = 0;
            hash_combine(seed, key.first, key.second);
            return seed;
        }
    };
}



