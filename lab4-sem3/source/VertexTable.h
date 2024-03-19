#pragma once
#include "containers/smart_ptrs/shared_ptr.h"
#include "containers/HashTable.h"
#include "containers/Sequence.h"
#include "containers/Matrix.h"

template<typename TVertex>
class VertexTable {
private:
    shared_ptr<Matrix<bool>> matrix;
    shared_ptr<HashTable<TVertex, bool>> hashTable;
public:
    VertexTable(shared_ptr<Sequence<TVertex>> verticies) {
        matrix = shared_ptr<Matrix<bool>>(new Matrix<bool>(verticies->GetLength(), verticies->GetLength()));
        HashTable = shared_ptr<HashTable<TVertex, bool>>(new HashTable<TVertex, bool>(verticies->GetLength()));
        auto e = verticies->GetEnumerator();
        while (e->next()) {
            hashTable->Add(**e, false);
        }
    }
    void SetBond(TVertex vertex1, TVertex vertex2, bool value) {
        return matrix->Set(hashTable->Get(vertex1), hashTable->Get(vertex2), value);
    }
    void MarkBond(TVertex vertex1, TVertex vertex2) {
        return matrix->Set(hashTable->Get(vertex1), hashTable->Get(vertex2), true);
    }
    bool GetBond(TVertex vertex1, TVertex vertex2) const {
        return matrix->Get(hashTable->Get(vertex1), hashTable->Get(vertex2));
    }
};
