#include <string>

/* Personal Mith: Overloaded function must have the same return type
*  Below class compiles with no error.Which means that function ove-
   rloading depends entirly on function parameters and has nothing to
   do with return type
*/

class C {
public:
	static const int x = 9;

	int foo() {}
	std::string foo(int c) {}
	const std::string foo() const {}
    double foo(int v) const {}
};
