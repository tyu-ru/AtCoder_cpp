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

    int w, h;
    in >> h, w;
    std::size_t max = 0;
    Map2d<int> m(w, h, [&] {
        auto a = in.read<int>(w * h);
        auto b = in.read<int>(w * h);
        for (std::size_t i = 0; i < w * h; ++i) {
            a[i] = std::abs(a[i] - b[i]);
            max = std::max((int)max, a[i]);
        }
        return a;
    }());

    max = max * (w + h) + 1;
    Map2d<std::vector<bool>> dp(w, h, std::vector<bool>(max, false));
    dp.at(0, 0)[m.at(0, 0)] = true;
    for (auto j : boost::irange<std::size_t>(0, h)) {
        for (auto i : boost::irange<std::size_t>(0, w)) {
            if (i == 0 && j == 0) continue;
            auto& dp_ = dp.at(i, j);
            for (auto k : boost::irange<std::size_t>(0, max)) {
                if (i != 0 && std::abs(dp.at(i - 1, j)[k])) {
                    dp_[k + m.at(i, j)] = true;
                    dp_[std::abs((int)k - m.at(i, j))] = true;
                }
                if (j != 0 && std::abs(dp.at(i, j - 1)[k])) {
                    dp_[k + m.at(i, j)] = true;
                    dp_[std::abs((int)k - m.at(i, j))] = true;
                }
            }
        }
    }
    for (auto i : boost::irange<std::size_t>(0, max)) {
        if (dp.at(w - 1, h - 1)[i]) {
            out, i;
            return;
        }
    }
}

int main()
{
    prog();
    return 0;
}
