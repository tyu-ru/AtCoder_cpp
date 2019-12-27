#pragma once

template <std::uint64_t mod = 1000000000 + 7>
class ModInt
{
    std::uint64_t v;

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
        std::uint64_t t = rhs.v - v;
        v = mod - t;
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
};
