#ifndef WEAK_PTR_H
#define WEAK_PTR_H
#include "defaultDeleter.h"
#include "shared_ptr.h"

template <class T, class D = DefaultDelete<T>>
class weak_ptr {
    friend class shared_ptr<T, D>;
private:
    T* _pointer;
    size_t* ref_count;
    size_t* weak_ref_count;

public:
    weak_ptr() noexcept : _pointer(nullptr), ref_count(nullptr), weak_ref_count(nullptr) {}

    weak_ptr(const shared_ptr<T, D>& shared) noexcept : _pointer(shared._pointer), ref_count(shared.ref_count), weak_ref_count(shared.weak_ref_count) {
        if(weak_ref_count)
            (*weak_ref_count)++;
        else
            weak_ref_count = new size_t(1);
    }
    weak_ptr(shared_ptr<T, D>&& shared) noexcept : _pointer(shared._pointer), ref_count(shared.ref_count), weak_ref_count(shared.weak_ref_count) {
		shared._pointer = nullptr;
		shared.ref_count = nullptr;
		shared.weak_ref_count = nullptr;        
        if(weak_ref_count)
            (*weak_ref_count)++;
        else
            weak_ref_count = new size_t(1);
    }

    weak_ptr(const weak_ptr& other) noexcept : _pointer(other._pointer), ref_count(other.ref_count), weak_ref_count(other.weak_ref_count) {
        if(weak_ref_count)
            (*weak_ref_count)++;
    }
	weak_ptr(weak_ptr&& other) noexcept : _pointer(other._pointer), ref_count(other.ref_count), weak_ref_count(other.weak_ref_count) {
		other._pointer = nullptr;
		other.ref_count = nullptr;
		other.weak_ref_count = nullptr;
	}
    weak_ptr& operator=(const weak_ptr<T>& other) noexcept {
        if (this != &other) {
            release();
            _pointer = other._pointer;
            ref_count = other.ref_count;
            weak_ref_count = other.weak_ref_count;
            if (weak_ref_count)
                (*weak_ref_count)++;
            else
                weak_ref_count = new size_t(1);
        }
        return *this;
    }
    weak_ptr& operator=(const shared_ptr<T, D>& shared) noexcept {        
        if (_pointer != shared._pointer) {
            reset(shared);
        }
        return *this;
    }


    ~weak_ptr() {
        release();
    }

    size_t use_count() const {
        return ref_count ? *ref_count : 0;
    }

    bool expired() const {
        return use_count() == 0;
    }

    shared_ptr<T, D> lock() const {
        if (expired()) {
            return shared_ptr<T, D>();
        }
        return shared_ptr<T, D>(*this);
    }
    explicit operator bool() const {
        return _pointer != nullptr;
    }
    void reset() noexcept {
        release();
        _pointer = nullptr;
        ref_count = nullptr;
        weak_ref_count = nullptr;
    }
private:
    void reset(const shared_ptr<T>& shared) {
        release();
        _pointer = shared._pointer;
        ref_count = shared.ref_count;
        weak_ref_count = shared.weak_ref_count;
        (*weak_ref_count)++;
    }

    void reset(const weak_ptr& other) {
        release();
        _pointer = other._pointer;
        ref_count = other.weak_ref_count;
        weak_ref_count = other.weak_ref_count;
        (*weak_ref_count)++;
    }
    void release() {
        if (weak_ref_count) {
            (*weak_ref_count)--;
            if (*weak_ref_count == 0 && *ref_count == 0) {
                delete ref_count;
                delete weak_ref_count;
            }
        }
    }

};
#endif