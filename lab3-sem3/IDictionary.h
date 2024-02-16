#pragma once
#include "Pair.h"

template <typename TKey, typename TValue>
class IDictionary {
public:
	virtual int GetLength() = 0;
	
	virtual TValue Get(TKey key) = 0;

	virtual bool ContainsKey(TKey key) = 0;
	virtual void Add(TKey key, TValue element) = 0;
    virtual TValue& operator[] (const TKey key) = 0;
    virtual void Set(TKey key, TValue element) = 0;
	virtual void Remove(TKey key) = 0;
	virtual shared_ptr<Sequence<TKey>> GetKeys() = 0;
//	virtual shared_ptr<Sequence<TValue>> GetValues() = 0;

	virtual ~IDictionary() {};
};