#include<iostream>
#include<algorithm>

int main() {
    int x = 1;

    /* 
    Below API is added since C++17 it return the
    value as min if val is less than min and max
    when val is more than max and val otherwise.
    So it's a one liner for below code:

    if (x < min)
        return min;
    else if (x > max)
        return max;
    else
        return val;
    */
    std::cout << std::clamp(x, 2, 7) << '\n';
}