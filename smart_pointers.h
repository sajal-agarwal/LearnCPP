#include <iostream>
#include <memory>

class Test
{
public:
    Test() { std::cout << "Test Created!" << std::endl; }
    ~Test() { std::cout << "Test Deleted!" << std::endl; }
};


int main () {
    std::unique_ptr<Test> tup(new Test());
}
