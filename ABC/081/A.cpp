#include <iostream>
#include <functional>
#include <type_traits>

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

    int x = 0;
    in.online<char>(3, [&](char c) {if (c == '1')++x; });

    std::cout << x;

    return 0;
}
