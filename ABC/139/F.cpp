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

template <class Integer>
auto boost_irange(Integer last) { return boost::irange(static_cast<Integer>(0), last); }
template <class Integer>
auto boost_irange(Integer first, Integer last) { return boost::irange(first, last); }

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

public:
    class proxy
    {
        std::ostream& cout;

    public:
        proxy() : cout(std::cout) {}
        ~proxy() { cout << std::endl; }
        template <class T>
        proxy& operator,(T&& val)
        {
            cout << val << ' ';
            return *this;
        }
    };

public:
    output() : cout(std::cout)
    {
        cout << std::fixed << std::setprecision(15);
    }
    template <class T>
    proxy operator<<(T&& val)
    {
        cout << val << ' ';
        return {};
    }
};

template <class T, std::size_t n>
class StaticVector : public boost::container::static_vector<T, n>
{
    using Parent = boost::container::static_vector<T, n>;

public:
    // is_constructible_v >= C++17
    template <class... Args, std::enable_if_t<std::is_constructible<Parent, Args&&...>::value, std::nullptr_t> = nullptr>
    StaticVector(Args&&... args) : Parent(std::forward<Args>(args)...) {}
    StaticVector(input& in, std::size_t n_) : Parent(n_)
    {
        for (std::size_t i = 0; i < n_; ++i) in >> static_cast<Parent&>(*this)[i];
    }
};

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

int main()
{
    input in;
    output out;

    int N = in.read<int>();
    StaticVector<std::pair<double, Vector2<int>>, 100> e;
    e.resize(N);
    for (auto& en : e) {
        in >> en.second;
        en.first = std::atan2((double)en.second.y(), (double)en.second.x());
    }

    auto cmp = [](auto&& l, auto&& r) { return l.first < r.first; };
    std::sort(e.begin(), e.end(), cmp);

    Vector2<int> full;
    for (auto& en : e) full += en.second;

    double result = full.norm_sq<double>();
    for (int i : boost_irange(0, N)) {
        Vector2<int> sum1, sum2 = full;
        for (int j : boost_irange(i, N)) {
            // out << i, j;
            sum1 += e[j].second;
            sum2 -= e[j].second;
            result = std::max({result, sum1.norm_sq<double>(), sum2.norm_sq<double>()});
        }
    }

    out << std::sqrt(result);

    return 0;
}
