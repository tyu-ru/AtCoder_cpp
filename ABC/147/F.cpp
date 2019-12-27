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

public:
    template <bool nl>
    class proxy
    {
        std::ostream& cout;

    public:
        proxy() : cout(std::cout) {}
        ~proxy() { final(); }
        template <class T>
        proxy& operator,(T&& val)
        {
            cout << ' ' << val;
            return *this;
        }
        template <bool f = nl>
        auto final() -> std::enable_if_t<f> { cout << '\n'; }
        template <bool f = nl>
        auto final() -> std::enable_if_t<!f> {}
    };

public:
    output() : cout(std::cout)
    {
        cout << std::fixed << std::setprecision(15);
    }

    template <class T>
    proxy<true> operator,(T&& val)
    {
        cout << val;
        return {};
    }
    proxy<false> noreturn() { return {}; }

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
    }
};

void prog()
{
    input in;
    output out;

    int64_t n, x, d;
    in >> n, x, d;

    if (d == 0) {
        if (x == 0)
            out, 1;
        else
            out, n + 1;
        return;
    }

    if (d < 0) {
        d = -d;
        x = -x;
    }

    // range[l,r]
    auto pick = [](auto n, auto k) {
        std::pair<int64_t, int64_t> res;
        res.first = k * (0 + k - 1) / 2;
        res.second = k * (n - 1 + n - k) / 2;
        return res;
    };

    std::map<int64_t, std::map<int64_t, int64_t>> s;
    for (auto k : boost::irange<int64_t>(0, n + 1)) {
        int64_t c = x * k;
        int64_t m = ((c % d) + d) % d;
        int64_t y = (c - m) / d;
        auto range = pick(n, k);
        s[m][y + range.first] += 1;
        s[m][y + range.second + 1] -= 1;
    }

    int64_t res = 0;
    for (auto&& v : s) {
        int64_t c = 0, p = 0;
        for (auto&& m : v.second) {
            if (c == 0) {
                p = m.first;
            }
            c += m.second;
            if (c == 0) {
                res += m.first - p;
            }
        }
    }
    out, res;
}

int main()
{
    prog();
    return 0;
}
