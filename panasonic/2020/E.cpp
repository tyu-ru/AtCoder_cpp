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
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/math/common_factor_rt.hpp>

class input
{
public:
    input()
    {
        std::cin.tie(nullptr);
        std::ios::sync_with_stdio(false);
    }

    template <class T>
    inline input& operator>>(T& var) { return std::cin >> var, *this; }
    template <class T>
    inline input& operator,(T& var) { return *this >> var; }

    template <class T>
    inline T read()
    {
        T var;
        std::cin >> var;
        return var;
    }

    template <class InputIterator>
    inline void read(InputIterator head, std::size_t n)
    {
        for (std::size_t i = 0; i < n; ++i) {
            std::cin >> *head;
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
            std::cin >> tmp;
            res.emplace_back(tmp);
        }
        return res;
    }

    template <class T, class F>
    inline void online(std::size_t n, F&& f)
    {
        T var;
        for (std::size_t i = 0; i < n; ++i) {
            std::cin >> var;
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

    template <class T, class... Args>
    void impl(T&& v, Args&&... args)
    {
        cout << std::forward<T>(v) << ' ';
        impl(std::forward<Args>(args)...);
    }
    template <class T>
    void impl(T&& v)
    {
        cout << std::forward<T>(v);
    }

public:
    output() : cout(std::cout)
    {
        cout << std::fixed << std::setprecision(15);
    }

    template <class... Args>
    void operator()(Args&&... args)
    {
        impl(std::forward<Args>(args)...);
        cout << '\n';
    }
    template <class... Args>
    void noreturn(Args&&... args)
    {
        impl(std::forward<Args>(args)...);
    }

    template <class T>
    void print(const T& container)
    {
        bool first = true;
        for (auto&& x : container) {
            if (!first) {
                cout << ' ';
            }
            cout << x;
            first = false;
        }
        cout << '\n';
    }
};

std::vector<int> Z(std::string s)
{
    std::vector<int> A(s.size());
    A[0] = s.size();
    int i = 1, j = 0;
    while (i < s.size()) {
        while (i + j < s.size() && (s[j] == '?' || s[i + j] == '?' || s[j] == s[i + j])) ++j;
        A[i] = j;
        if (j == 0) {
            ++i;
            continue;
        }
        int k = 1;
        while (i + k < s.size() && k + A[k] < j) A[i + k] = A[k], ++k;
        i += k;
        j -= k;
    }
    return A;
}

std::string marge(std::string a, std::string b, int x)
{
    std::string res = a.substr(0, x);
    a = a.substr(x);
}

void prog()
{
    input in;
    output out;
    std::string s1, s2, s3;
    in >> s1, s2, s3;
    auto a = Z(s1 + s2);
    std::distance(a.begin() + s1.size(), std::max_element(a.begin() + s1.size(), a.end()));
}

int main()
{
    prog();
    return 0;
}
