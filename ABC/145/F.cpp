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
    }
};

template <class T>
class Map2d
{
    std::size_t w = 0, h = 0;
    std::vector<T> m;

public:
    Map2d(std::size_t w_, std::size_t h_, const T& v = T())
    {
        w = w_;
        h = h_;
        m.resize(w * h, v);
    }
    Map2d(std::size_t w_, std::size_t h_, std::vector<T>&& v)
    {
        w = w_;
        h = h_;
        m = std::move(v);
        m.resize(w * h);
    }

    T& at(std::size_t i, std::size_t j)
    {
        return m[i + j * w];
    }
};

void prog()
{
    input in;
    output out;

    int n, k;
    in >> n, k;
    auto h = in.read<int>(n);

    if (n == k) {
        out(0);
        return;
    }

    // dp[i][j] : i番目まで　i番を残す　j+1個残す cost
    Map2d<uint64_t> dp(n, n - k, std::numeric_limits<uint64_t>::max());
    for (int i : boost::irange(0, n)) dp.at(i, 0) = h[i];

    for (int j : boost::irange(1, n - k)) {
        for (int i : boost::irange(j, n)) {
            auto m = std::numeric_limits<uint64_t>::max();
            for (int k : boost::irange(j - 1, i)) {
                m = std::min(m, std::max(0, h[i] - h[k]) + dp.at(k, j - 1));
            }
            dp.at(i, j) = m;
            // out(i, j, dp.at(i, j));
        }
    }
    auto res = std::numeric_limits<uint64_t>::max();
    for (int i : boost::irange(n - k - 1, n)) {
        res = std::min(res, dp.at(i, n - k - 1));
    }
    out(res);
}

int main()
{
    prog();
    return 0;
}
