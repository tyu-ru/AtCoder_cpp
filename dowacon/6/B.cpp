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

class input
{
    std::istream& cin;

public:
    input() : cin(std::cin)
    {
        std::cin.tie(nullptr);
        std::ios::sync_with_stdio(false);
    }

    template <class T>
    inline input& operator>>(T& var)
    {
        cin >> var;
        return *this;
    }
    template <class T>
    inline input& operator,(T& var)
    {
        cin >> var;
        return *this;
    }

    template <class T>
    inline T read()
    {
        T var;
        cin >> var;
        return var;
    }

    template <class InputIterator>
    inline void read(InputIterator head, std::size_t n)
    {
        for (std::size_t i = 0; i < n; ++i) {
            cin >> *head;
            ++head;
        }
    }

    template <class T>
    inline std::vector<T> read(std::size_t n)
    {
        std::vector<T> res;
        res.reserve(n);

        for (std::size_t i = 0; i < n; ++i) {
            T tmp;
            cin >> tmp;
            res.emplace_back(tmp);
        }
        return res;
    }

    template <class T, class F>
    inline void online(std::size_t n, F&& f)
    {
        T var;
        for (std::size_t i = 0; i < n; ++i) {
            cin >> var;
            f(var);
        }
    }
};
template <class T, std::size_t n>
std::istream& operator>>(std::istream& in, std::array<T, n>& var)
{
    for (std::size_t i = 0; i < n; ++i) {
        in >> var[i];
    }
    return in;
}

class output
{
    std::ostream& cout;

    template <class T, class... Args>
    void impl(T&& v, Args&&... args)
    {
        cout << std::forward<T>(v) << ' ';
        impl(std::forward<Args>(args)...);
    }
    template <class T>
    void impl(T&& v)
    {
        cout << std::forward<T>(v);
    }

public:
    output() : cout(std::cout)
    {
        cout << std::fixed << std::setprecision(15);
    }

    template <class... Args>
    void operator()(Args&&... args)
    {
        impl(std::forward<Args>(args)...);
        cout << '\n';
    }
    template <class... Args>
    void noreturn(Args&&... args)
    {
        impl(std::forward<Args>(args)...);
    }

    template <class T>
    void print(const T& container)
    {
        bool first = true;
        for (auto&& x : container) {
            if (!first) {
                cout << ' ';
            }
            cout << x;
            first = false;
        }
        cout << '\n';
    }
};

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
    static std::vector<ModInt> inv(std::size_t n)
    {
        std::vector<ModInt<>> res(n + 1, 0);
        res[0] = 1;
        res[1] = 1;
        for (std::size_t i = 2; i <= n; ++i) {
            res[i] = (mod - mod / i) * res[mod % i];
        }
        return res;
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

std::map<std::set<uint64_t>, ModInt<>> memo;

ModInt<> f(const std::set<uint64_t>& set)
{
    output out;
    // out.print(set);

    if (set.size() == 2) {
        return *set.rbegin() - *set.begin();
    }
    ModInt<> res = 0;

    for (auto x : set) {
        if (x == *set.rbegin()) break;

        auto tmp = set;
        tmp.erase(x);
        auto it = memo.find(tmp);
        if (it != memo.end()) {
            res += it->second;
        } else {
            auto t = f(tmp);
            memo[std::move(tmp)] = t;
            res += t;
        }
        auto it2 = set.upper_bound(x);
        res += *it2 - x;
    }
    return res;
}

void prog()
{
    input in;
    output out;

    auto n = in.read<std::size_t>();
    auto a = in.read<std::uint64_t>(n);

    std::set<uint64_t> s;
    for (auto i : a) s.insert(i);
    out(f(s).value());
}

int main()
{
    prog();
    return 0;
}
