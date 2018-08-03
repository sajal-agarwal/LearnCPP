#if 0
#include <iostream>
#include <functional>
#include <test.h>

template<typename Func, typename ...Args>
struct temp_func {
    temp_func(Func &&func, Args&&... args): f(func), t(std::forward<Args...>(args...)) {
    }

    void call() {
        execute(std::make_index_sequence<std::tuple_size_v<decltype(t)>>());
    }

    template<size_t... I>
    void execute(std::index_sequence<I...> Is) {
#if 0
        f(std::forward<Args>(std::get<I>(t))...);
#endif
        std::invoke(f, std::move(std::get<I>(t))...);
    }

private:
    std::tuple<std::decay_t<Args>...> t;
    //std::tuple<Args...> t;
    std::function<void(Args&&...)> f;
};

void f(const int &x) {
    std::cout << x << '\n';
}

void f2(int &x) {
    x = 3;
}

int main() {
    int v = 0, u = 0;

    temp_func caller(f, 9);
    caller.call();

    temp_func caller2(f2, std::ref(v));
    caller2.call();

#if 0
    temp_func<std::function<void(int&)>, int&> caller3(f2, u);
    caller3.call();

    temp_func caller4(f2, v);
    caller4.call();
#endif

    std::cout << "v = " << v << "\tu = " << u << std::endl;
}
#else
#include<iostream>

int main() {
    char line[256];
    std::cin.getline(line, 256);
    std::cout << line << std::endl;
}

#endif
