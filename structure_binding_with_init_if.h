#include<map>
#include<iostream>

int main() {
    std::map<int, int> vect{ { 1, 10 },{ 2, 20 },{ 3, 30 },{ 4, 40 } };

    //'if' init statement
    if (auto res = vect.insert({ 5, 50 }); res.second) {
        std::cout << res.first->second << " : " << res.first->first << '\n';
    }

    /*
    'if' init statement with structural binding
    Structural binding working with struct, pairs,
    tupples

    */
    if (auto[it, status] = vect.insert({ 6, 60 }); status) {
        std::cout << it->second << " : " << it->first << '\n';
    }

    //Structural binding with 'struct'
    struct S {
        int i{ 4 };
        int j{ 5 };
    };

    auto[i, j] = S();

    std::cout << "i, j: " << i << ", " << j << '\n';

    //switch init statement
    switch (int x = 7; x) {
    case 7: {
        break;
    }
    }

    return 0;
}
