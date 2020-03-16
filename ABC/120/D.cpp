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

class UnionFind
{
    std::vector<std::size_t> t;
    std::vector<std::size_t> s;

public:
    UnionFind(std::size_t n) : t(n), s(n, 1)
    {
        for (std::size_t i = 0; i < n; ++i) t[i] = i;
    }

    void unite(std::size_t a, std::size_t b)
    {
        if (root(a) == root(b)) return;
        auto tmp = s[root(a)];
        s[root(a)] = 0;
        s[root(b)] += tmp;
        t[root(a)] = root(b);
    }
    std::size_t root(std::size_t a)
    {
        if (t[a] == a) return a;
        auto res = root(t[a]);
        t[a] = res;
        return res;
    }
    std::size_t size(std::size_t a)
    {
        return s[root(a)];
    }
};

void prog()
{
    std::uint64_t n, m;
    std::cin >> n >> m;
    UnionFind islands(n);
    auto bridge = read<std::pair<std::uint64_t, std::uint64_t>>(m);
    std::vector<std::uint64_t> res;
    res.push_back(n * (n - 1) / 2);
    for (auto b : bridge | boost::adaptors::reversed) {
        if (islands.root(b.first - 1) == islands.root(b.second - 1)) {
            res.push_back(res.back());
            continue;
        }
        res.push_back(res.back() - islands.size(b.first - 1) * islands.size(b.second - 1));
        islands.unite(b.first - 1, b.second - 1);
    }
    res.pop_back();
    for (auto r : res | boost::adaptors::reversed) {
        out(r);
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
