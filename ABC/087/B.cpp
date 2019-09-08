#include <iostream>
#include <functional>

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

template <class T = std::size_t>
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

int main()
{
    input in;
    int A, B, C, X;
    in >> A, B, C, X;
    int res = 0;
    for (auto a : Range<>(A + 1)) {
        for (auto b : Range<>(B + 1)) {
            for (auto c : Range<>(C + 1)) {
                if (a * 500 + b * 100 + c * 50 == X) ++res;
            }
        }
    }
    std::cout << res;
    return 0;
}
