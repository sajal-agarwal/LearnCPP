#ifndef ASYNC_H
#define ASYNC_H

#include <iostream>
#include <future>
#include <chrono>

bool is_prime(unsigned num) {
    for (int i = 2; i < num/2; ++i)
        if (0 == num%i) return false;
    return true;
}




// MAIN.CPP

int main() {
    auto ret = std::async(is_prime, 1500450271);


    switch (ret.wait_for(std::chrono::seconds(1)))  //wait_for() will wait utill the task (is_prime()) completes
                                                    //or 1 second, whichever happens first
    {
    case std::future_status::deferred:
    case std::future_status::timeout:
    {
        std::cout << "Result not ready yet!" << std::endl;
        break;
    }
    case std::future_status::ready:
    {
        std::cout << (ret.get() ? "Prime!" : "Not a Prime!") << std::endl;
        break;
    }
    }
}

#endif
