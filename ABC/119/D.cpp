#include <iostream>
#include <iomanip>
#include <cmath>
#include <functional>
#include <algorithm>
#include <numeric>
#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <deque>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <boost/range/irange.hpp>
#include <boost/range/adaptor/reversed.hpp>
#include <boost/container/static_vector.hpp>
#include <boost/utility/string_ref.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/math/common_factor_rt.hpp>

template <class... Args>
struct tuple_input_impl;
template <std::size_t i, std::size_t... tail>
struct tuple_input_impl<std::index_sequence<i, tail...>>
{
    template <class... Args>
    static void f(std::tuple<Args...>& x)
    {
        std::cin >> std::get<i>(x);
        tuple_input_impl<std::index_sequence<tail...>>::f(x);
    }
};
template <>
struct tuple_input_impl<std::index_sequence<>>
{
    static void f(...) {}
};

template <class... Args>
std::istream& operator>>(std::istream& in, std::tuple<Args...>& x)
{
    tuple_input_impl<std::index_sequence_for<Args...>>::f(x);
    return in;
}
template <class T1, class T2>
std::istream& operator>>(std::istream& in, std::pair<T1, T2>& x) { return in >> x.first >> x.second; }

template <class T>
T read()
{
    T res;
    std::cin >> res;
    return res;
}
template <class T>
std::vector<T> read(std::size_t n)
{
    std::vector<T> res(n);
    for (std::size_t i = 0; i < n; ++i) std::cin >> res[i];
    return res;
}

template <class T>
void out_impl(T&& v) { std::cout << std::forward<T>(v); }
template <class T, class... Args>
void out_impl(T&& v, Args&&... args)
{
    std::cout << std::forward<T>(v) << ' ';
    out_impl(std::forward<Args>(args)...);
}
template <class... Args>
void out(Args&&... args)
{
    out_impl(std::forward<Args>(args)...);
    std::cout << '\n';
}
template <class... Args>
void out_noreturn(Args&&... args) { out_impl(std::forward<Args>(args)...); }

template <class T>
void print(const T& container)
{
    bool first = true;
    for (auto&& x : container) {
        if (!first) std::cout << ' ';
        std::cout << x;
        first = false;
    }
    std::cout << '\n';
}

void prog()
{
    int a, b, q;
    std::cin >> a >> b >> q;
    auto s = read<std::uint64_t>(a);
    auto t = read<std::uint64_t>(b);

    auto abs = [](std::uint64_t a, std::uint64_t b) -> std::uint64_t {
        if (a < b) return b - a;
        return a - b;
    };
    auto f = [&](std::vector<std::uint64_t>& s, std::uint64_t x) -> std::vector<std::uint64_t> {
        auto it = std::lower_bound(s.begin(), s.end(), x);
        if (it == s.end()) {
            return {s.back()};
        }
        if (it == s.begin()) {
            return {s.front()};
        }
        return {*it, *(it - 1)};
    };

    for (auto i : boost::irange(0, q)) {
        auto x = read<std::uint64_t>();
        std::uint64_t res = ~std::uint64_t{0};
        {
            auto n = f(s, x);
            for (auto y : n) {
                for (auto z : f(t, y)) {
                    res = std::min(res, abs(y, x) + abs(y, z));
                }
            }
        }
        {
            auto n = f(t, x);
            for (auto y : n) {
                for (auto z : f(s, y)) {
                    res = std::min(res, abs(y, x) + abs(y, z));
                }
            }
        }
        out(res);
    }
}

int main()
{
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);
    std::cout << std::fixed << std::setprecision(15);
    prog();
    return 0;
}
