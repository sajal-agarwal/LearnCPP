#pragma once
#include <cstdio>

#define INVALID_FUNCTION_DEFINITION 0
#define INVALID_CLASS_DEFINITION 0

//{ FINAL FUNCTION USES
class Base
{
public:
    virtual void do_something() const
    {
        puts("Base::do_something called");
    }
};

class Derived: public Base
{
public:
    /*
    * This class declares do_something() as final
    * so all the classes which are derived from
    * Derived class are forbidden to override it.
    * Set INVALID_FUNCTION_DEFINITION to 1 to see
    * the error.
    */
    void do_something() const final override
    {
        puts("Derived::do_something called");
    }
};

class DerivedDerived : public Derived
{
public:
#if INVALID_FUNCTION_DEFINITION
    void do_something() const override
    {
        puts("DerivedDerived::do_something called");
    }
#endif

};
//} FINAL FUNCTION USES

//{ FINAL CLASS USES
class Derived2 final: public Base
{
};

#if INVALID_CLASS_DEFINITION
class DerivedDerived2 : Derived2
{
};
#endif // 0


int main()
{

}
