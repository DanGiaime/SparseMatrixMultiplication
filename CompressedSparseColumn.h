//
// Created by Daniel Giaime on 12/8/17.
//

#ifndef SPARSEMATRIXMULTIPLICATION_COMPRESSEDSPARSECOLUMN_H
#define SPARSEMATRIXMULTIPLICATION_COMPRESSEDSPARSECOLUMN_H


#include <list>
#include "CompressedSparseColumnNode.h"

class CompressedSparseColumn {
public:
    float *val;
    int *col_ptr;
    int *row;
    int num_cols;
    int num_edges;
    std::list<CompressedSparseColumnNode> *temp_storage;
    void AddEdge(float val, int col, int row);
    CompressedSparseColumn(int num_edges, int num_cols);
    ~CompressedSparseColumn() = default;

    friend std::ostream &operator<<(std::ostream &os, const CompressedSparseColumn &col);
};


#endif //SPARSEMATRIXMULTIPLICATION_COMPRESSEDSPARSECOLUMN_H
