#pragma once
#include <optional>
#include <string>
#include <iostream>
#include <any>
#include <variant>


#define IN_PLACE_WITH_OPTIONAL 0
#define IN_PLACE_WITH_ANY 0
#define IN_PLACE_WITH_VARIANT 1

class Test
{
    int m_idata{};
    std::string m_str{};
public:
    Test(const int idata, std::string str)
        : m_idata(idata)
        , m_str(std::move(str))
    {
        std::cout << "Constructed\n";
    }

    Test(const Test& o)
    {
        std::cout << "Copied\n";
    }

    Test(Test &&o) noexcept
    {
        std::cout << "Moved\n";
    }

    ~Test()
    {
        std::cout << "Deleted\n";
    }

    void print() const
    {
        std::cout << m_idata << '|' << m_str << '\n';
    }
};

int main()
{
#if IN_PLACE_WITH_OPTIONAL
    {
        std::cout << "1)-----------\n";
        std::optional<Test> t{ Test{3, "CPP"} };
        /* In above line:
        * First, a temporary Test object will be created
        * then it will be moved
        * then the left over object will be deleted
        * and at last Test object owned by optional will be deleted
        *
        * This is quite inefficient. The best case would be if Test
        * object gets created once with in the optional and gets
        * destructed when optional is destructed. We can achieve it
        * with the help of std::in_place as below
        */
    }
    {
        std::cout << "2)-----------\n";
        std::optional<Test> t{ std::in_place, 3, "CPP" };
    }
    {
        // This is same as std::in_place
        std::cout << "3)-----------\n";
        std::optional<Test> t = std::make_optional<Test>(3, "CPP");
    }
#endif // IN_PLACE_WITH_OPTIONAL

#if IN_PLACE_WITH_ANY
    {
        // Without std::in_place_type
        std::cout << "1)-----------\n";
        std::any any{ Test{3, "CPP"} };
    }
    {
        // With std::in_place_type
        std::cout << "2)-----------\n";
        std::any any{ std::in_place_type<Test> , 3, "CPP" };
        /* 
        * Here we have used 'std::in_place_type<Test>' becuse
        * unlike std::optional std::any is not templated so
        * lacks in type information and the same is provided
        * using 'std::in_place_type<Test>'. With this std::any
        * contructor will know what type of object to be created
        * in place.
        */
    }
    {
        // This is same as std::in_place_type
        std::cout << "3)-----------\n";
        std::any any = std::make_any<Test>(3, "CPP");
    }
#endif // IN_PLACE_WITH_ANY

#if IN_PLACE_WITH_VARIANT
    {
        // Without std::in_place_type
        std::cout << "1)-----------\n";
        std::variant<Test, int, std::string> var{ Test{3, "CPP"} };
    }
    {
        // With std::in_place_type
        std::cout << "2)-----------\n";
        std::variant<Test, int, std::string> var{ std::in_place_type<Test> , 3, "CPP" };
        /*
        * Here we have used 'std::in_place_type<Test>' becuse
        * unlike std::optional std::any is not templated so
        * lacks in type information and the same is provided
        * using 'std::in_place_type<Test>'. With this std::any
        * contructor will know what type of object to be created
        * in place.
        */
    }
    {
        // With std::in_place_index
        std::cout << "3)-----------\n";
        std::variant<Test, int, std::string> var{ std::in_place_index<0> , 3, "CPP" };
        /*
        * Here same result is achieved using std::in_place_index.
        * It tells the std::variant create the object of type at
        * index mentioned in std::in_place_index
        */
    }
#endif // IN_PLACE_WITH_VARIANT
    return 0;
}