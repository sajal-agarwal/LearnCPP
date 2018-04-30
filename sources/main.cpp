/* TOPICS TO BE COVERED
*
*
*
*/

#include <findNumOfSetsWithEqualSum.h>

#if 0
#include <iostream>
#include <algorithm>

#define DEFINE_LESS_THAN_OPERATOR 0


struct A {
    A() = default;
    A(int i) : x(i) {}

#if DEFINE_LESS_THAN_OPERATOR
    bool operator<(const A &o) const {
        return x < o.x;
}
#endif // DEFINE_LESS_THAN_OPERATOR


    int x = 1;
};

_STD_BEGIN
template<>
struct less <A> {
    constexpr bool operator()(const A& o1, const A& o2) const {
        return o1.x < o2.x;
    }
};
_STD_END

int main() {
    struct A oA1, oA2 { 2 };

    std::max(oA1, oA2, std::less <A>());

    std::cout << oA2.x << '\n';
}

#endif // 0
