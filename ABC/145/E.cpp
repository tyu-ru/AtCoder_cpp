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
    int N, T;
    in >> N, T;
    std::vector<std::pair<int, int>> C;
    for (int i = 0; i < N; ++i) {
        int a, b;
        in >> a, b;
        C.push_back(std::make_pair(a, b));
    }
    std::sort(std::begin(C), std::end(C));
    // dp[i+1][t] ... max manxoku [0,i] cuisine time < t
    Map2d<int> dp(N + 1, T);

    for (auto i : boost::irange(0, N)) {
        for (auto t : boost::irange(0, T)) {
            if (t >= C[i].first)
                dp.at(i + 1, t) = std::max(dp.at(i, t - C[i].first) + C[i].second, dp.at(i, t));
            else
                dp.at(i + 1, t) = dp.at(i, t);
        }
    }

    int res = 0;
    for (int i : boost::irange(1, N + 1)) {
        res = std::max(res, dp.at(i - 1, T - 1) + C[i - 1].second);
    }
    out(res);
}

int main()
{
    prog();
    return 0;
}
