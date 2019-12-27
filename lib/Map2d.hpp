#pragma once

#include <vector>

template <class T>
class Map2d
{
    std::size_t w = 0, h = 0;
    std::vector<T> m;

public:
    Map2d(std::size_t w_, std::size_t h_, const T& v = T())
    {
        w = w_;
        h = h_;
        m.resize(w * h, v);
    }
    Map2d(std::size_t w_, std::size_t h_, std::vector<T>&& v)
    {
        w = w_;
        h = h_;
        m = std::move(v);
        m.resize(w * h);
    }

    T& at(std::size_t i, std::size_t j)
    {
        return m[i + j * w];
    }
};
