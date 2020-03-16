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

template <class T, class... Args>
void out_impl(T&& v, Args&&... args)
{
    std::cout << std::forward<T>(v) << ' ';
    impl(std::forward<Args>(args)...);
}
template <class T>
void out_impl(T&& v) { std::cout << std::forward<T>(v); }
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

// ax+by=gcd(a,b)となるx,yを求める
std::uint64_t extGCD(std::int64_t a, std::int64_t b, std::int64_t& x, std::int64_t& y)
{
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    auto d = extGCD(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

template <std::uint64_t m = 1000000000 + 7>
class ModInt
{
    std::uint64_t v;

public:
    static constexpr auto mod = m;

public:
    ModInt() : v(0){};
    ModInt(std::uint64_t x) : v(x % mod){};
    ModInt(const ModInt&) = default;
    ModInt(ModInt&&) = default;
    ModInt& operator=(const ModInt&) = default;
    ModInt& operator=(ModInt&&) = default;

    std::uint64_t value() const { return v; }

    ModInt& operator+=(const ModInt& rhs)
    {
        v += rhs.v;
        v %= mod;
        return *this;
    }
    ModInt& operator-=(const ModInt& rhs)
    {
        if (v >= rhs.v) {
            v -= rhs.v;
            return *this;
        }
        v = mod - (rhs.v - v);
        return *this;
    }
    ModInt& operator*=(const ModInt& rhs)
    {
        __uint128_t t = v;
        t *= rhs.v;
        v = t % mod;
        return *this;
    }
    friend ModInt operator+(const ModInt& lhs, const ModInt& rhs)
    {
        auto t = lhs;
        t += rhs;
        return t;
    }
    friend ModInt operator-(const ModInt& lhs, const ModInt& rhs)
    {
        auto t = lhs;
        t -= rhs;
        return t;
    }
    friend ModInt operator*(const ModInt& lhs, const ModInt& rhs)
    {
        auto t = lhs;
        t *= rhs;
        return t;
    }

    ModInt power(const uint64_t& p) const
    {
        if (p == 0) return 1;
        if (p == 1) return v;
        auto t = power(p / 2);
        t *= t;
        if (p % 2) t *= v;
        return t;
    }

    ModInt inv() const
    {
        std::int64_t x, y;
        extGCD(v, mod, x, y);
        return x % mod + mod;
    }

    // invers [0,n]
    static const std::vector<ModInt>& inv(std::size_t n)
    {
        static std::vector<ModInt<>> buf(2, 1);
        if (buf.size() > n) {
            return buf;
        }
        auto old = buf.size();
        buf.resize(n + 1, 0);
        for (std::size_t i = old; i <= n; ++i) {
            buf[i] = (mod - mod / i) * buf[mod % i];
        }
        return buf;
    }
};

template <std::uint64_t mod>
std::ostream& operator<<(std::ostream& os, const ModInt<mod>& v)
{
    return os << '[' << v.value() << ']';
}

ModInt<> binomial(ModInt<> n, ModInt<> r)
{
    ModInt<> res = 1;
    auto inv = ModInt<>::inv(r.value());
    for (std::size_t i = 0; i < r.value(); ++i) {
        res *= n - i;
        res *= inv[i + 1];
    }
    return res;
}

using Data = std::array<char, 3>;

std::map<Data, ModInt<>> f(int n)
{
    if (n == 3) {
        std::map<Data, ModInt<>> res;
        char c[4] = {'A', 'T', 'C', 'G'};
        for (auto c1 : c) {
            for (auto c2 : c) {
                for (auto c3 : c) {
                    Data t = {c1, c2, c3};
                    if (t != Data{'A', 'G', 'C'} &&
                        t != Data{'G', 'A', 'C'} &&
                        t != Data{'A', 'C', 'G'}) {
                        res.emplace(t, 1);
                    }
                }
            }
        }
        return res;
    }

    auto check = [](const Data& a, char x) {
        auto c = [](std::array<char, 4> a) {
            return (a[0] == 'A' && a[1] == 'G' && a[2] == 'C') ||
                   (a[1] == 'A' && a[2] == 'G' && a[3] == 'C');
        };
        return !c({a[0], a[1], a[2], x}) &&
               !c({a[1], a[0], a[2], x}) &&
               !c({a[0], a[2], a[1], x}) &&
               !c({a[0], a[1], x, a[2]});
    };
    auto push = [](const Data& arr, char x) {
        return Data{arr[1], arr[2], x};
    };

    std::map<Data, ModInt<>> res;
    for (auto p : f(n - 1)) {
        res[push(p.first, 'A')] += p.second;
        res[push(p.first, 'T')] += p.second;
        // if (!(p.first[1] == 'A' && p.first[2] == 'C')) {
        if (check(p.first, 'G')) {
            res[push(p.first, 'G')] += p.second;
        }
        if (!(p.first[1] == 'A' && p.first[2] == 'G') &&
            !(p.first[1] == 'G' && p.first[2] == 'A') &&
            !(p.first[0] == 'A' && p.first[2] == 'G') &&
            !check(p.first, 'C')) {
            std::string s;
            s += p.first[0];
            s += p.first[1];
            s += p.first[2];
            s += 'C';
            out(s);
        }
        if (check(p.first, 'C')) {
            res[push(p.first, 'C')] += p.second;
        }
    }
    return res;
}

void prog()
{
    auto n = read<int>();
    ModInt<> res = 0;
    for (auto p : f(n)) {
        res += p.second;
    }
    out(res.value());
}

int main()
{
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);
    std::cout << std::fixed << std::setprecision(15);
    prog();
    return 0;
}
