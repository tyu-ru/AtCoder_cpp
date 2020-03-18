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

void prog()
{
    std::uint64_t n, m, k;
    std::cin >> n >> m >> k;
    ModInt<> res = 0;
    for (auto i : boost::irange(1ul, n)) {
        res += i * (n - i) * m * m;
    }
    for (auto i : boost::irange(1ul, m)) {
        res += i * (m - i) * n * n;
    }
    res *= binomial(n * m - 2, k - 2);
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
