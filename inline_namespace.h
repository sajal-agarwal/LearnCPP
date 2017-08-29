#pragma once

#include <iostream>

namespace  outer {
inline  //without this foo() would not be visible to outer
namespace inner {
    template<class T>
    void foo(T t) { std::cout << "foo() called" << std::endl; }
}
#if 0   //this has the same effect as inline
using namespace inner;
#endif
}

/* below specialization will only work with 'inline' symentic
 * for exposing inner to outer NOT with 'using namespace ...'
 * symentic
 **/
namespace outer {
template<>
void foo<int>(int i) {std::cout << "specialised foo() called" << std::endl;}
}

int main () {
    outer::foo(2);
}
