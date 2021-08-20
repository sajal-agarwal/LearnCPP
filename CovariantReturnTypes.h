#pragma once
#include <cstdio>


// Suppose we have base class named 'Base'
class Base
{
public:
    virtual void do_something() const
    {

    }

    void test()
    {
        puts("Base::test() called");
    }
};

// and a derived class named 'Derived'
class Derived: public Base
{
public:
    void test()
    {
        puts("Derived::test() called");
    }
};

/*
* Now image there is another base class named
* 'ClientBase'which has method named 'getObject()'
* which return a Base*.
*/ 
class ClientBase
{
    Base* m_object{ nullptr };
public:
    ClientBase(Base* object) : m_object(object)
    {

    }

    virtual Base* getObject() const
    {
        return m_object;
    }
};

/* 
* Now let say there is another class named
* 'ClientDerived' and this class is derived
* from 'ClientBase'. Also, it overrides the
* getObject function. In general, return type
* of the overridden function should be same
* as the return type of the base class fun-
* ction but there is an exception to this.
* If the return type of the overridden fun-
* ction is derived from the return type of
* the base class function then it is valid.
* This phenomenon is know as Covariant Return
* Type. This is mostly in cloning/copying
* scenarios where the base class has a vertual
* clone method which is overridden by the
* derived classes. In this case returning the
* derived class pointer from the derived class
* can help avoiding use of dynamic_cast.
*/
class ClientDerived: public ClientBase
{
public:
    using ClientBase::ClientBase;

    Derived* getObject() const override
    {
        return dynamic_cast<Derived*>(ClientBase::getObject());
    }
};

//{ Clone Example
/* In this example cloning from base class
* pointer will return base class pointer
* and cloning from derived class pointer
* will return derived class pointer.
*/
class Object
{
    int m_data{};

protected:
    void copy(Object* obj)
    {
        obj->m_data = m_data;
    }
public:
    Object() = default;
    Object(const int data): m_data(data)
    {}

    virtual Object* clone()
    {
        auto obj = new Object{};
        copy(obj);
        return obj;
    }
};

class DerivedObject: public Object
{
    double m_data2{};

protected:
    void copy(DerivedObject* obj)
    {
        Object::copy(obj);
        obj->m_data2 = m_data2;
    }

public:
    DerivedObject() = default;
    DerivedObject(const int data1, const double data2)
        : Object(data1)
        , m_data2(data2)
    {}

    DerivedObject* clone() override
    {
        auto obj = new DerivedObject{};
        copy(obj);
        return obj;
    }
};
//} Clone Example

int main()
{
    ClientDerived d{ new Derived{} };
    ClientBase& b = d;
    /* Below call prints 'Derived::test() called'
    * Without Covariant return type it would have
    * printed 'Base::test() called'.
    */
    d.getObject()->test();
    /* On the other below call will still prints
    * 'Base::test() called' because we are calling
    * a virtual function through a Base class
    * pointer pointing to derived class. Even though
    * The derived class 'getObject()' function is
    * called the return is decided based on the
    * virtual function in the base class.
    */
    b.getObject()->test();

//{ Clone Example
    DerivedObject dob{3, 4.2};
    auto cdob = dob.clone();
    Object& bob = dob;
    auto cbob = bob.clone();
//} Clone Example
}