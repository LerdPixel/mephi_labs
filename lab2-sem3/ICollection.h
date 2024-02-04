#ifndef ICOLLECTION_H
#define ICOLLECTION_H

template <class T> class ICollection {
public:
    virtual T Get(size_t) const = 0;
    virtual size_t GetLength() const = 0;
    virtual ~ICollection() {}
    bool operator==(const ICollection<T> &rhs) const {
        size_t leftLen = GetLength();
//        std::cout << "==start=="<<GetLength()<<"  "<< rhs.GetLength() << '\n';
        if (leftLen != rhs.GetLength()) {
            return false;
        }
//        std::cout << "  len ok" << '\n';
        for (size_t i = 0; i < leftLen; i++) {
//            std::cout << i << "   left:" << Get(i) << "   right:" << rhs.Get(i) << '\n';
            if (! ( Get(i) == rhs.Get(i)) )
                return false;
        }
        return true;
    }
};

#endif
