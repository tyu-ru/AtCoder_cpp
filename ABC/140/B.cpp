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
        for (auto i : boost_irange(n)) {
            (void)i;
            cin >> var;
            f(var);
        }
    }
};
template <class T, std::size_t n>
std::istream& operator>>(std::istream& in, std::array<T, n>& var)
{
    for (auto i : boost_irange(n)) {
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
        in.read(static_cast<Parent*>(this)->begin(), n_);
    }
};

template <class T = int, std::size_t digit = 10>
class DigitPart
{
    T x;

public:
    class iterator
    {
        T x;

    public:
        using value_type = T;
        using difference_type = std::make_signed_t<T>;
        using pointer = const T*;
        using reference = const T;
        using iterator_category = std::forward_iterator_tag;

        constexpr iterator(T v) : x(v) {}
        constexpr inline bool operator==(const iterator&) { return x == 0; }
        constexpr inline bool operator!=(const iterator&) { return x != 0; }
        constexpr inline T operator*() const { return x % digit; }
        constexpr inline iterator& operator++()
        {
            x /= digit;
            return *this;
        }
        constexpr inline iterator operator++(int)
        {
            auto y = x;
            x /= digit;
            return iterator(y);
        }
    };

public:
    constexpr DigitPart(T x_) : x(x_) {}

    constexpr inline iterator begin() const { return iterator(x); };
    constexpr inline iterator end() const { return iterator(0); };
};

using Vec2i = std::array<int, 2>;

template <class T, std::size_t n>
T manhattan_distance(const std::array<T, n>& lhs, const std::array<T, n>& rhs)
{
    T res = 0;
    for (auto i : boost_irange(n)) {
        res += std::abs(lhs[i] - rhs[i]);
    }
    return res;
}

int main()
{
    input in;
    output out;
    int N = in.read<int>();
    StaticVector<int, 20> A(in, N), B(in, N), C(in, N);

    int manzoku = 0;
    int old = -1;
    for (auto i : boost_irange(N)) {
        int a = A[i];
        manzoku += B[a - 1];
        if (old == a - 1) manzoku += C[old - 1];
        old = a;
    }
    std::cout << manzoku;

    return 0;
}
