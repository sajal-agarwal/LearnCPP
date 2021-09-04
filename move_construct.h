#include <iostream>



class MoveConstruct {
public:
	MoveConstruct() {
		std::cout << "Constructor called!" << std::endl;
	}

	// Copy constructor
	MoveConstruct(const MoveConstruct& other) {
		std::cout << "Copy constructor called!" << std::endl;
	}
	// Assignment operator
	MoveConstruct& operator=(const MoveConstruct& other) {
		std::cout << "Assignment operator called!" << std::endl;
	}
	// Move constructor
	MoveConstruct(MoveConstruct&& other) noexcept {
		std::cout << "Move constructor called!" << std::endl;
	}
	// Move assignment operator
	MoveConstruct& operator=(MoveConstruct&& other) noexcept {
		std::cout << "Move assignment operator called!" << std::endl;
	}

	void foo(const MoveConstruct& obj) {
		std::cout << "foo() called!" << std::endl;
	}

	void foo(MoveConstruct&& obj) {
		std::cout << "Move foo() called!" << std::endl;
	}
};

MoveConstruct get() {
#if 0 // This contruct and move
	MoveConstruct omc;
	return omc;
#endif
	/*
	* This will only contruct no move.
	* This is known as copy and move elision.
	*/
	return MoveConstruct{};
}
int main(int /*argc*/, char **/*argv*/) {
	MoveConstruct omc = get();
	MoveConstruct omc2;
	omc.foo(get());
}
