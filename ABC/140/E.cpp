#include <iostream>
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
    output() : cout(std::cout) {}
    template <class T>
    proxy operator<<(T&& val)
    {
        cout << val << ' ';
        return {};
    }
};

template <class T, std::size_t n>
class StaticVector : public boost::container::static_vector<T, n>
{
    using Parent = boost::container::static_vector<T, n>;

public:
    // is_constructible_v >= C++17
    template <class... Args, std::enable_if_t<std::is_constructible<Parent, Args&&...>::value, std::nullptr_t> = nullptr>
    StaticVector(Args&&... args) : Parent(std::forward<Args>(args)...) {}
    StaticVector(input& in, std::size_t n_) : Parent(n_)
    {
        for (std::size_t i = 0; i < n_; ++i) in >> static_cast<Parent&>(*this)[i];
    }
};

int main()
{
    input in;
    output out;
    int N = in.read<int>();
    StaticVector<std::pair<int, int>, 100000> P(N);
    for (int i = 0; i < N; ++i) P[i] = std::make_pair(in.read<int>(), i);
    std::sort(P.begin(), P.end());

    long long res = 0;
    std::multiset<int> used({-1, -1, N, N});
    for (int x : boost::irange(N, 0, -1)) {
        auto index = std::lower_bound(P.begin(), P.end(), std::make_pair(x, 0))->second;
        auto it = used.insert(index);
        if (x != N) {
            auto l = std::prev(it);
            auto ll = std::prev(l);
            auto u = std::next(it);
            auto uu = std::next(u);
            // out << x, *ll, *l, index, *u, *uu;
            res += x * ((long long)(*l - *ll) * (*u - index) + (long long)(index - *l) * (*uu - *u));
        }
    }
    out << res;

    return 0;
}
