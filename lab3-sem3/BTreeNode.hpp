#pragma once
#include "Sequence.h"
#include "smart_ptrs/shared_ptr.h"

template <typename T> class BPlusTreeNode {
private:
    shared_ptr<Sequence<T>> data;
    shared_ptr<Sequence<shared_ptr<BTreeNode>>> nodePointers;
    bool isLeaf;
public:
    BTreeNode() {

    }
}