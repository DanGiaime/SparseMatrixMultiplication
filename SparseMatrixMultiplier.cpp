//
// Created by Daniel Giaime on 12/8/17.
//

#include "SparseMatrixMultiplier.h"

SparseMatrixMultiplier::SparseMatrixMultiplier(const CompressedSparseRow &A, const CompressedSparseColumn &B) : A(A),
                                                                                                                B(B) {}

//float **SparseMatrixMultiplier::multiply() {
//    //float new_matrix[A.num_rows][B.num_cols];
//   // auto new_matrix = new float[A.num_rows][B.num_cols];
//    for (int i = 0; i < A.num_rows; ++i) {
//        for (int j = 0; j < B.num_cols; ++j) {
//            //A.row_ptr[]
//        }
//    }
//
//}

//void multiply_single_element(int *row_ptr, int *col_ptr, ) {
//
//}
