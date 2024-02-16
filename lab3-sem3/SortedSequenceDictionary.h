#pragma once
#include "IDictionary.h"
#include "smart_ptrs/shared_ptr.h"
#include "smartPtrPairComparator.h"
#include "SortedSequence.h"

template <typename TKey, typename TValue>
class SortedSequenceDictionary : public IDictionary<TKey, TValue> {
protected:
    typedef SortedSequence<shared_ptr<Pair<TKey, TValue>>> SortedPairs;
    shared_ptr<SortedPairs> sortedSequence;
    shared_ptr<Pair<TKey, TValue>> nullValuePair(const TKey key) {
        return shared_ptr<Pair<TKey, TValue>>(new Pair<TKey, TValue>(key));
    }
public:
    SortedSequenceDictionary() : sortedSequence(new SortedPairs(smartPtrPairComparator, smartPtrPairEqual)) {}

    SortedSequenceDictionary(shared_ptr<Sequence<TKey>> keys, shared_ptr<Sequence<TValue>> values) {
        if (keys->GetLength() != values->GetLength()) 
            throw std::invalid_argument("Keys and values sequences must have the same size");
        shared_ptr<Sequence<shared_ptr<Pair<TKey, TValue>>>> pairs(new ArraySequence<shared_ptr<Pair<TKey, TValue>>>() );
        auto eKey = keys->GetEnumerator();
        auto eValue = values->GetEnumerator();
        while (eKey->next() && eValue->next()) {
            pairs->Append(shared_ptr<Pair<TKey,TValue>>(new Pair<TKey,TValue>(*(*eKey), *(*eValue))));
        }
        sortedSequence = shared_ptr<SortedPairs>(new SortedPairs(pairs, smartPtrPairComparator, smartPtrPairEqual));
    }
    void Add(TKey key, TValue value) override {
        sortedSequence->Add(shared_ptr<Pair<TKey, TValue>>(new Pair<TKey, TValue>(key, value)));
    }
    bool ContainsKey(TKey key) override {
        return sortedSequence->IndexOf(nullValuePair(key)) != -1;
    }
    TValue Get(TKey key) override {
        return sortedSequence->Get(nullValuePair(key)).value()->GetValue();
    }
    void Set(TKey key, TValue value) override {
        sortedSequence->Get(nullValuePair(key)).value()->SetValue(value);
    }
    int GetLength() override {
        return sortedSequence->GetLength();
    }
    TValue& operator[] (const TKey key) override {
        return sortedSequence->Get(nullValuePair(key)).value()->GetValueRef();
    }
    void Remove (TKey key) override { 
        sortedSequence->Remove(nullValuePair(key));
    }
    shared_ptr<Sequence<TKey>> GetKeys() override {
        auto SSdata = sortedSequence->GetValues();
        auto keys = shared_ptr<Sequence<TKey>>(new ArraySequence<TKey>());
        auto e = SSdata->GetEnumerator();
        while (e->next()) {
            keys->Append((**e)->GetKey());
        }
        return keys;
    }
};
