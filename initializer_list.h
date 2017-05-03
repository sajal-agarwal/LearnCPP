#include <vector>
#include <initializer_list>
#include <iostream>
#include <string>

class InitializerList {
    std::vector<int> m_vect;

public:
    struct Biodata {
        struct Name {
            std::string name;
            std::string surName;
        } fullName;
        std::string homeTown;
        unsigned short age;
        std::vector<std::string> hobbies;
    } m_biodata;

    InitializerList(std::initializer_list<int> intList, struct Biodata biodata)
        : m_vect (intList)
        , m_biodata (biodata) {

    }

    void print() {
        std::cout << "Int Vector:" << std::endl;
        for (auto e : m_vect) {
            std::cout << e << " ";
        } std::cout << std::endl;
        std::cout << "Bio-data:" << std::endl;
        std::cout << "{" << m_biodata.fullName.name << ", "
                  << m_biodata.fullName.surName << ", "
                  << m_biodata.homeTown << ", "
                  << m_biodata.age << ", ";
        std::cout << "Hobbies: ";
        for (auto e : m_biodata.hobbies) {
            std::cout << e << " ";
        } std::cout << "}" << std::endl;
    }
};

#if 0 //main.cpp
#include <initializer_list.cpp>

int main(int /*argc*/, char** /*argv*/) {
    InitializerList oil{{3, 4, 7, 9, 2}, {{"Sajal", "Agarwal"}, "Lucknow", 32, {"Movie", "TV", "Gardening"}}};
    oil.print();
}
#endif
