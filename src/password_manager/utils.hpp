#pragma once

#include <ostream>
#include <vector>

template <typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &vec) {
    if (vec.empty()) {
        return os;
    }

    auto iter = vec.begin();
    os << "vector{" << *iter;
    ++iter;
    while (iter != vec.end()) {
        os << ", " << *iter;
        ++iter;
    }
    os << '}';

    return os;
}
