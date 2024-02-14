#pragma once
#include "IDictionary.h"
#include "smart_ptrs/shared_ptr.h"
#include "smartPtrPairComparator.h"
#include "SortedSequence.h"

template <typename TKey, typename TValue>
class SortedSequenceDictionary : public IDictionary<TKey, TValue> {
protected:
    shared_ptr<SortedSequence<shared_ptr<Pair<TKey, TValue>>>> sortedSequence;
    shared_ptr<Pair<TKey, TValue>> nullValuePair(const TKey key) {
        return make_shared<Pair<TKey, TValue>>(key);
    }
public:
    SortedSequenceDictionary() : sortedSequence(new SortedSequence<shared_ptr<Pair<TKey, TValue>>>(smartPtrPairComparator, smartPtrPairEqual)) {}
    SortedSequenceDictionary(shared_ptr<Sequence<TKey>> keys, shared_ptr<Sequence<TValue>> values) {
        if (keys->GetLength() != values->GetLength()) 
            throw std::invalid_argument("Keys and values sequences must have the same size");
        shared_ptr<Sequence<shared_ptr<Pair<TKey, TValue>>>> pairs(new ArraySequence<shared_ptr<Pair<TKey, TValue>>>() );
        auto eKey = keys->GetEnumerator();
        auto eValue = values->GetEnumerator();
        while (eKey->next() && eValue->next()) {
            pairs->Append(make_shared<Pair<TKey,TValue>>(*(*eKey), *(*eValue)));
        }
        sortedSequence = shared_ptr<SortedSequence<shared_ptr<Pair<TKey, TValue>>>>(new SortedSequence<shared_ptr<Pair<TKey, TValue>>>(pairs, smartPtrPairComparator, smartPtrPairEqual));
    }
    void Add(TKey key, TValue value) override {
        sortedSequence->Add(make_shared<Pair<TKey, TValue>>(key, value));
    }
    bool ContainsKey(TKey key) override {
        return sortedSequence->IndexOf(nullValuePair(key)) != -1;
    }
    TValue Get(TKey key) override {
        return sortedSequence->Get(nullValuePair(key))->GetValue();
    }
    void Set(TKey key, TValue value) override {
        sortedSequence->Get(nullValuePair(key))->SetValue(value);
    }
    int GetLength() override {
        return sortedSequence->GetLength();
    }
    TValue& operator[] (const TKey key) override {
        return sortedSequence->Get(nullValuePair(key))->GetValueRef();
    }
};
