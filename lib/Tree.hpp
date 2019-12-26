#pragma once

#include <vector>

class Tree
{
    std::vector<std::vector<int>> tree;

public:
    Tree(int n) : tree(n) {}

    void addEdge(int a, int b)
    {
        a -= 1;
        b -= 1;
        tree[a].push_back(b);
        tree[b].push_back(a);
    }

    template <class F, class T>
    void dfs(F func, T takeover, int node, int parent = -1) const
    {
        auto tak = func(node, takeover);
        for (int n : tree[node]) {
            if (n == parent) continue;
            dfs(func, tak, n, node);
        }
    }

    std::vector<int> distance(int node) const
    {
        std::vector<int> res(tree.size());
        dfs([&res](int n, int t) { res[n] = t; return t + 1; }, 0, node);
        return res;
    }
};

/// !!! Bug
class RootedTree
{
    std::vector<int> tree;

public:
    RootedTree(int n)
        : tree(n + 1, 0)
    {
        tree[0] = 1;
    }

    void addEdge(int a, int b)
    {
        if (a > b) std::swap(a, b);
        tree[b] = a;
    }

    void turn(int root)
    {
        if (root == tree[0]) return;
        if (root != tree[0]) {
            turn(tree[root]);
        }
        int prevRoot = tree[0];
        tree[0] = root;
        tree[prevRoot] = root;
        tree[root] = 0;
    }

    void depth(std::vector<int>& res, int node) const
    {
        if (res[node] != -1) return;
        if (node == tree[0]) {
            res[node] = 0;
            return;
        }
        if (res[tree[node]] == -1) {
            depth(res, tree[node]);
        }
        res[node] = res[tree[node]] + 1;
    }

    std::vector<int> depth() const
    {
        std::vector<int> res(tree.size(), -1);
        for (int i = 1; i < res.size(); ++i) {
            depth(res, i);
        }
        return res;
    }
};
