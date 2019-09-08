#pragma once

#include <array>

using Vec2i = std::array<int, 2>;

template <class T, std::size_t n>
inline T manhattan_distance(const std::array<T, n>& lhs, const std::array<T, n>& rhs)
{
    T res = 0;
    for (std::size_t i = 0; i < n; ++i) {
        res += std::abs(lhs[i] - rhs[i]);
    }
    return res;
}
