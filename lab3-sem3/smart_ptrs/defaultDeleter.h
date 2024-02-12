#ifndef DEFAULT_DELETER
#define DEFAULT_DELETER

template <class T>
struct DefaultDelete {
	void operator()(T* pointer) { delete pointer; }
};

#endif