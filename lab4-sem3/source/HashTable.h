#pragma once
#include <functional>
#include "SmartPtrLinkedList.h"
#include "Pair.h"
#include "Sequence.h"
#include "ArraySequence.h"
#include "IDictionary.h"

template <typename TKey, typename TValue>
class HashTable : IDictionary<TKey, TValue> {
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
	int GetLength() override { return length; }

	size_t GetCapacity() { return capacity; }

	void Add(TKey key, TValue item) override {
		size_t index = Hash{}(key) % capacity;
		((*container)[index])->Prepend(Pair<TKey, TValue>(key, item));
		++length;
		if (length >= capacity) {
			IncreaseCapacity();
			Rearrangement();
		}
	}
	TValue& operator[] (const TKey key) override {
		size_t index = Hash{}(key) % capacity;
		size_t chainNumber = ((*container)[index])->findByValue(Pair<TKey, TValue>(key));
		if (chainNumber == -1)
			throw std::out_of_range("key not found");
		return  (*(*container)[index])[chainNumber].GetValueRef();
	}
	TValue Get(TKey key) override {
		size_t index = Hash{}(key) % capacity;
		size_t chainNumber = ((*container)[index])->findByValue(Pair<TKey, TValue>(key));
		if (chainNumber == -1)
			throw std::out_of_range("key not found");
		return  (*(*container)[index])[chainNumber].GetValue();
	}
	void Set(TKey key, TValue element) override {
		size_t index = Hash{}(key) % capacity;
		size_t chainNumber = ((*container)[index])->findByValue(Pair<TKey, TValue>(key));
		if (chainNumber == -1)
			throw std::out_of_range("key not found");
		(*(*container)[index])[chainNumber].SetValue(element);
	}
	void Remove(TKey key) override {
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
	bool ContainsKey(TKey key) override {
		size_t index = Hash{}(key) % capacity;
		size_t chainNumber = ((*container)[index])->findByValue(Pair<TKey, TValue>(key));
		return chainNumber != -1;
	}
	shared_ptr<Sequence<TKey>> GetKeys() override {
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
};