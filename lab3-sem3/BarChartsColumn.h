#pragma once

#include "Sequence.h"
#include "smart_ptrs/shared_ptr.h"
#include "baseComparator.h"
#include "ISortedSequence.h"
#include "SortedSequenceDictionary.h"
#include "Sequence.h"

template <typename TObject> class Column {
    shared_ptr<Sequence<TObject>> columnValues;
    Column()
}