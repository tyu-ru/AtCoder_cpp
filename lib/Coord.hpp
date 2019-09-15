#pragma once
#include <ios>

template <class T, std::size_t n>
class Vector
{
public:
    T dat[n] = {};

public:
    T& operator[](std::size_t i) { return dat[i]; }
    const T& operator[](std::size_t i) const { return dat[i]; }

    T* begin() { return dat; }
    const T* begin() const { return dat; }
    T* end() { return dat + n; }
    const T* end() const { return dat + n; }

    template <class U = T>
    U norm_sq() const
    {
        U res = 0;
        for (auto x : dat) res += static_cast<U>(x) * x;
        return res;
    }
    template <class U = T>
    U norm() const
    {
        return std::sqrt(norm_sq<U>());
    }

    Vector operator-() const { return *this * -1; }

    Vector& operator+=(const Vector& rhs)
    {
        for (std::size_t i = 0; i < n; ++i) dat[i] += rhs.dat[i];
        return *this;
    }
    Vector& operator-=(const Vector& rhs)
    {
        for (std::size_t i = 0; i < n; ++i) dat[i] -= rhs.dat[i];
        return *this;
    }

    Vector& operator*=(const T& rhs)
    {
        for (std::size_t i = 0; i < n; ++i) dat[i] *= rhs;
        return *this;
    }
    Vector& operator/=(const T& rhs)
    {
        for (std::size_t i = 0; i < n; ++i) dat[i] /= rhs;
        return *this;
    }

    friend Vector operator+(const Vector& lhs, const Vector& rhs)
    {
        Vector res;
        for (std::size_t i = 0; i < n; ++i) res.dat[i] = lhs.dat[i] + rhs.dat[i];
        return res;
    }
    friend Vector operator-(const Vector& lhs, const Vector& rhs)
    {
        Vector res;
        for (std::size_t i = 0; i < n; ++i) res.dat[i] = lhs.dat[i] - rhs.dat[i];
        return res;
    }
};

template <class T, std::size_t n>
inline std::istream& operator>>(std::istream& in, Vector<T, n>& val)
{
    for (std::size_t i = 0; i < n; ++i) {
        in >> val[i];
    }
    return in;
}
template <class T, std::size_t n>
inline std::ostream& operator<<(std::ostream& out, const Vector<T, n>& val)
{
    out << "(";
    for (std::size_t i = 0; i < n; ++i) {
        out << val[i];
        if (i != n - 1) out << ", ";
    }
    out << ")";
    return out;
}

template <class T>
class Vector2 : public Vector<T, 2>
{
public:
    T& x() { return (*this)[0]; }
    const T& x() const { return (*this)[0]; }
    T& y() { return (*this)[1]; }
    const T& y() const { return (*this)[1]; }
};
template <class T>
class Vector3 : public Vector<T, 3>
{
public:
    T& x() { return (*this)[0]; }
    const T& x() const { return (*this)[0]; }
    T& y() { return (*this)[1]; }
    const T& y() const { return (*this)[1]; }
    T& z() { return (*this)[2]; }
    const T& z() const { return (*this)[2]; }
};

template <class T, std::size_t n>
inline T manhattan_distance(const Vector<T, n>& lhs, const Vector<T, n>& rhs)
{
    T res = 0;
    for (std::size_t i = 0; i < n; ++i) {
        res += std::abs(lhs[i] - rhs[i]);
    }
    return res;
}
