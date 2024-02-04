#ifndef SEQUENCE_H
#define SEQUENCE_H
#include "IEnumerator.h"
#include "IEnumerable.h"
#include "ICollection.h"

template <class T>
class Sequence : public IEnumerable<T>, public ICollection<T> {
public:
    virtual ~Sequence() {}
    virtual T GetFirst() const = 0;
    virtual T GetLast() const = 0;
    virtual T Get(size_t index) const override = 0;
    virtual T& operator[] (const size_t index) = 0;
    virtual Sequence<T>* GetSubsequence(size_t startIndex, size_t endIndex) const = 0;
    virtual size_t GetLength() const override = 0;
    virtual void Append(T item) = 0;
    virtual void Prepend(T item) = 0;
    virtual void InsertAt(T item, size_t index) = 0;
    template <class T_SEQ>
    Sequence <T>* Concat(Sequence <T> *list) {
        auto e = list->GetEnumerator();
        T_SEQ *resSequence = new T_SEQ(this);
        while (e->next()) {
//            std::cout<< *(*e) << '\n';
            resSequence->Append(*(*e));
        }
        return resSequence;
    }
    template <class T_SEQ, class T2>
    Sequence <T2>* Map(T2 (*f)(T)) {
        IEnumerable<T> *base = this;
        auto e = base->GetEnumerator();
        T_SEQ *resSequence = new T_SEQ();
//        std::cout<< " " << '\n';
        while (e->next()) {
//            std::cout<< *(*e)<<" " << f(*(*e)) << '\n';
            resSequence->Append(f(*(*e)));
        }
        return resSequence;
    }
    template <class T1>
    T1 Reduce(T1 (*f)(T, T1), T1 iter) {
        IEnumerable<T> *base = this;
        auto e = base->GetEnumerator();
        while (e->next()) {
            iter = f(*(*e), iter);
        }
        return iter;
    }
    template <class T_SEQ>
    Sequence<T>* Where(bool (*f)(T)) {
        IEnumerable<T> *base = this;
        auto e = base->GetEnumerator();
        T_SEQ *resSequence = new T_SEQ();
        while (e->next()) {
            if (f(*(*e)))
                resSequence->Append(*(*e));
        }
        return resSequence;
    }
};

#endif
