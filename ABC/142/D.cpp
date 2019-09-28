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
        ~proxy() { cout << '\n'; }
        template <class T>
        proxy& operator,(T&& val)
        {
            cout << ' ' << val;
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
        cout << val;
        return {};
    }

    template <class T>
    void print(const T& container)
    {
        bool first = true;
        for (auto&& x : container) {
            if (!first) {
                cout << ' ';
                first = false;
            }
            cout << x;
        }
    }
};

std::uint64_t gcd(std::uint64_t x, std::uint64_t y)
{
    if (x < y) std::swap(x, y);
    auto z = x % y;
    if (z == 0) return y;
    return gcd(y, x % y);
}

std::size_t prime_factor_count(std::uint64_t x)
{
    std::size_t res = 0;
    for (std::uint64_t i = 2; i * i <= x; ++i) {
        bool f = false;
        while (x % i == 0) {
            x /= i;
            f = true;
        }
        if (f) ++res;
    }
    if (x != 1) ++res;
    return res;
}

int main()
{
    input in;
    output out;

    std::uint64_t A, B;
    in >> A, B;
    out << prime_factor_count(gcd(A, B)) + 1;

    return 0;
}
