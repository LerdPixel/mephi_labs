#pragma once
#include "../Range.h"
#include "../IDictionary.h"

std::ostream &operator<<(std::ostream &os, Range const &range) {
    return os << "( " << range.GetStart() << " , " << range.GetEnd() << " )";
}
template <typename T>
std::ostream &operator<<(std::ostream &os, IDictionary<T, int> &dict) {
    auto keys = dict.GetKeys();
    auto e = keys->GetEnumerator();
    while (e->next()) {
        os << **e << " >==< " << dict[**e] << "\n";
    }
    return os;
}