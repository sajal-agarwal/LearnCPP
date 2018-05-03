#include<iostream>
#include<vector>
#include<string>
#include<functional>

class Test
{
public:
    Test() {}

    void func(int d, std::string str) {
        auto f = [d, s = std::move(str)](){
            std::cout << "Captured data : " << d << " and " << s << std::endl;
        };
        m_vect.push_back(f);
    }

    void show() {
        for (auto it : m_vect)
            it();
    }

    std::vector<std::function<void(void)>> m_vect;
};


int main(int /*argc*/, char** /*argv*/) {
    Test oTestSig;

    oTestSig.func(1, "one");
    oTestSig.func(2, "two");
    oTestSig.func(3, "three");

    oTestSig.show();

	// Below lines of code shows that lambdas maintain the state
	auto l = [i = 0]() mutable { return ++i; };

	std::cout << l() << '\n';	// this prints 1
	std::cout << l() << '\n';	// this prints 2
	std::cout << l() << '\n';	// this prints 3

	//1 - lambda can be consider as struct with captured values as members
	//so abve lambda will look like below struct
	//2 - A muatable lambda is equivalent to struct with non const operator()
	//function and non-mutable lambda (normal lambda) is equivalent to
	//struct with const operator() function
	//3 - Values captured by lambda by referance can be chnaged even for
	//non-mutable lambdas just as struct in member by referance can be changed
	//in constant methods see below struct named 'struct_l'
	struct struct_l_mutable {
		int i = 0;
		int operator()() {
			return ++i;
		}
	};
	struct_l_mutable slm;
	std::cout << slm() << '\n';	// this prints 1
	std::cout << slm() << '\n';	// this prints 2
	std::cout << slm() << '\n';	// this prints 3

	struct struct_l {
		int i = 0;
		int &j;
		struct_l(int &k) : j(k) {}
		int operator()() const {
#if 0	// This is invalid as function is defined const
			return ++i;
#endif // 0
			return ++j;
		}
	};

	int i = 0;
	struct_l sl(i);
	sl();
}