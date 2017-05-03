#include<iostream>
#include <fstream>
#include<cstdio>



int main () {
    freopen("../LearnCPP/in.txt", "r", stdin);
    int n;
    std::cin >> n;
    std::cout << n << std::endl;
    for (int i = 0; i < n; ++i) {
        int m;
        std::cin >> m;
        std::cout << m << std::endl;
        for (int j = 0; j < m; ++j) {
            int elem;
            std::cin >> elem;
            std::cout << elem << ((j < m - 1) ? " " : "");
        } std::cout << std::endl;
    } std::cout << std::endl;
}
