#ifndef ASYNC_H
#define ASYNC_H

#include <iostream>
#include <future>
#include <chrono>
#include <algorithm>
#include <numeric>

bool is_prime(unsigned num) {
    for (size_t i = 2; i < num/2; ++i)
        if (0 == num%i) return false;
    return true;
}


auto callAsync() {
    auto ret = std::async(is_prime, 1500450271);

    // The 'ret's destructor is blocking call that's why if we don't assign the return
    // value of 'std::async' call the program will wait here till the execution completes
    // otherwire whereever the 'ret' is going to be destructed like at end of scope.
    // One exception to this is when 'ret' is returned by the function. In this scenerio
    // the program will wait till the destruction of the future variable which is going
    // to accept the value of 'ret'

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

    return ret;
}

// A more usefull example of std::async() would be finding the sum of all the elements a integer array
template<typename T, int N>
int sum(T(&arr)[N], size_t start = 0, size_t end = N - 1) {
    if (end - start < 3) {
        auto res =  std::accumulate(std::begin(arr) + start, std::begin(arr) + end + 1, 0);
        return res;
    }
    else {
        auto mid = start + (end - start) / 2;
        return sum(arr, start, mid) + sum(arr, mid + 1, end);
    }
}

template<typename T, int N, typename = std::enable_if<std::is_integral<T>::value>::type>
T parallel_sum(T(&arr)[N], size_t start = 0, size_t end = N - 1) {
    if (end - start < 1000) {
        return std::accumulate(std::begin(arr) + start, std::begin(arr) + end + 1, 0);
    }
    else {
        size_t mid = start + (end - start) / 2;
        auto res1 = std::async(std::launch::async, parallel_sum<T, N>, std::ref(arr), start, mid);
#if 0 // below can replace above line
        auto res1 = std::async([&arr, start, mid]() {return parallel_sum(arr, start, mid); });
#endif
        auto res2 = parallel_sum(arr, mid + 1, end);
        return res2 + res1.get();
    }
}

// MAIN.CPP

int main() {
    constexpr const size_t ARR_LEN = 100000;
    unsigned arr[ARR_LEN];
    for (size_t i = 0; i < ARR_LEN; ++i) {
        arr[i] = std::rand()%5;
    }
    auto st = std::chrono::system_clock::now();
    std::cout << "Sum is " << parallel_sum(arr) << std::endl;
    std::cout << "Time consumed in sum(): " << std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now() - st).count() << std::endl;
#if 0
    auto ret = callAsync(); // here as the future value from callAsync() function is assigned to 'ret'
                            // the program will keep going till the end of main function as that's where
                            // 'ret' is going to be destructed and program will start waiting for the same

    std::cout << "Out of callAsync() function!" << std::endl;
    std::cout << "Result is " << std::boolalpha << ret.get() << std::endl; // here get is waiting call
#endif
}

#endif
