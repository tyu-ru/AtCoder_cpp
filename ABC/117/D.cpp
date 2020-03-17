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

std::uint64_t max(std::uint64_t n, const std::array<std::uint64_t, 64>& b, std::uint64_t i)
{
    std::uint64_t res = 0;
    for (auto j : boost::irange(0ul, i)) {
        res += std::max(b[j], n - b[j]) * (1ul << j);
    }
    return res;
}

std::uint64_t f(std::uint64_t n, const std::array<std::uint64_t, 64>& b, std::uint64_t k, std::uint64_t i, std::uint64_t x)
{
    if (i == 0) {
        if (x < k) {
            return std::max(b[0], n - b[0]);
        }
        return b[0];
    }
    std::uint64_t res = 0;
    if (k & (1ul << i)) {
        res = std::max(res, max(n, b, i) + b[i] * (1ul << i));
        res = std::max(res, f(n, b, k, i - 1, x | (1ul << i)) + (n - b[i]) * (1ul << i));
        return res;
    }
    res = std::max(res, f(n, b, k, i - 1, x) + b[i] * (1ul << i));
    if ((x | (1ul << i)) <= k) {
        res = std::max(res, f(n, b, k, i - 1, x | (1ul << i)) + (n - b[i]) * (1ul << i));
    }
    return res;
}

void prog()
{
    std::uint64_t n, k;
    std::cin >> n >> k;
    auto a = read<std::uint64_t>(n);

    std::array<std::uint64_t, 64> b{{}};
    for (auto& x : b) x = 0;
    for (auto x : a) {
        for (auto i : boost::irange(0, 64)) {
            if ((x >> i) & 1) ++b[i];
        }
    }
    out(f(n, b, k, 63, 0));
}

int main()
{
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);
    std::cout << std::fixed << std::setprecision(15);
    prog();
    return 0;
}
