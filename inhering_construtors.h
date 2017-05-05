class A
{
public:
    template<typename T>
    A(T t){}

    A() {}
    explicit A(int x) {}
    A(float x){}

    template<typename T>
    void foo(T t){}

    template<typename T>
    void foo(T *t){}
#if 0
    template<>
    void foo<int>(int t){}
#endif

    void foo(int x){}
    void foo(int *x){}
    virtual void foo(char (&arr)[5]){}

};

template<>
void A::foo<int>(int t){}

class B: public A
{
    using A::A;
public:
    using A::foo;   //function inheritance
    void foo() {}
    void foo(int x){}   //function hidding
    virtual void foo(char (&arr)[5]){}  //function over-ridding
};

template<typename T>
void foo(T t) {

}

template<>
void foo<int>(int x) {

}
#if 0   // below is same as above <int> is optional
template<>
void foo (int x) {

}
#endif

void foo (int x) {

}

void foo (double x) {

}

int main () {
    B oB1(5);
    B oB2(float(3.67));

    B oB;
    int m = 0;
    oB.foo(m);
    //oB.foo(&m);

    foo<int>(4);
}
