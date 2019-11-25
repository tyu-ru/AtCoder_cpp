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

int main()
{
    input in;
    output out;

    auto N = in.read<int>();
    std::vector<std::tuple<int, int, int>> E(N - 1);
    std::vector<std::vector<std::tuple<int, int, int>>> G(N);
    for (auto i : boost::irange(0, N - 1)) {
        int a, b;
        in >> a, b;
        a -= 1;
        b -= 1;
        E[i] = std::make_tuple(a, b, 0);
        G[a].push_back(std::make_tuple(b, i, -1));
    }
    int c = std::max_element(G.begin() + 1, G.end(), [](auto& l, auto& r) { return l.size() < r.size(); })->size();
    c = std::max<int>(c + 1, G[0].size());

    std::queue<std::pair<int, int>> q;
    q.push(std::make_pair(0, -1));
    while (!q.empty()) {
        int c_ = 1;
        for (auto&& b : G[q.front().first]) {
            if (c_ == q.front().second) c_++;
            std::get<2>(E[std::get<1>(b)]) = c_;
            q.push(std::make_pair(std::get<0>(b), c_));
            c_++;
        }
        q.pop();
    }

    out << c;
    for (auto&& e : E) {
        out << std::get<2>(e);
    }
    return 0;
}
