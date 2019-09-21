#include <iostream>
#include <iomanip>
#include <cmath>
#include <functional>
#include <algorithm>
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
#include <boost/container/string.hpp>
#include <boost/utility/string_ref.hpp>

template <class Integer>
auto boost_irange(Integer last) { return boost::irange(static_cast<Integer>(0), last); }
template <class Integer>
auto boost_irange(Integer first, Integer last) { return boost::irange(first, last); }

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
        ~proxy() { cout << std::endl; }
        template <class T>
        proxy& operator,(T&& val)
        {
            cout << val << ' ';
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
        cout << val << ' ';
        return {};
    }
};

void Z_algorithm(boost::string_ref str, std::vector<std::size_t>& res)
{
    std::size_t c = 0, n = str.length();
    res.clear();
    res.resize(n, 0);
    for (std::size_t i = 1; i < n; ++i) {
        auto l = i - c;
        if (i + res[l] < c + res[c]) {
            res[i] = res[l];
        } else {
            auto j = c + res[c] < i ? 0 : c + res[c] - i;
            while (i + j < n && str[j] == str[i + j]) ++j;
            res[i] = j;
            c = i;
        }
    }
    res[0] = n;
}
//    my_assert(Z_algorithm("aabaabaaa"), std::vector<std::size_t>({9, 1, 0, 5, 1, 0, 2, 2, 1}));
std::vector<std::size_t> Z_algorithm(boost::string_ref str)
{
    std::vector<std::size_t> res;
    Z_algorithm(str, res);
    return std::move(res);
}

int main()
{
    input in;
    output out;

    int N = in.read<int>();
    auto S = in.read<std::string>();
    boost::string_ref ref = S;

    std::vector<std::size_t> Z;
    std::size_t res = 0;
    for (int i = 0; i < N; ++i) {
        Z_algorithm(ref.substr(i), Z);
        for (std::size_t j = 0; j < Z.size(); ++j) {
            if (Z[j] <= j) res = std::max(Z[j], res);
        }
    }

    out << res;

    return 0;
}
