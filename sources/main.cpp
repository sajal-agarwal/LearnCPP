/* TOPICS TO BE COVERED
*
*
*
*/
#if 1
#include<iostream>
#include<vector>

extern template class std::vector<int>;
void pushint(int e);

int main () {
    pushint(9);
    std::vector<int> intVect;
    intVect.push_back(7);
}
#endif
