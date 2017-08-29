#include <iostream>
#include <tuple>

/* Finding Factorial:
 * ------------------
 * The advantage of template meta programing
 * is all work happens a compile time it self
 * so in this particular case time take for
 * Fact<5> and Fact<17> at run time will be
 * same.
 * */
template<size_t N>
struct Fact {
    static constexpr size_t value = N*Fact<N-1>::value;
};

template<>
struct Fact<0> {
  static constexpr size_t value = 1;
};
/* Finding Factorial */

/* Print tuple:
 * ------------
 * */
template<size_t N, typename Tp>
struct PrintTp {
    void operator()(const Tp &t) {
        std::cout << std::get<N-1>(t) << std::endl;
        PrintTp<N-1, Tp>()(t);
    }
};
/* Below is the example of partial template specialization
 * */
template<typename Tp>
struct PrintTp<0, Tp> {
    void operator()(Tp t) {
    }
};

int main() {
    std::cout << "Fact(5) = " << Fact<5>::value << std::endl;
    auto t = std::make_tuple("my typle", 2.34, 'S');
    PrintTp<std::tuple_size<decltype(t)>::value, decltype(t)>()(t);
}
