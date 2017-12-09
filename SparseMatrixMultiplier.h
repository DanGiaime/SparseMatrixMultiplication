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
    void multiply_single_element(int row_start, int row_end, int col_start, int col_end, float *out, int answer_col);
};


#endif //SPARSEMATRIXMULTIPLICATION_SPARSEMATRIXMULTIPLIER_H
