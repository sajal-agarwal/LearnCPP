class B {
public:
	B() = default;
	B(const B& o) = delete; // its a good practice to delete the default defination 
							// of copy constructor of base class and make use of 
							// virtual clone function
	virtual ~B() = default;
	void foo() {}
	virtual void func() {}
    virtual void func2() final {}
};

class C :public B{
public:
	C() = default;
	C(const C& o){}

	void foo() = delete;
    void func() override final {}    // so any mistake in name of the function can be caught unless function
							// with that name is present in base class and declared virtual, also
							// it clearlly tells that the function is overiding a base class  function
#if 0
    void func2() {} //error: overriding final function 'virtual void B::func2()'
#endif
};

class D: public C {
public:
#if 0
    void func() {}  //error: overriding final function 'virtual void C::func()'
#endif
};

int main(int /*argc*/, char **/*argv*/) {
	C oc;
#if 0
    oc.foo(); //error: use of deleted function 'void C::foo()'
#endif
	B().foo();
}
