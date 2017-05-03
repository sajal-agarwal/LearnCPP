#include<iostream>

class CPPAttribute {
public:
    /*
    Indicates that the function does not return to the calling statement.
    This attribute applies to function declarations only.
    The behavior is undefined if the function with this attribute actually returns.
    The following standard functions have this attribute:
    std::_Exit, std::abort, std::exit,
    std::quick_exit, std::unexpected, std::terminate, std::rethrow_exception,
    std::throw_with_nested, std::nested_exception::rethrow_nested
    */
    [[noreturn]]
    void foo ([[maybe_unused]] int x = 7) {
        std::cout << "foo() called!" << std::endl;
        throw "faliled";
    }

    [[deprecated("because safer api available")]]
    void func(int i = 3){
        switch(i){
        case 1:
        {
            [[maybe_unused]] int x = 9;
            std::cout << "Case 1" <<std::endl;
            [[fallthrough]];
        }
        case 2: // no warning on fallthrough
        {
            break;
        }
        case 3:
        {
             std::cout << "Case 3" <<std::endl;
        }
        case 4: // compiler may warn on fallthrough
        {
            break;
        }
        default:
        {

        }
        }

    }

    /* Appears in a function declaration, enumeration declaration, or class declaration.
     * If a function declared nodiscard or a function returning an enumeration or class
     * declared nodiscard by value is called from a discarded-value expression other than
     * a cast to void, the compiler is encouraged to issue a warning.*/
    struct [[nodiscard]] error_info {

    };

    /* Appears in the declaration of a class, a typedef­, a variable,
     * a non­static data member, a function, an enumeration, or an enumerator.
     * If the compiler issues warnings on unused entities,
     * that warning is suppressed for any entity declared maybe_unused.
    */
    [[maybe_unused]]
    error_info func2 () {
        return error_info{};
    }

    [[nodiscard]]
    int func3() {
        return 4;
    }
};


#if 0
#include <attributes.h>

int main(int /*argc*/, char** /*argv*/) {
    CPPAttribute cppattr;

    cppattr.foo();
    cppattr.func();
    cppattr.func2();
}
#endif
