#pragma once

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
    ModInt(std::uint64_t x) : v(x % mod){};
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
