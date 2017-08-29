#include <tuple>
#include <type_traits>
#include <iostream>


/* Tupple Traversal:
 * Here use of enable_if hide one implemenation of print
 * depending on the value of 'I' because of whihc only
 * these 2 functions with exactly same prototype can
 * exist together.
 * */
template<size_t I = 0, typename Tp>
typename std::enable_if<!I/*0 == I*/>::type print(Tp t) {

}

template<size_t I, typename Tp>
typename std::enable_if<I/*0 < I*/>::type print(Tp t) {
    std::cout <<std::get<I - 1>(t) << std::endl;
    print<I - 1, Tp>(t);
}

int main () {
    auto t = std::make_tuple("my tuple", 4.5, 'A');
    print<std::tuple_size<decltype(t)>::value, decltype(t)>(t);
}
