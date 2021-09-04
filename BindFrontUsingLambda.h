#pragma once
#include<iostream>


template<typename Func, typename ...Params>
auto bindFront(Func &&func, Params&&...args) {
    /* Type should not be specified in lambdda capture
       func in 'func = std::forward<Func>(func)' and
       args in '...args = std::forward<Args>(args)'
       can be named anything, just imagin a type before
       there names and below will make sense
    */
    return [func = std::forward<Func>(func), ...args = std::forward<Params>(args)](auto&& ...params) {
        return func(args..., std::forward<decltype(params)>(params)...);
    };
}

/*
* No template version of bind
*/
auto bind(auto&& fn, auto&&...args)
{
    return[fn = std::forward<decltype(fn)>(fn), ...args = std::forward<decltype(args)>(args)](
        auto&&...pargs)->decltype(auto) {
        return fn(args..., std::forward<decltype((pargs))>(pargs)...);
    };
}

/*
* bind function with functor. This is what
* labdas do for us in above code.
* Here we are using std::tuple to capture the
* binded arguments and using std:index_sequence
* to retreive those binded arguments.
*/
template<typename Fn, typename...Args>
class Functor
{
    Fn m_fn;
    std::tuple<Args...> m_captures;
public:
    explicit Functor(Fn&& fn, Args&&...args)
        : m_fn{ std::forward<Fn>(fn) }
        , m_captures{ std::make_tuple(std::forward<Args>(args)...) }
    {
    }

    void print_captures() const
    {
        print_captures(std::make_index_sequence<std::tuple_size_v<std::tuple<Args...>>>());
    }

    template<size_t...I>
    void print_captures([[maybe_unused]] std::index_sequence<I...>) const
    {
        ((std::cout << std::get<I>(m_captures) << ' '), ...);
    }

    template<typename...Params>
    auto operator()(Params&&...args) const
    {
        return invoker(std::make_index_sequence<sizeof...(args)>(), std::forward<Params>(args)...);
    }

private:
    template<size_t...I, typename...Params>
    auto invoker([[maybe_unused]] std::index_sequence<I...>, Params&&...args) const
    {
        return m_fn(std::get<I>(m_captures)..., std::forward<decltype(args)>(args)...);
    }
};

auto bindWithFunctor(auto&& fn, auto&&...args)
{
    return Functor(std::forward<decltype(fn)>(fn), std::forward<decltype(args)>(args)...);
}



int add(const int a, const int b, const int c) {
    return (a + b + c);
}

int main() {
    std::cout << bindFront(add, 2, 3)(6) << '\n';
}
