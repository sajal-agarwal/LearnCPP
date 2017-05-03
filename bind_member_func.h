#include<string>
#include<iostream>

class Test
{
public:
    Test() {}

    void foo(int id, std::string str) {
        std::cout << id << ", " << str << std::endl;
    }
};

void func3(Test o, void (Test::*f)(int, std::string)) {
    (o.*f)(2, "you");
}

template<typename... Args>
void func4(std::function<void(int, std::string)> f, Args... args){
    f(args...);
}


#if 0   //main.cpp
#include<bind_member_func.h>

int main(int /*argc*/, char** /*argv*/) {
    Test oTest;

    //here func3() is calling a member function via pointer to function
    func3(oTest
          , &Test::foo  //this parameter can be passed with '&' as well
          );

    //here fun4() is calling a member function indirectly via bind
    func4(std::bind(&Test::foo, oTest   //this argument can be a pointer as well
                                        //here it is passed as reference
                    , std::placeholders::_1, std::placeholders::_2)
          , 24, "Twenty four");
}
#endif
