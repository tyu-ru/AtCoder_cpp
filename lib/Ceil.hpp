#pragma once

template <class Integer>
Integer ceil(Integer x, Integer y)
{
    return (x + y - 1) / y;
}
