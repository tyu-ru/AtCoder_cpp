#include <iostream>
#include <functional>
#include <algorithm>

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

    template <class T>
    inline void read(T* head, std::size_t n)
    {
        for (std::size_t i = 0; i < n; ++i) {
            cin >> head[i];
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

template <class T = int>
class Range
{
    T f = 0, l;

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
        constexpr inline bool operator==(const iterator& rhs) { return x == rhs.x; }
        constexpr inline bool operator!=(const iterator& rhs) { return x != rhs.x; }
        constexpr inline const T& operator*() const { return x; }
        constexpr inline iterator& operator++()
        {
            ++x;
            return *this;
        }
        constexpr inline iterator operator++(int)
        {
            return iterator(x++);
        }
    };

public:
    constexpr Range(T first, T last) : f(first), l(last) {}
    constexpr Range(T count) : l(count) {}

    constexpr inline iterator begin() const { return iterator(f); };
    constexpr inline iterator end() const { return iterator(l); };
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

int main()
{
    input in;
    int N, a[100];
    in >> N;
    in.read(a, N);

    std::sort(a, a + N, std::greater<>());

    int alice = 0;
    for (int i : Range<>(N)) {
        alice += (i & 1) ? -a[i] : a[i];
    }
    std::cout << alice;

    return 0;
}
