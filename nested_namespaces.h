namespace First {
    namespace Second {
        namespace Third {
            struct MyStruct {

            };
        }
    }
}

/*From C++17 above nested namespaces can also be written like
below. This cleans-up alot of the mess and comes pretty handy
when we need to specialize a templatise class, such std::less
*/
namespace First::Second::Third {
    struct MyStruct2 {

    };
}

int main() {
    First::Second::Third::MyStruct s;
    First::Second::Third::MyStruct2 s2;
}