#pragma once

template <typename TKey, typename TValue>
class Pair {
private:
    TKey key;
    TValue value;
public:
    Pair(const TKey& k, const TValue& v) : key(k), value(v) {}
    TKey GetKey() {
        return key;
    }
    TValue GetValue() {
        return value;
    }
};