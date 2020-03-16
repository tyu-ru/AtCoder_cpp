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
    auto n = read<int>();
    auto t = read<int>(3);
    auto l = read<int>(n);
    std::sort(std::begin(l), std::end(l));
    int res = 100000000;
    for (uint32_t i = 0; i < (1 << n * 2); ++i) {
        int r = 0;
        for (auto j : boost::irange(0, 3)) {
            std::vector<int> l_;
            auto x = t[j];
            for (auto k : boost::irange(0, n)) {
                if ((i >> (k * 2)) % 4 == j) l_.push_back(l[k]);
            }
            if (l_.empty()) {
                r = -1;
                break;
            }
            if (std::binary_search(l_.begin(), l_.end(), x)) {
                continue;
            }

            int rr = 100000000;

            for (int i = 1; i < (1 << l_.size()); ++i) {
                int y = 0;
                for (int j = 0; j < l_.size(); ++j) {
                    if (i & (1 << j)) y += l_[j];
                }
                rr = std::min(rr, std::abs(x - y) + (__builtin_popcount(i) - 1) * 10);
            }
            r += rr;
        }
        if (r >= 0) {
            res = std::min(r, res);
        }
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
