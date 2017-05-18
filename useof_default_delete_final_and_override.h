class B {
public:
	B() = default;
	B(const B& o) = delete; // its a good practice to delete the default defination 
							// of copy constructor of base class and make use of 
							// virtual clone function
	virtual ~B() = default;
	void foo() {}
	virtual void func() {}
};

class C :public B{
public:
	C() = default;
	C(const C& o){}

	void foo() = delete;
	void func() override {} // so any mistake in name of the function can be caught unless function
							// with that name is present in base class and declared virtual, also
							// it clearlly tells that the function is overiding a base class  function
};

#if 0 //main.cpp
#include "useof_default_and_delete.cpp"

int main(int /*argc*/, char **/*argv*/) {
	C oc;
	oc.foo(); //attempting to reference a deleted function
	B().foo();
}
#endif