#include <iostream>
#include <string>

using namespace std;

void sum(int a, int b)
{
    cout << a + b << endl;
}

void concat(const string& a, const string& b)
{
    cout << a + b << endl;
}

/* Below function will cause compilation error
 * if L-1 block is enabled and L-2 is disabled
 * reason being const value can not be passed
 * to a non const reference to fix this if we
 * chnage the function as L-3 by removing const
 * then L-4 and L-5 will give compilation error
 * as rvalue reference can not be passed to non-
 * const value. So one solution would be to create
 * another function such as L-6 but the problem
 * with this solution is we will end up creating
 * many such function for different parameter.
 * So the best solution is to write a function
 * as L-2. This will alow both above cases to
 * work with a single function std::forward is
 * added to pass the rvalue parameter as rvalue
 * parameter to the next function call
 */
void incr(int a, int &b) {
    b += a;
}
#if 0   //L-1
template <typename PROC, typename A, typename B>
void invoke(PROC p, const A& a, const B& b)
{
    p(a, b);
}
#endif
#if 0   //L-3
template <typename PROC, typename A, typename B>
void invoke(PROC p, A& a, B& b)
{
    p(a, b);
}
#endif
#if 0   //L-6
template <typename PROC, typename A, typename B>
void invoke(PROC p, const A& a, B& b)
{
    p(a, b);
}
#endif
#if 1   //L-2
template <typename PROC, typename A, typename B>
void invoke(PROC p, A&& a, B&& b)
{
    p(std::forward<A>(a), std::forward<B>(b));
}
#endif
int main()
{
    /*L-4*/invoke(sum, 10, 20);
    /*L-5*/invoke(concat, std::string("Hello "), std::string("world"));
    int b = 5;
    invoke(incr, 2, b);
    std::cout << "b = " << b << std::endl;
    return 0;
}
