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

#if 1   //SHOW-1
template <typename T>
typename std::enable_if<!has_iterator<T>::value, void>::type show(T t) {
    std::cout << t << std::endl;
}
#endif


#if 1   //SHOW-2
template <typename T>
void show(typename std::enable_if<!has_iterator<T>::value, T>::type t) {
    std::cout << t << std::endl;
}
#endif

template<typename T>
struct is_pointer : std::false_type {

};

template<typename T>
struct is_pointer <T*> : std::true_type {

};


#include <string>
#include <vector>

int main () {
#if 0
    Test<float> intTest;
    std::cout << intTest.foo<std::string>(std::string("9")) << std::endl;
#endif

    show(std::vector<int>{1, 2, 3, 4, 5});
    show<int>(3);   // Works with both SHOW-1 as well as SHOW-2
    //In above call both SHOW-1 ans SHOW-2 are valid, still no ambiguity
    //SHOW-2 is used for both (above and below) the calls. If SHOW-2 is
    //defined alone below call gives compilation erro but both are defined
    //SHOW-2 is called
    show(5);    //SHOW-2 gives compilation error - 'void show(std::enable_if<!has_iterator<T>::value,T>::type)': could not deduce template argument for 'T'


}

