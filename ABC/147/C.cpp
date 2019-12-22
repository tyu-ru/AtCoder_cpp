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
    std::vector<std::map<int, bool>> test(N);
    for (auto i : boost::irange(0, N)) {
        auto n = in.read<int>();
        for (auto j : boost::irange(0, n)) {
            int a, b;
            in >> a, b;
            test[i][a] = (bool)b;
        }
    }

    auto check = [&](int n) -> bool {
        std::vector<int> assum(N);
        for (auto i : boost::irange(N - n, N)) assum[i] = 1;
        do {
            std::map<int, bool> test2;
            bool conflict = false;
            for (auto i : boost::irange(0, N)) {
                if (!assum[i]) continue;
                for (auto&& p : test[i]) {
                    if (assum[p.first - 1] != p.second ||
                        (test2.count(p.first) != 0 && test2[p.first] != p.second)) {
                        conflict = true;
                        break;
                    } else {
                        test2[p.first] = p.second;
                    }
                }
                if (conflict) break;
            }
            if (!conflict) return true;
        } while (std::next_permutation(assum.begin(), assum.end()));
        return false;
    };

    int l = 0, r = N;
    while (r - l != 1) {
        int m = l + (r - l) / 2;
        if (check(m)) {
            l = m;
        } else {
            r = m;
        }
    }
    out << l;

    return 0;
}
