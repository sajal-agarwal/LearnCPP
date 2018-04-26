#include <iostream>
#include <memory>

class Test
{
public:
    Test() { std::cout << "Test Created!" << std::endl; }
    ~Test() { std::cout << "Test Deleted!" << std::endl; }

    void func() { std::cout << "Called from Test!" << std::endl; }
};

void foo(std::unique_ptr<Test> t) {

}

int main () {
    std::unique_ptr<Test> tup(new Test());
    //foo(tup); //[1] unique_ptr sare non copiable so can not be passed as value to a function

    //[2] On the other hand below function call isperfectly alright as it will invoke the
    //move constructor of unique_ptr and unique_ptr sare movable
    foo(std::unique_ptr<Test>(new Test()));

    //std::unique_ptr<Test> t2 = tup; //This function will also give compilation error - [1]

    //but is fine - [2]
    std::unique_ptr<Test> t3 = std::move(tup); //After this line tup will point to nothing

    std::cout << "tup = " << tup.get() << std::endl;

    std::cout << "t3 = " << t3.get() << std::endl;
}
