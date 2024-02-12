#ifndef IENUMERABLE
#define IENUMERABLE
#include "smart_ptrs/shared_ptr.h"
#include "IEnumerator.h"


template <class T>
class IEnumerable {
public:
    virtual shared_ptr<IEnumerator<T>> GetEnumerator() = 0;
    virtual ~IEnumerable() {}
};
#endif
