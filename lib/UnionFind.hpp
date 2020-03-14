class UnionFind
{
    std::vector<std::size_t> t;
    std::vector<std::size_t> s;

public:
    UnionFind(std::size_t n) : t(n), s(n, 1)
    {
        for (std::size_t i = 0; i < n; ++i) t[i] = i;
    }

    void unite(std::size_t a, std::size_t b)
    {
        if (root(a) == root(b)) return;
        auto tmp = s[root(a)];
        s[root(a)] = 0;
        s[root(b)] += tmp;
        t[root(a)] = root(b);
    }
    std::size_t root(std::size_t a)
    {
        if (t[a] == a) return a;
        auto res = root(t[a]);
        t[a] = res;
        return res;
    }
    std::size_t size(std::size_t a)
    {
        return s[root(a)];
    }
};
