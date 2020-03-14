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

class UnionFind
{
    std::vector<std::size_t> t;
    std::vector<std::size_t> s;

public:
    UnionFind(std::size_t n) : t(n), s(n, 1)
    {
        for (std::size_t i = 0; i < n; ++i) t[i] = i;
    }

    void unite(std::size_t a, std::size_t b)
    {
        if (root(a) == root(b)) return;
        auto tmp = s[root(a)];
        s[root(a)] = 0;
        s[root(b)] += tmp;
        t[root(a)] = root(b);
    }
    std::size_t root(std::size_t a)
    {
        if (t[a] == a) return a;
        auto res = root(t[a]);
        t[a] = res;
        return res;
    }
    std::size_t size(std::size_t a)
    {
        return s[root(a)];
    }
};

void prog()
{
    input in;
    output out;

    int n, m, k;
    in >> n, m, k;
    UnionFind net(n);
    std::vector<std::set<int>> ff_block(n);
    for (int i = 0; i < m; ++i) {
        int a, b;
        in >> a, b;
        --a, --b;
        net.unite(a, b);
        ff_block[a].insert(b);
        ff_block[b].insert(a);
    }
    for (int i = 0; i < k; ++i) {
        int c, d;
        in >> c, d;
        --c, --d;
        ff_block[c].insert(d);
        ff_block[d].insert(c);
    }

    for (int i = 0; i < n; ++i) {
        int res = 0;
        for (auto&& it : ff_block[i]) {
            if (net.root(i) == net.root(it)) ++res;
        }
        out.noreturn(net.size(i) - res - 1);
        out.noreturn(" ");
    }
}

int main()
{
    prog();
    return 0;
}
