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
public:
    input()
    {
        std::cin.tie(nullptr);
        std::ios::sync_with_stdio(false);
    }

    template <class T>
    inline input& operator>>(T& var) { return std::cin >> var, *this; }
    template <class T>
    inline input& operator,(T& var) { return *this >> var; }

    template <class T>
    inline T read()
    {
        T var;
        std::cin >> var;
        return var;
    }

    template <class InputIterator>
    inline void read(InputIterator head, std::size_t n)
    {
        for (std::size_t i = 0; i < n; ++i) {
            std::cin >> *head;
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
            std::cin >> tmp;
            res.emplace_back(tmp);
        }
        return res;
    }

    template <class T, class F>
    inline void online(std::size_t n, F&& f)
    {
        T var;
        for (std::size_t i = 0; i < n; ++i) {
            std::cin >> var;
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

void prog()
{
    input in;
    output out;
    int x, y, z, k;
    in >> x, y, z, k;
    auto a = in.read<std::uint64_t>(x);
    auto b = in.read<std::uint64_t>(y);
    auto c = in.read<std::uint64_t>(z);
    std::sort(std::begin(a), std::end(a), std::greater<>());
    std::sort(std::begin(b), std::end(b), std::greater<>());
    std::sort(std::begin(c), std::end(c), std::greater<>());
    a.resize(std::min(k, x));
    b.resize(std::min(k, y));
    c.resize(std::min(k, z));
    std::vector<std::uint64_t> ab, abc;
    ab.reserve(k * k);
    for (auto x : a)
        for (auto y : b) ab.push_back(x + y);
    std::sort(std::begin(ab), std::end(ab), std::greater<>());
    ab.resize(std::min<std::size_t>(k, ab.size()));

    abc.reserve(k * k);
    for (auto xy : ab)
        for (auto z : c) abc.push_back(xy + z);
    std::sort(std::begin(abc), std::end(abc), std::greater<>());
    abc.resize(k);
    for (auto x : abc) {
        out(x);
    }
}

int main()
{
    prog();
    return 0;
}
