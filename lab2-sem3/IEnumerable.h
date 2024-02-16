#ifndef IENUMERABLE
#define IENUMERABLE
#include <memory>
#include "IEnumerator.h"
#include "smart_ptrs/shared_ptr.h"


template <class T>
class IEnumerable {
public:
    virtual shared_ptr<IEnumerator<T>> GetEnumerator() = 0;
    virtual ~IEnumerable() {}
};
#endif
