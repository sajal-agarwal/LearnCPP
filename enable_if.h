#include <type_traits>
#include <iostream>
#include <string>


template<typename T, typename = typename std::enable_if<!std::is_same<T, int>::value>::type>
class Test {
public:
    Test() {
        std::cout << "Test : int" << std::endl;
    }

    template<typename Q>
    std::string foo(typename std::enable_if<std::is_same<Q, std::string>::value, Q>::type str) {
        return str;
    }
};

template <typename T>
struct has_iterator
{
    template <typename U>
    static char test(typename U::iterator* x);

    template <typename U>
    static long test(U* x);

    static constexpr const bool value = sizeof(test<T>(0)) == 1;
};

template <typename T>
typename std::enable_if<has_iterator<T>::value, void>::type show(T t) {
    for (auto i : t)
        std::cout << i << " ";
    std::cout << std::endl;
}

template <typename T>
typename std::enable_if<!has_iterator<T>::value, void>::type show(T t) {
    std::cout << t << std::endl;
}

#include <string>
#include <vector>

int main () {
#if 0
    Test<float> intTest;
    std::cout << intTest.foo<std::string>(std::string("9")) << std::endl;
#endif

    show(std::vector<int>{1, 2, 3, 4, 5});
    show(3);
}

