#include <iostream>
#include <functional>
#include <limits>

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
    input& operator>>(T& var)
    {
        cin >> var;
        return *this;
    }
    template <class T>
    input& operator,(T& var)
    {
        cin >> var;
        return *this;
    }

    template <class T>
    T read()
    {
        T var;
        cin >> var;
        return var;
    }

    template <class T, class F>
    void online(std::size_t n, F&& f)
    {
        T var;
        for (std::size_t i = 0; i < n; ++i) {
            cin >> var;
            f(var);
        }
    }
};

int main()
{
    input in;
    auto min = std::numeric_limits<int>::max();
    in.online<int>(in.read<std::size_t>(), [&](auto x) { min = std::min(min, __builtin_ctz(x)); });

    std::cout << min;
    return 0;
}
