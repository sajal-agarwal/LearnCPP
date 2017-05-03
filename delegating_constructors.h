class Test {
	int m1 = 0, m2 = 0, m3 = 0;
public:
	Test(int p1, int p2):m1(p1), m2(p2), m3(4) {}	//normal constructor
	Test(int p1) : Test(p1, 6){ m3 = 8; }	//delegating constructor - constructor calling constructor
	
	//a call to a delegating constructor shall be the only member-initializer, so below is illeagal
#if 0
	Test(int p1) :Test(p1, 6), m3(5){}
#endif
};