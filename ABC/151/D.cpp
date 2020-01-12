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

void prog()
{
    input in;
    output out;

    int h, w;
    in >> h, w;

    std::array<std::array<bool, 20>, 20> map;
    for (auto j : boost::irange(0, h)) {
        for (auto i : boost::irange(0, w)) {
            map[j][i] = in.read<char>() == '.';
        }
    }

    int res = 0;
    for (auto j : boost::irange(0, h)) {
        for (auto i : boost::irange(0, w)) {
            if (!map[j][i]) continue;
            std::array<std::array<bool, 20>, 20> d = map;
            std::queue<std::tuple<int, int, int>> q;
            q.emplace(i, j, 0);
            while (!q.empty()) {
                int i, j, dd;
                std::tie(i, j, dd) = q.front();
                q.pop();
                res = std::max(res, dd);
                d[j][i] = false;
                int di[] = {1, 0, -1, 0}, dj[] = {0, 1, 0, -1};
                for (auto k : boost::irange(0, 4)) {
                    int ni = i + di[k], nj = j + dj[k];
                    if (ni < 0 || w <= ni || nj < 0 || h <= nj) continue;
                    if (d[nj][ni]) {
                        q.emplace(ni, nj, dd + 1);
                        d[nj][ni] = false;
                    }
                }
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
