#ifndef ICOLLECTION_H
#define ICOLLECTION_H

template <class T> class ICollection {
public:
    virtual T Get(size_t) const = 0;
    virtual size_t GetLength() const = 0;
    virtual ~ICollection() {}
    bool operator==(const ICollection<T> &rhs) const {
        size_t leftLen = GetLength();
        if (leftLen != rhs.GetLength()) {
            return false;
        }
        for (size_t i = 0; i < leftLen; i++) {
            if (! ( Get(i) == rhs.Get(i)) )
                return false;
        }
        return true;
    }
};

#endif
