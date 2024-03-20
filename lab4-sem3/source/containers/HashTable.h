#pragma once
#include <functional>
#include "SmartPtrLinkedList.h"
#include "SmartPtrLinkedListSequence.h"
#include "Pair.h"
#include "Sequence.h"
#include "ArraySequence.h"
#include "IDictionary.h"

template <typename TKey, typename TValue>
class HashTable : public IDictionary<TKey, TValue> {
protected:
    typedef std::hash<TKey> Hash;
	size_t capacity;
	size_t length;
	static const size_t DEFAULT_CAPACITY = 8;
	const size_t expansionCoeff = 2;
	const size_t ultimateCapacityCoeff = 3;
	shared_ptr<Sequence<shared_ptr<SmartPtrLinkedList<Pair<TKey, TValue>>>>> container;    
	
	inline void IncreaseCapacity() { capacity *= expansionCoeff; }
	inline void DecreaseCapacity() { capacity /= expansionCoeff; }
    
	shared_ptr<Sequence<shared_ptr<SmartPtrLinkedList<Pair<TKey, TValue>>>>> emptySequence(size_t size);
	
	void Rearrangement();
public:
	HashTable();
	HashTable(size_t capacity);
	~HashTable() {}
	inline int GetLength() override { return length; }

	inline size_t GetCapacity() { return capacity; }

	void Add(TKey key, TValue item) override;
	TValue& operator[] (const TKey key) override;
	TValue Get(TKey key) override;
	void Set(TKey key, TValue element) override;
	void Remove(TKey key) override;
	bool ContainsKey(TKey key) override;
	shared_ptr<Sequence<TKey>> GetKeys() const override;
	shared_ptr<Sequence<Pair<TKey, TValue>>> GetPairs() const;
};

template <typename TKey, typename TValue>
shared_ptr<Sequence<shared_ptr<SmartPtrLinkedList<Pair<TKey, TValue>>>>> HashTable<TKey, TValue> :: emptySequence(size_t size) {
	auto emptySeq = shared_ptr<Sequence<shared_ptr<SmartPtrLinkedList<Pair<TKey, TValue>>>>>(new ArraySequence<shared_ptr<SmartPtrLinkedList<Pair<TKey, TValue>>>>());
	for(int i = 0; i < size; ++i) {
		emptySeq->Append(shared_ptr<SmartPtrLinkedList<Pair<TKey, TValue>>>(new SmartPtrLinkedList<Pair<TKey, TValue>>()));
	}
	return emptySeq;
}
template <typename TKey, typename TValue>
void HashTable<TKey, TValue> :: Rearrangement() {
	auto tempContainer = container;
	container = emptySequence(capacity);
	auto e = tempContainer->GetEnumerator();
	while(e->next()) {
		auto eList = (**e)->GetEnumerator();
		while (eList->next()) {
			TKey key = (**eList).GetKey();
			TValue item = (**eList).GetValue();
			size_t index = Hash{}(key) % capacity;
			(*container)[index]->Prepend(Pair<TKey, TValue>(key, item));
		}
	}
}
template <typename TKey, typename TValue>
HashTable<TKey, TValue> :: HashTable() : capacity(DEFAULT_CAPACITY), length(0) {
	container = emptySequence(capacity);
}
template <typename TKey, typename TValue>
HashTable<TKey, TValue> :: HashTable(size_t capacity) : capacity(capacity), length(0) {
	container = emptySequence(capacity);
}
template <typename TKey, typename TValue>
void HashTable<TKey, TValue> :: Add(TKey key, TValue item) {
	size_t index = Hash{}(key) % capacity;
	((*container)[index])->Prepend(Pair<TKey, TValue>(key, item));
	++length;
	if (length >= capacity) {
		IncreaseCapacity();
		Rearrangement();
	}
}
template <typename TKey, typename TValue>
TValue& HashTable<TKey, TValue> :: operator[] (const TKey key) {
	size_t index = Hash{}(key) % capacity;
	size_t chainNumber = ((*container)[index])->findByValue(Pair<TKey, TValue>(key));
	if (chainNumber == -1)
		throw std::out_of_range("key not found");
	return  (*(*container)[index])[chainNumber].GetValueRef();
}
template <typename TKey, typename TValue>
TValue HashTable<TKey, TValue> :: Get(TKey key) {
	size_t index = Hash{}(key) % capacity;
	size_t chainNumber = ((*container)[index])->findByValue(Pair<TKey, TValue>(key));
	if (chainNumber == -1)
		throw std::out_of_range("key not found");
	return  (*(*container)[index])[chainNumber].GetValue();
}
template <typename TKey, typename TValue>
void HashTable<TKey, TValue> :: Set(TKey key, TValue element) {
	size_t index = Hash{}(key) % capacity;
	size_t chainNumber = ((*container)[index])->findByValue(Pair<TKey, TValue>(key));
	if (chainNumber == -1)
		throw std::out_of_range("key not found");
	(*(*container)[index])[chainNumber].SetValue(element);
}
template <typename TKey, typename TValue>
void HashTable<TKey, TValue> :: Remove(TKey key) {
	size_t index = Hash{}(key) % capacity;
	size_t chainNumber = ((*container)[index])->findByValue(Pair<TKey, TValue>(key));
	if (chainNumber == -1)
		throw std::out_of_range("key not found");
	--length;
	((*container)[index])->Remove(chainNumber);
	if (length * ultimateCapacityCoeff <= capacity) {
		DecreaseCapacity();
		Rearrangement();
	}
}
template <typename TKey, typename TValue>
bool HashTable<TKey, TValue> :: ContainsKey(TKey key) {
	size_t index = Hash{}(key) % capacity;
	size_t chainNumber = ((*container)[index])->findByValue(Pair<TKey, TValue>(key));
	return chainNumber != -1;
}
template <typename TKey, typename TValue>
shared_ptr<Sequence<TKey>> HashTable<TKey, TValue> :: GetKeys() const {
	shared_ptr<Sequence<TKey>> keysContainer = shared_ptr<Sequence<TKey>>(new ArraySequence<TKey>());
	auto e = container->GetEnumerator();
	while(e->next()) {
		auto eList = (**e)->GetEnumerator();
		while (eList->next()) {
			keysContainer->Append((**eList).GetKey());
		}
	}
	return keysContainer;
}
template <typename TKey, typename TValue>
shared_ptr<Sequence<Pair<TKey, TValue>>> HashTable<TKey, TValue> :: GetPairs() const {
	shared_ptr<Sequence<Pair<TKey, TValue>>> pairsContainer = shared_ptr<Sequence<Pair<TKey, TValue>>>(new SmartPtrLinkedListSequence<Pair<TKey, TValue>>());
	auto e = container->GetEnumerator();
	while(e->next()) {
		auto eList = (**e)->GetEnumerator();
		while (eList->next()) {
			pairsContainer->Prepend((**eList));
		}
	}
	return pairsContainer;
}