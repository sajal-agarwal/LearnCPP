class MyClass {
    int value{ 3 };

public:
    MyClass(int val = 2) : value(val) {}

    /* Below 'friend' function is as good as defined outside the class
    *  IT IS NOT A MEMBER FUNCTION OF THE 'MyClass' CLASS
    */
    friend MyClass operator+ (const MyClass &other1, const MyClass &other2) {
        return MyClass(other1.value + other2.value);
    }

    /* If below function is non-const then [1] has no issue */
    MyClass operator+ (const MyClass &other) const {
        return MyClass(value + other.value);
    }

    MyClass& copy(const MyClass& other) {
        value = other.value;
        return *this;
    }
};

int main() {
    MyClass myClass, myClass2{ 4 };
    myClass.copy(myClass2);
#if 0   //[1] compiler error: 'operator +' is ambiguous
    myClass = myClass + myClass2;
#endif

    myClass = operator+(myClass, myClass2);
}
