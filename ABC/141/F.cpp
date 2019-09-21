#include <iostream>
#include <iomanip>
#include <cmath>
#include <functional>
#include <numeric>
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

int main()
{
    input in;
    output out;

    std::size_t N = in.read<std::size_t>();

    std::vector<std::uint64_t> d(N);
    in.read(d.begin(), N);

    auto all = std::accumulate(std::begin(d), std::end(d), std::uint64_t{0}, std::bit_xor<>{});

    std::size_t rank = 0;
    for (std::uint64_t i = std::uint64_t{1} << 60; i != 0; i >>= 1) {
        if (all & i) continue;

        for (std::size_t r = rank; r < N; ++r) {
            if (!(d[r] & i)) continue;

            for (std::size_t rr = 0; rr < N; ++rr) {
                if (rr == r) continue;
                if (!(d[rr] & i)) continue;
                d[rr] ^= d[r];
            }
            std::swap(d[rank], d[r]);
            rank++;
            break;
        }
    }
    std::uint64_t res = 0;
    for (auto x : d) {
        res ^= x;
    }

    out << (res & (~all)) * 2 + all;

    return 0;
}
