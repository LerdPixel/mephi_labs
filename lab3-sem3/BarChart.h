#pragma once
#include "Sequence.h"
#include "smart_ptrs/shared_ptr.h"
#include "baseComparator.h"
#include "SortedSequence.h"
#include "SortedSequenceDictionary.h"
#include "Sequence.h"
#include "Range.h"

template<typename TKey, typename TObject> 
class BarChart {
private:
    static bool rangeCmp(Range r1, Range r2) { return r1.has(r2); }
    shared_ptr<SortedSequence<Range>> sortedRanges;
    shared_ptr<Sequence<Range>> _ranges;
    shared_ptr<IDictionary<TKey, shared_ptr<Sequence<TObject>>>> barChartDict;
    std::optional<Range> findNumInRanges(double number) {
        return sortedRanges->Get(Range(number, number));
    }
    void rangeDictCreator() { // sortedRanges must already be created
        shared_ptr<Sequence<shared_ptr<Sequence<TObject>>>> seq(new ArraySequence<shared_ptr<Sequence<TObject>>>());   
        for (int i = 0; i < sortedRanges->GetLength(); ++i) {
            seq->Append(shared_ptr<Sequence<TObject>>(new ArraySequence<TObject>()));
        }
        barChartDict = shared_ptr<IDictionary<Range, shared_ptr<Sequence<TObject>>>>(new SortedSequenceDictionary<Range, shared_ptr<Sequence<TObject>>>(_ranges, seq));
    }
public:
    BarChart(shared_ptr<Sequence<TObject>> objects, shared_ptr<Sequence<Range>> ranges, double (*f)(TObject)) : sortedRanges(new SortedSequence<Range>(ranges, baseComparator, BarChart::rangeCmp)), _ranges(ranges) {
        rangeDictCreator();
        auto e = objects->GetEnumerator();
        while (e->next()) {
            auto range = findNumInRanges(f(*(*e)));
            if (range) {
                (*barChartDict)[*range]->Append(*(*e));
            }
        }
    }
    BarChart(shared_ptr<Sequence<TObject>> objects, TKey (*f)(TObject)) {
        barChartDict = shared_ptr<IDictionary<TKey, shared_ptr<Sequence<TObject>>>>(new SortedSequenceDictionary<TKey, shared_ptr<Sequence<TObject>>>());
        auto e = objects->GetEnumerator();
        while (e->next()) {
            TKey key = (f(*(*e)));
            if (barChartDict->ContainsKey(key)) {
                (*barChartDict)[key]->Append(*(*e));
            } else {
                auto newSeq = shared_ptr<Sequence<TObject>>(new ArraySequence<TObject>());
                newSeq->Append( *(*e) );
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
