//
// Created by Daniel Giaime on 12/8/17.
//

#include <iostream>
#include <thread>
#include <vector>
#include "SparseMatrixMultiplier.h"

SparseMatrixMultiplier::SparseMatrixMultiplier(const CompressedSparseRow &A, const CompressedSparseColumn &B) : A(A),
                                                                                                                B(B) {}

float** SparseMatrixMultiplier::multiply() {

    auto **answer_matrix = new float*[A.num_rows];
    for (int k = 0; k < A.num_rows; ++k) {
        answer_matrix[k] = new float[B.num_cols];
    }

    std::vector<std::thread> threads;

    // Iterate over all rows in A
    for (int i = 0; i < A.num_rows; ++i) {
        int row_start = A.GetStartOfRow(i);
        int row_end = A.GetEndOfRow(i);

        // Iterate over all columns in B
        for (int j = 0; j < B.num_cols; ++j) {
            int col_start = B.GetStartOfColumn(j);
            int col_end = B.GetEndOfColumn(j);

            // This is where syntax starts to get really misleading
            // We're looping over all entries in this column
            // We're checking the row value of each entry in this column
            // Then we're going to perform a merge-sort-esque multiplication
            // Since this is entirely read based right up until we
            // write the value to the output matrix, we can make
            // each (row of A * col of B) calculation into a separate thread
            if((row_start != row_end) && (col_start != col_end)) {
                threads.emplace_back(
                        std::thread(&SparseMatrixMultiplier::multiply_single_element, this, row_start, row_end,
                                    col_start, col_end, answer_matrix[i], j));
            }
            else {
                answer_matrix[i][j] = 0;
            }
        }
    }

    auto curr = threads.begin();
    auto end = threads.end();
    while(curr != end) {
        curr->join();
        ++curr;
    }

    return answer_matrix;

}

/// This function multiplies one row of A by one column of B
void SparseMatrixMultiplier::multiply_single_element(int row_start, int row_end, int col_start, int col_end,
                                                      float *out, int answer_col) {

    // Here comes some merge-sort ish multiplication
    // We need to move between each array depending on where the elements lie
    // I am going to refer to the position in the row of A / col of B as the index
    // That is to say, the 5th item in a given col of B has an index of 5.

    // With all that said, the algorithm will go as follows.
    // Begin at start of row for row pointer
    int row_curr = row_start;

    // Begin at start of col for col pointer
    int col_curr = col_start;

    float total = 0;

    // Iterate until we've reached the end of the row or col
    while(row_curr != row_end && col_curr != col_end) {

        // This syntax is confusing, but all it does is get the index
        // Into the row of A and the col of B
        // The names are misleading, you may want to look at the structure
        // To fully understand why this is
        int row_index = A.col[row_curr];
        int col_index = B.row[col_curr];

        // If index into row == index into col
        // We have two corresponding numbers we can multiply
        if(row_index == col_index) {
            total += A.val[row_curr] * B.val[col_curr];
            row_curr++;
            col_curr++;
        }
        else if (row_index < col_index) {
            row_curr++;
        }
        else {
            col_curr++;
        }
    }

    // Total is now the value of this element in the matrix;
    out[answer_col] = total;

}
