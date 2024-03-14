#ifndef UNIQUE_PTR_H
#define UNIQUE_PTR_H
#include "defaultDeleter.h"

template <class T, class D = DefaultDelete<T>>
class unique_ptr {
protected:
	T* _pointer;
	D _deleter;
public:
	unique_ptr() noexcept : unique_ptr(nullptr) {}
	unique_ptr(T *pointer) noexcept : _pointer(pointer), _deleter() {}
	unique_ptr(const unique_ptr&) = delete;
	unique_ptr& operator=(const unique_ptr&) = delete;

	unique_ptr(unique_ptr &&rValue) noexcept : _pointer(rValue.release()) {}
	unique_ptr& operator=(unique_ptr&& rValue) noexcept {
		if (this != &rValue) {
			_deleter(_pointer);
			reset(rValue.release());
		}
		return *this;
	}

	T* release() noexcept {
		return std::exchange(_pointer, nullptr);
	}

	void reset(T* pointer = nullptr) noexcept {
		T* old = _pointer;
		_pointer = pointer;
		if (old) {
			_deleter(old);
		}
	}

	T* get() const noexcept { return _pointer; }
	T* operator->() const noexcept { return _pointer; }
	T &operator*() const noexcept { return *_pointer; }

	explicit operator bool() const noexcept {
		return _pointer != nullptr;
	}

	D& get_deleter() noexcept { return _deleter; }
	const D& get_deleter() const noexcept { return _deleter; }

	~unique_ptr() noexcept {
		if (_pointer) {
			_deleter(_pointer);
		}
	}
};

template <class T, class... Args>
unique_ptr<T> make_unique(Args&&... args) noexcept {
	return unique_ptr<T>(new T(std::forward<Args>(args)...));
}


#endif 

