#ifndef ATOMIC_TYPE_H
#define ATOMIC_TYPE_H

#include <atomic>

class Test
{
    std::atomic<int> m_data;
public:
    Test(int data = 3) : m_data (data) {}

    int operator++ () {
        return ++m_data;
    }

    Test (const Test &other) {
        m_data.store(other.m_data.load());
    }

    int getData () { return m_data.load(); }

    void setData (int data) { m_data = data; }
};

#endif //ATOMIC_TYPE_H


#if 0
struct Test2 {
    int a;
    int b;
    int sum () { return a + b; }
};

#include <atomic_types.h>

int main(int /*argc*/, char** /*argv*/) {
#if 0
    std::atomic<Test> oaTest;   // error: std::atomic requires a trivially copyable type
#endif
    std::atomic<Test2> oaTest2; // no error, but if we add a constructor to Test2 class
                                // Test2 becomes non trivially copyable type, so error
}
#endif
