const double PI1 = 3.14159;
constexpr double PI2 = 3.14159;

int ARRAY_LEN = 7;
const int ARRAY_LEN1 = 7;   //may be a compile time constant
constexpr int ARRAY_LEN2 = 7;   //compile time constant

template<typename T, int N>
struct VarArray {
    T arr[N];

    T& operator[](int i) {
        return arr[i];
    }
};

class ConstexprTest {
public:
    static int ARRAY_LEN;
};

// Pass by value
constexpr float exp(float x, int n)
{
    return n == 0 ? 1 :
        n % 2 == 0 ? exp(x * x, n / 2) :
        exp(x * x, (n - 1) / 2) * x;
}

// Pass by reference
constexpr float exp2(const float& x, const int& n)
{
    return n == 0 ? 1 :
        n % 2 == 0 ? exp2(x * x, n / 2) :
        exp2(x * x, (n - 1) / 2) * x;
}

// MAIN.CPP

int ConstexprTest::ARRAY_LEN = 7;

int main () {
    constexpr double area_of_1 = PI2*PI2;
#if 0
    constexpr double area_of_2 = 2*PI1*PI1; // error: the value of 'PI1' is not usable in a constant expression
#endif

    int arr[ConstexprTest::ARRAY_LEN];
    arr[0] = 2;
    arr[1] = 3;
    int arr1[(int)(PI1*ARRAY_LEN1)];   // no error, some compiler might through error
    int arr2[(int)(PI2*ARRAY_LEN2)];

    struct VarArray<int, 34> varArr;
    struct VarArray<int, ARRAY_LEN1> varArr1;
    struct VarArray<int, ARRAY_LEN2> varArr2;
#if 0
    struct VarArray<int, ARRAY_LEN> varArr3;    //error: the value of 'ARRAY_LEN' is not usable in a constant expression
#endif
#if 0
    constexpr float res = exp(PI1, 4);  // error: the value of 'PI1' is not usable in a constant expression
#endif
}
