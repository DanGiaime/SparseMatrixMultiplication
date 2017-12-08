//
// Created by Daniel Giaime on 12/1/17.
//

#ifndef SPARSEMATRIXMULTIPLICATION_COMPRESSEDSPARSEROW_H
#define SPARSEMATRIXMULTIPLICATION_COMPRESSEDSPARSEROW_H

#include "CompressedSparseRowNode.h"
#include <list>
#include <ostream>

class CompressedSparseRow {
public:
    float *val;
    int *row_ptr;
    int *col;
    int num_rows;
    int num_edges;
    std::list<CompressedSparseRowNode> *temp_storage;
    void AddEdge(float val, int row, int col);
    CompressedSparseRow(int num_edges, int num_rows);
    ~CompressedSparseRow() = default;

    friend std::ostream &operator<<(std::ostream &os, const CompressedSparseRow &row);
};



#endif //SPARSEMATRIXMULTIPLICATION_COMPRESSEDSPARSEROW_H
