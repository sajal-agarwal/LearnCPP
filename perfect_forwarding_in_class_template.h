#include<iostream>
#include<string>
#include<type_traits>

template<typename P>
class B {
public:
#if 0
    explicit B(std::string &&str) : m_str(std::move(str)) {}
    explicit B(const std::string &str) : m_str(str) {}
#endif
    template<typename T>
    explicit B(T &&str) : m_str(std::forward<T>(str)) {}

#if 0
	template<typename U>
	std::enable_if_t<std::is_convertible<std::remove_cv_t<std::remove_reference_t<U>>, std::remove_cv_t<std::remove_reference_t<P>>>::value
		|| std::is_same<std::remove_cv_t<std::remove_reference_t<U>>, std::remove_cv_t<std::remove_reference_t<P>>>::value> set(U &&str) {
		m_str = std::forward<U>(str);
	}
#endif
	template<typename U>
	std::enable_if_t<std::is_convertible<std::remove_cv_t<std::remove_reference_t<U>>, std::remove_cv_t<std::remove_reference_t<P>>>::value> set(U &&str) {
		m_str = std::forward<U>(str);
	}

private:
    std::string m_str;
};

//Perfect forwarding with variadic template using two function
template<typename... Args>
class C {
public:
	void foo(Args&&... args) {      //1

	}

	/*
	SFINAE only works for deduced template arguments.
	In your case your method did not depend on any
	parameter from the method call so it is not in a
	deduced context. Everything is already known while
	instantiate the class itself.
	*/
#if 0
	template<typename = std::enable_if_t<(0 < sizeof...(Args))>>
	void foo(const Args&... args) {     //2

	}
#endif
	template<size_t N = sizeof...(Args)>
	std::enable_if_t<N && (N == sizeof...(Args))> foo(const Args&... args) {     //2

	}
};


//Perfect forwarding with variadic template using one function
template <typename... Ts>
struct Test
{
	template <typename... Us>
	std::enable_if_t<(std::is_convertible_v<std::remove_cv_t<std::remove_reference_t<Us>>, std::remove_cv_t<std::remove_reference_t<Ts>>> && ...)> foo(Us&&... t) {
	}
};

//Perfect forwarding with variadic template using one function with disjunction
/*
* In below code std::conjunction_v performs the && operation and gives the result
* Simillarly for or-ing the utility is std::disjunction_v
*/
template <typename... Ts>
struct D {
	template <typename... Us>
	std::enable_if_t<std::conjunction_v<
		std::is_convertible<std::remove_cv_t<std::remove_reference_t<Us>>,
		std::remove_cv_t<std::remove_reference_t<Ts>>
		>...>>
		foo(Us&&... t) {}
};

int main() {
    std::string str = "Hmmm";
    B<std::string> oB("Hmmm");
    B<std::string> oB2(str);
    oB.set("Hmmm");
    oB.set(str);

    //Perfect forwarding with variadic template using two function
	C<> oC;
	oC.foo();	//First foo will be called here

    C<int, std::string> c;
    int x = 3;
    c.foo(3, "hi");  //1 will be called
    c.foo(x, "hi");  //2 will be called
    c.foo(std::move(x), "hi");  //1 will be called

#if 0 	//This is not compiling in VS2017
	//Perfect forwarding with variadic template using one function
	D<int, std::string> oD;
	oD.foo(4, "hi");
	int y = 3;
	oD.foo(y, str);
#endif

}
