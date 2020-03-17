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

std::pair<std::int64_t, uint64_t> dp[10100][10100];

void prog()
{
    std::uint64_t n, k;
    std::cin >> n >> k;
    std::vector<std::uint64_t> sushi;
    std::map<int, std::uint64_t> top;
    for (auto s : read<std::pair<std::uint64_t, std::uint64_t>>(n)) {
        auto it = top.find(s.first);
        if (it != top.end()) {
            if (it->second < s.second) {
                std::swap(it->second, s.second);
            }
            sushi.push_back(s.second);
        } else {
            top[s.first] = s.second;
        }
    }
    std::vector<std::uint64_t> top2;
    for (auto s : top) {
        top2.push_back(s.second);
    }
    std::sort(std::begin(top2), std::end(top2));
    std::sort(std::begin(sushi), std::end(sushi), std::greater<>());
    sushi.resize(std::min(sushi.size(), k));

    std::uint64_t sum = 0;
    for (auto s : sushi) {
        sum += s;
    }
    std::uint64_t i = 0;
    for (auto j : boost::irange(0ul, k - sushi.size())) {
        sum += top2.back();
        top2.pop_back();
        ++i;
    }
    std::uint64_t res = sum + i * i;
    while (sushi.size() && top2.size()) {
        sum += top2.back() - sushi.back();
        top2.pop_back();
        sushi.pop_back();
        ++i;
        res = std::max(res, sum + i * i);
    }
    out(res);
}

int main()
{
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);
    std::cout << std::fixed << std::setprecision(15);
    prog();
    return 0;
}
