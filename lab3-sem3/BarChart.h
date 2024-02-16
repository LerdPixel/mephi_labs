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
    shared_ptr<IDictionary<Range, shared_ptr<Sequence<TObject>>>> barChartRangeDict;
    std::optional<Range> findNumInRanges(double number) {
        return sortedRanges->Get(Range(number, number));
    }
    void rangeDictCreator() { // sortedRanges must already be created
        shared_ptr<Sequence<shared_ptr<Sequence<TObject>>>> seq(new ArraySequence<shared_ptr<Sequence<TObject>>>());   
        for (int i = 0; i < sortedRanges->GetLength(); ++i) {
            seq->Append(shared_ptr<Sequence<TObject>>(new ArraySequence<TObject>()));
        }
        barChartRangeDict = shared_ptr<IDictionary<Range, shared_ptr<Sequence<TObject>>>>(new SortedSequenceDictionary<Range, shared_ptr<Sequence<TObject>>>(_ranges, seq));
    }
    //shared_ptr<Sequence<shared_ptr<Sequence<TObject>>>> SequenceOfSequenceGenerator
public:
    BarChart(shared_ptr<Sequence<TObject>> objects, shared_ptr<Sequence<Range>> ranges, double (*f)(TObject)) : sortedRanges(new SortedSequence<Range>(ranges, baseComparator, BarChart::rangeCmp)), _ranges(ranges) {
        rangeDictCreator();
        auto e = objects->GetEnumerator();
        while (e->next()) {
            auto range = findNumInRanges(f(*(*e)));
            if (range) {
                (*barChartRangeDict)[*range]->Append(*(*e));
            }
        }
    }
    shared_ptr<IDictionary<Range, int>> GetChart() {
        shared_ptr<IDictionary<Range, int>> chart = shared_ptr<IDictionary<Range, int>>( new SortedSequenceDictionary<Range, int>());
        if (barChartRangeDict) {
            auto e = _ranges->GetEnumerator();
            while(e->next()) {
                chart->Add(**e, barChartRangeDict->Get(**e)->GetLength());
            } 
            return chart;
        }
        return chart;
    }
    //auto GetSequenceChart() {}
};
