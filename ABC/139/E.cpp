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

    std::vector<std::vector<int>> match(N);
    for (auto& v : match) {
        v.resize(N - 1);
        in.read(v.rbegin(), N - 1);
    }

    std::queue<std::pair<int, int>> today, next;

    for (int i = 0; i < N; ++i) {
        int j = match[i].back() - 1;
        if (j < 0) continue;
        if (match[j].back() - 1 == i) {
            match[i].back() = 0;
            match[j].back() = 0;
            today.push(std::make_pair(i, j));
        }
    }

    auto reserve = [&](int i) {
        match[i].pop_back();
        if (match[i].empty()) return;
        int j = match[i].back() - 1;
        if (match[j].empty()) return;
        if (match[j].back() - 1 == i) {
            // out << "reserve", i, j;
            match[i].back() = 0;
            match[j].back() = 0;
            next.push(std::make_pair(i, j));
        }
    };

    int days = 0, count = 0;
    for (; !today.empty(); ++days) {
        count += today.size();
        for (; !today.empty(); today.pop()) {
            // out << "match", today.front().first, today.front().second;
            reserve(today.front().first);
            reserve(today.front().second);
        }
        today = next;
        next = decltype(next){};
    }
    if (count != N * (N - 1) / 2) {
        out << -1;
    } else {
        out << days;
    }
    return 0;
}
