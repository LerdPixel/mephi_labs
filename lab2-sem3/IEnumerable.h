#ifndef IENUMERABLE
#define IENUMERABLE
#include <memory>
#include "IEnumerator.h"


template <class T>
class IEnumerable {
public:
    virtual std::shared_ptr<IEnumerator<T>> GetEnumerator() = 0;
    virtual ~IEnumerable() {}
};
#endif
