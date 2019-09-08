#include <iostream>

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
};

int main()
{
    input in;
    int a, b;
    in >> a, b;

    std::cout << ((a & 1 && b & 1) ? "Odd" : "Even");

    return 0;
}
