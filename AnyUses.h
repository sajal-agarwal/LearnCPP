#include <any>
#include <vector>
#include <iostream>

struct X
{
    int x{ 0 };
};

int main()
{
    std::vector<std::any> anyList;

    anyList.push_back(1);
    anyList.push_back(3.14);
    anyList.push_back('A');
    anyList.push_back(std::string("Hi"));
    anyList.push_back(X{ 5 });

    std::cout << std::any_cast<int>(anyList[0]) << '\n';
    std::cout << std::any_cast<double>(anyList[1]) << '\n';
    std::cout << std::any_cast<char>(anyList[2]) << '\n';
    std::cout << std::any_cast<std::string>(anyList[3]) << '\n';
    std::cout << std::any_cast<X>(anyList[4]).x << '\n';
}
