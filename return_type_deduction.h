#include <vector>
#include <algorithm>

using int_vector = std::vector<int>;

class MyClass
{
public:
	MyClass() = default;
	~MyClass() = default;

	// Trailing return type (->std::vector<int> and ->size_t) in below 2
    // function not required since c++14 the 'int elem' in lambda function
    // parameter can be replaced with auto elem
    auto allGreaterThan(int n) {
		std::vector<int> greaterVect;
		std::for_each(m_intVect.begin()
			, m_intVect.end()
            , [&greaterVect, &n](auto elem) {
			if (elem > n) {
				greaterVect.push_back(elem);
			}
		});
		return greaterVect;
	}

	// In c++14 it is possible to define generic lambdas like 
	// defined in below getSize() function, here 'c' must have 
	// a function called size()
	auto getSize() {
		auto getSize = [](auto c){ return c.size(); };
		getSize (m_intVect);
	}

	bool findElem(int elem) {
		// In below lambda trailing return type (->bool) could be omited
		// even though there are mutiple return path but same is
		// not true for class methods (as above) with vs2013 compiler
		// but as per c++14 specification it should be true for both
		// lambdas and methods, verified the same @ http://cpp.sh/
		return (m_intVect.end() != std::find_if(m_intVect.begin()
			, m_intVect.end()				
			, [&elem](int e) {
			if (e == elem)
				return true;
			else return false;
		}
		));
	}

    // In below function if m_intVect is returned with '()' the
    // return type is deduced as int_vector& othertwise int_vector.
	// If only auto is used in place of decltype(auto)
	// the return type is deduced as int_vector in both
	// scenerios (with brecket and with out brecket).

	decltype(auto) getVect() { return (m_intVect); }

private:
	int_vector m_intVect;
};
