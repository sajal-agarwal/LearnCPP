//AGGREGATE INITIALIZATION
//========================

#include<string>
#include<vector>

struct S {
    int i;
    std::string str;
};

struct S2 {
    float f;
    S s;
    std::vector<double> vect;
};

struct S3 : S {
    char ch;
    double d;
};

class C {
public:
    int i = 9;
    std::string str;

    /*
    For uniform initialization to work class must
    not have any user defined or delete/default-ed
    constructors
    */
#if 0
    C() {}
#endif
    /*
    For uniform initialization to work class must
    not have any virtual functions
    */
#if 0
    virtual void foo() {}
#endif
    /*
    For uniform initialization to work there should be no
    private or protected data members
    */
#if 0  
private:
    float f;
#endif

};

int main() {
    S s{ 2, "Hi" }, s_1{ 5 }
#if 0   // This fails as the member before 'str' is not initilized
        , s_2{ "Fails" }
#endif
#if 0   // '{}' can not replaced with '()' unless a suitable constructor is available
    , s_2(1);
#endif
    ;
    S2 s2{ 3.1415f,{ 3, "Hello" } }, s2_1{ 2.34f }, s2_2{ 3.1415f,{ 3, "Hello" },{ 1, 2, 3, 4 } };

    //UNIFORM INITIALIZATION WITH ARRAY
    S s_arr[3] = { { 1, "a" },{ 2, "b" },{ 3, "c" } };

    /*
    UNIFORM INITIALIZATION WITH INHERITENCE
    ---------------------------------------
    below is invalid as base class is not initialized
    (no constructor to do that)
    */
#if 0
    S3 s3{ 'V', 3.4 };
#endif
    /*
    Untill C++17 a constructor was must to make above code valid
    C++17 provides a way to initialize base classes as well with-
    in uniform initilization, as below
    */
    S3 s3{ { 12, "Monkey" }, 'V', 3.4 };

    /*
    UNIFORM INITILIZATION WITH CLASSES
    ----------------------------------
    Uniform initilization also works with classes
    provided all the members are public and the
    - class has no private and/or protected members
    - Class has no virtual functions
    - Class has no user defined constructor
    */
    C c{ 7, "Boy" };
}