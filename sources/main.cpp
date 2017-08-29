/* TOPICS TO BE COVERED
*
*
*
*/
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

void incr(int a, int &b) {
    b += a;
}

template <typename PROC, typename A, typename B>
void invoke(PROC p, A&& a, B&& b)
{
    p(a, b);
}

int main()
{
    invoke(sum, 10, 20);
    invoke(concat, std::string("Hello "), std::string("world"));
    int b = 5;
    invoke(incr, 2, b);
    return 0;
}
