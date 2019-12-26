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
        cout << '\n';
    }
};

class Tree
{
    std::vector<std::vector<int>> tree;

public:
    Tree(int n) : tree(n) {}

    void addEdge(int a, int b)
    {
        a -= 1;
        b -= 1;
        tree[a].push_back(b);
        tree[b].push_back(a);
    }

    template <class F, class T>
    void dfs(F func, T takeover, int node, int parent = -1) const
    {
        auto tak = func(node, takeover);
        for (int n : tree[node]) {
            if (n == parent) continue;
            dfs(func, tak, n, node);
        }
    }

    std::vector<int> distance(int node) const
    {
        std::vector<int> res(tree.size());
        dfs([&](int n, int t) { res[n] = t; return t + 1; }, 0, node);
        return res;
    }
};

void prog()
{
    input in;
    output out;
    int n, u, v;
    in >> n, u, v;

    Tree tree(n);
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        in >> a, b;
        tree.addEdge(a, b);
    }
    auto ud = tree.distance(u - 1);
    auto vd = tree.distance(v - 1);
    int res = -1;
    for (int i : boost::irange(0, n)) {
        if (ud[i] < vd[i]) {
            res = std::max(res, vd[i]);
        }
    }
    out, res - 1;
}

int main()
{
    prog();
    return 0;
}
