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

void prog()
{
    input in;
    output out;

    int n, p;
    std::string s;
    in >> n, p, s;

    // std::set<std::pair<int, int>> r;
    if (p == 2 || p == 5) {
        std::uint64_t res = 0;
        for (int i = 0; i < n; ++i) {
            if (s[i] % p == 0) {
                res += i + 1;
            }
        }
        out(res);
        return;
    }

    std::uint64_t res = 0;
    for (int i = 0; i < n; ++i) {
        int r = 0;
        for (int j = i; j < n; ++j) {
            r = (r * 10 + s[j]) % p;
            if (r == 0) {
                ++res;
            }
        }
    }
    out(res);
}

int main()
{
    prog();
    return 0;
}
