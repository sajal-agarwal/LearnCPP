#include<vector>

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


#if 0
#include<lambda_capture.h>

int main(int /*argc*/, char** /*argv*/) {
    Test oTestSig;

    oTestSig.func(1, "one");
    oTestSig.func(2, "two");
    oTestSig.func(3, "three");

    oTestSig.show();
}
#endif
