#include<string>
#include<array>

class Test
{
public:

    /*The real benefits of member initializers do not become apparent until
     * a class has multiple constructors. For many data members, especially
     * private ones, all constructors initialize a data member to a common
     * value as in the next example 'school' is initialized by most of the
     * constructors to a single value "SKD" so it would convinient initialized
     * at one place by replacing "NO NAME" to "SKD" and have it as a member
     * only for those constructors which may require a different value for
     * school like the 4th constructor below
     */
    Test(): i (3), id{'N', 'D', 'A'}, school("SKD"){}
    Test(int _i): i (_i), id{'K', 'P', 'L'}, school("SKD"){}
    Test(int _i, std::array<char, 4> _id): i (5), id(_id), school("SKD"){}
    Test(int _i, std::array<char, 4> _id, std::string _school): i (5), id(_id), school(_school){}
private:
    int i = 9;
    std::array<char, 4> id;
    std::string school = "NO NAME";
};


#if 0
#include <non_static_data_member_initializers.h>

int main(int /*argc*/, char** /*argv*/) {
    Test oTest;
}

#endif
