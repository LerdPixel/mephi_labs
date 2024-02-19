#pragma once
#include <functional>
#include "SmartPtrLinkedList.h"
#include "Pair.h"
#include "Sequence.h"
#include "ArraySequence.h"

template <typename TKey, typename TValue>
class HashTable
{
protected:
    typedef std::hash<TKey> Hash;
	size_t capacity;
	size_t length;
	const size_t expansionCoeff = 2;
	const size_t ultimateCapacityCoeff = 3;
	shared_ptr<Sequence<shared_ptr<SmartPtrLinkedList<Pair<TKey, TValue>>>>> container;

    
	void IncreaseCapacity() {
		capacity *= expansionCoeff;
	}
	void DecreaseCapacity() {
		capacity /= expansionCoeff;
	}
    shared_ptr<Sequence<shared_ptr<SmartPtrLinkedList<Pair<TKey, TValue>>>>> emptySequence(size_t size) {
        auto emptySeq = shared_ptr<Sequence<shared_ptr<SmartPtrLinkedList<Pair<TKey, TValue>>>>>(new ArraySequence<shared_ptr<SmartPtrLinkedList<Pair<TKey, TValue>>>>());
        for(int i = 0; i < size; ++i) {
            emptySeq->Append(shared_ptr<SmartPtrLinkedList<Pair<TKey, TValue>>>(new SmartPtrLinkedList<Pair<TKey, TValue>>()));
        }
		return emptySeq;
    }
	void Rearrangement() {
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
public:
	HashTable() = delete;
	HashTable(size_t capacity) : capacity(capacity), length(0) {
		container = emptySequence(capacity);
	}
	~HashTable() {}
	size_t GetLength() { return length; }

	size_t GetCapacity() { return capacity; }

	void Add(TKey key, TValue item) {
		size_t index = Hash{}(key) % capacity;
		((*container)[index])->Prepend(Pair<TKey, TValue>(key, item));
		++length;
		if (length >= capacity) {
			IncreaseCapacity();
			Rearrangement();
		}
	}
	TValue& Get(TKey key) {
		size_t index = Hash{}(key) % capacity;
		size_t chainNumber = ((*container)[index])->findByValue(Pair<TKey, TValue>(key));
		if (chainNumber == -1)
			throw std::out_of_range("key not found");
		return  (*(*container)[index])[chainNumber].GetValueRef();
	}
	void Remove(TKey key) {
		size_t index = Hash{}(key) % capacity;
		size_t chainNumber = ((*container)[index])->findByValue(Pair<TKey, TValue>(key));
		if (chainNumber == -1)
			throw std::out_of_range("key not found");
		((*container)[index])->Remove(chainNumber);
	}
	bool ContainsKey(TKey key)
	{
		size_t index = Hash{}(key) % capacity;
		size_t chainNumber = ((*container)[index])->findByValue(Pair<TKey, TValue>(key));
		return chainNumber != -1;
	}
};