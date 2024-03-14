#pragma once

template <typename TKey, typename TValue>
class Pair {
private:
    TKey key;
    TValue value;
public:
    Pair(TKey k) : key(k) {}
    Pair(TKey k, TValue v) : key(k), value(v) {}
    TKey GetKey() const {
        return key;
    }
    TValue GetValue() const {
        return value;
    }
    TValue& GetValueRef() {
        return value;
    }
    void SetValue(TValue v) {
        value = v;
    }
    bool operator ==(const Pair<TKey, TValue>& other) const {
        return (key == other.GetKey());
    }
};