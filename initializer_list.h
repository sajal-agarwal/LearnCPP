#include <vector>
#include <initializer_list>
#include <iostream>
#include <string>

/* vector::emplace_back used initizer list so it is possible to
 * pass the members of an object, rather the object itself
 */

class InitializerList {
    std::vector<int> m_vect;

public:
    class Biodata {
        friend InitializerList;
    public:
        struct Name;
        Biodata(struct Name fname, std::string htown, unsigned short ag, std::vector<std::string> hb)
            : fullName(fname)
        , homeTown(htown)
        , age(ag)
        , hobbies(hb){

        }

    private:
        struct Name {
            std::string name;
            std::string surName;
        } fullName;

        std::string homeTown;
        unsigned short age;
        std::vector<std::string> hobbies;
    } m_biodata;

    InitializerList(std::initializer_list<int> intList, Biodata biodata)
        : m_vect (intList)
        , m_biodata (biodata) {

    }
#if 1
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
#endif
};

int main(int /*argc*/, char** /*argv*/) {
    InitializerList oil{{3, 4, 7, 9, 2}, {{"Sajal", "Agarwal"}, "Lucknow", 32, {"Movie", "TV", "Gardening"}}};
    oil.print();
}

