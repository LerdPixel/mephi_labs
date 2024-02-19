#pragma once
#include "Sequence.h"
#include "smart_ptrs/shared_ptr.h"
#include "baseComparator.h"
#include "ISortedSequence.h"
#include "SortedSequenceDictionary.h"
#include "Sequence.h"

template<typename TKey, typename TObject> 
class BarChart {
private:
    shared_ptr<IDictionary<TKey, shared_ptr<Sequence<TObject>>>> barChartDict;

    void adjustedKeysDictCreator(shared_ptr<ISortedSequence<TKey>> adjustedKeys) {
        shared_ptr<Sequence<shared_ptr<Sequence<TObject>>>> seq(new ArraySequence<shared_ptr<Sequence<TObject>>>());   
        for (int i = 0; i < adjustedKeys->GetLength(); ++i) {
            seq->Append(shared_ptr<Sequence<TObject>>(new ArraySequence<TObject>()));
        }
        barChartDict = shared_ptr<IDictionary<TKey, shared_ptr<Sequence<TObject>>>>(new SortedSequenceDictionary<TKey, shared_ptr<Sequence<TObject>>>(adjustedKeys->GetValues(), seq));
    }
public:
    BarChart(shared_ptr<Sequence<TObject>> objects, TKey (*f)(const TObject&), shared_ptr<ISortedSequence<TKey>> adjustedKeys) {
        adjustedKeysDictCreator(adjustedKeys);
        auto e = objects->GetEnumerator();
        while (e->next()) {
            auto objectKey = adjustedKeys->Get(f(**e));
            if (objectKey.has_value()) {
                (*barChartDict)[*objectKey]->Append(**e);
            }
        }
    }
    BarChart(shared_ptr<Sequence<TObject>> objects, const TKey& (*f)(const TObject&)) {
        barChartDict = shared_ptr<IDictionary<TKey, shared_ptr<Sequence<TObject>>>>(new SortedSequenceDictionary<TKey, shared_ptr<Sequence<TObject>>>());
        auto e = objects->GetEnumerator();
        while (e->next()) {
            TKey key = (f(**e));
            if (barChartDict->ContainsKey(key)) {
                (*barChartDict)[key]->Append(**e);
            } else {
                auto newSeq = shared_ptr<Sequence<TObject>>(new ArraySequence<TObject>());
                newSeq->Append(**e);
                barChartDict->Add(key, newSeq);
            }
        }
    }
    shared_ptr<IDictionary<TKey, int>> GetChart() {
        shared_ptr<IDictionary<TKey, int>> chart = shared_ptr<IDictionary<TKey, int>>( new SortedSequenceDictionary<TKey, int>());
        auto keys = barChartDict->GetKeys();
        auto e = keys->GetEnumerator();
        while(e->next()) {
            chart->Add(**e, barChartDict->Get(**e)->GetLength());
        } 
        return chart;
    }
    shared_ptr<IDictionary<TKey, shared_ptr<Sequence<TObject>>>> GetSequenceChart() {
        return barChartDict;
    }
};
