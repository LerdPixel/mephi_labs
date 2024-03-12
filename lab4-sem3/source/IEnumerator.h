#ifndef IENUMERATOR_H
#define IENUMERATOR_H

template <class T> class IEnumerator {
public:
    virtual bool next() = 0;
    virtual T& operator * () = 0;
    virtual ~IEnumerator() {}
};

#endif
