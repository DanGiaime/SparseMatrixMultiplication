//
// Created by Daniel Giaime on 12/8/17.
//

#ifndef SPARSEMATRIXMULTIPLICATION_SPARSEMATRIXMULTIPLIER_H
#define SPARSEMATRIXMULTIPLICATION_SPARSEMATRIXMULTIPLIER_H


#include "CompressedSparseRow.h"
#include "CompressedSparseColumn.h"

class SparseMatrixMultiplier {
public:
    CompressedSparseRow A;
    CompressedSparseColumn B;
    float** multiply();
    SparseMatrixMultiplier(const CompressedSparseRow &A, const CompressedSparseColumn &B);
private:
    //void multiply_single_element(auto row_start, auto row_end, auto col_start, auto col_end);
};


#endif //SPARSEMATRIXMULTIPLICATION_SPARSEMATRIXMULTIPLIER_H
