#ifndef SHARED_PTR_H
#define SHARED_PTR_H
#include "defaultDeleter.h"
template <class T, class D>
class weak_ptr;

template <class T, class D = DefaultDelete<T>>
class shared_ptr {
	friend class weak_ptr<T, D>;
private:
	T* _pointer;
	D _deleter;
	size_t* ref_count;
	size_t* weak_ref_count;
public:
	shared_ptr() noexcept : _pointer(nullptr), ref_count(nullptr), weak_ref_count(nullptr), _deleter() {}
	explicit shared_ptr(T* pointer) noexcept : _pointer(pointer), _deleter(), ref_count(new size_t(1)), weak_ref_count(new size_t(0)) {}
	shared_ptr(const shared_ptr& other) : _pointer(other._pointer), ref_count(other.ref_count), weak_ref_count(other.weak_ref_count) {
		if (ref_count)
			++(*ref_count);
		else
			ref_count = new size_t(1);
	}
	shared_ptr(shared_ptr&& other) noexcept : _pointer(other._pointer), ref_count(other.ref_count), weak_ref_count(other.weak_ref_count) {
		other._pointer = nullptr;
		other.ref_count = nullptr;
		other.weak_ref_count = nullptr;
	}
	shared_ptr(const weak_ptr<T, D>& weak) : _pointer(weak._pointer), ref_count(weak.ref_count), weak_ref_count(weak.weak_ref_count), _deleter() {
		if (ref_count)
			++(*ref_count);
		else
			ref_count = new size_t(1);		
	}
	//constexpr shared_ptr(shared_ptr)
	shared_ptr& operator=(const shared_ptr& other) noexcept {
		if  (this != &other) {
			release();
			_pointer = other._pointer;
			ref_count = other.ref_count;
			weak_ref_count = other.weak_ref_count;			
			++(*ref_count);
		}
		return *this;
	}
	shared_ptr& operator=(shared_ptr&& other) noexcept {
		if (this != &other) {
			release();
			_pointer = other._pointer;
			ref_count = other.ref_count;
			weak_ref_count = other.weak_ref_count;
			other._pointer = nullptr;
			other.ref_count = nullptr;
			other.weak_ref_count = nullptr;
		}
		return *this;
	}
	void reset(T* pointer = nullptr) noexcept {
		release();
		_pointer = pointer;
		if (_pointer) {
			ref_count = new size_t(1);
			weak_ref_count = new size_t(0);
		} else {
			ref_count = nullptr;
			weak_ref_count = nullptr;
		}
	}
	size_t use_count() const noexcept {
		return ref_count != nullptr ? *ref_count : 0;
	}
	T* get() const noexcept { return _pointer; }
	T* operator->() const noexcept { return _pointer; }
	T& operator*() const noexcept { return *_pointer; }

	explicit operator bool() const noexcept {
		return _pointer != nullptr;
	}
	bool operator==(const shared_ptr<T, D>& other) const noexcept {
		return _pointer == other._pointer;
	}
	bool operator!=(const shared_ptr<T, D>& other) const noexcept {
		return _pointer != other._pointer;
	}
	D& get_deleter() noexcept { return _deleter; }
	const D& get_deleter() const noexcept { return _deleter; }

	~shared_ptr() {
		release();
	}

private:
	void release() {
		if (ref_count != nullptr) {
			--(*ref_count);
			if (*ref_count > 0) {
				return;
			}
			if (*weak_ref_count == 0) {
				delete weak_ref_count;
				delete ref_count;
/* 				_deleter(_pointer);
				return; */
			}
			_deleter(_pointer);
		}
	}
};

template <class T, class... Args>
shared_ptr<T> make_shared(Args&&... args) {
	return shared_ptr<T>(new T(std::forward<Args>(args)...));
}

#endif