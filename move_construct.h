#include <iostream>



class MoveConstruct {
public:
	MoveConstruct() = default;

	// Copy constructor
	MoveConstruct(const MoveConstruct& other) {
		std::cout << "Copy constructor called!" << std::endl;
	}
	// Assignment operator
	MoveConstruct& operator=(const MoveConstruct& other) {
		std::cout << "Assignment operator called!" << std::endl;
	}
	// Move constructor
	MoveConstruct(MoveConstruct&& other) {
		std::cout << "Move constructor called!" << std::endl;
	}
	// Move assignment operator
	MoveConstruct& operator=(MoveConstruct&& other) {
		std::cout << "Move assignment operator called!" << std::endl;
	}

	void foo(const MoveConstruct& obj) {
		std::cout << "foo() called!" << std::endl;
	}

	void foo(MoveConstruct&& obj) {
		std::cout << "Move foo() called!" << std::endl;
	}
};

#if 0 //main.cpp
#include <iostream>
#include "move_construct.cpp"

MoveConstruct get() {
	MoveConstruct omc;
	return omc;
}
int main(int /*argc*/, char **/*argv*/) {
	MoveConstruct omc = get();
	MoveConstruct omc2;
	omc.foo(get());
}
#endif