//
// Created by Daniel Giaime on 12/8/17.
//

#include <iostream>
#include "CompressedSparseColumn.h"

void CompressedSparseColumn::AddEdge(float val, int col, int row) {
    int start_index = (col == 0) ? 0 : this->col_ptr[col - 1];
    auto itr = this->temp_storage->begin();

    // Get to the start of this row
    for (int i = 0; i < start_index; ++i) {
        ++itr;
    }

    // Get the end of the row so we know if we should insert ourselves
    int end_index = this->col_ptr[col];
    bool placed = false;

    // LinkedList insertion within the current row
    for (int j = start_index; j < end_index; ++j) {
        if(itr->row > row) {
            this->temp_storage->insert(itr, CompressedSparseColumnNode(val, row));
            std::cout << "Inserted at not end (" << val << ", " << row << ")" << std::endl;
            placed = true;
            break;
        }
        else {
            ++itr;
        }
    }

    // Get end of row pointer so we can find out if we inserted or if this should go at end of list
    if(!placed) {
        auto end_itr = this->temp_storage->begin();
        for (int j = 0; j < end_index; ++j) {
            ++end_itr;
        }

        // If we haven't inserted put at end of list
        if (itr == end_itr) {
            this->temp_storage->insert(itr, CompressedSparseColumnNode(val, row));
            std::cout << "Inserted at end (" << val << ", " << row << ")" << std::endl;
        }
    }

    //Add 1 to this row, update other columns correspondingly
    for (int k = col; k < num_cols; ++k) {
        this->col_ptr[k]++;
    }


}

CompressedSparseColumn::CompressedSparseColumn(int num_edges, int num_cols) : num_cols(num_cols), num_edges(num_edges){
    this->temp_storage = new std::list<CompressedSparseColumnNode>();

    // Don't init any values here since we will not use this until we're ready
    this->val = new float[num_edges];

    // Init row counts to zero (all rows begin with 0 items in them)
    this->col_ptr = new int[num_edges];
    std::fill_n(this->col_ptr, num_cols, 0);

    // Init additional array locations to -1 sentinel value
    // meaning this row does not exist (there is no row with -1 items in it)
    std::fill_n(this->col_ptr + num_cols, num_edges - num_cols, -1);

    // Init columns to -1 sentinel value (there is no column -1)
    this->row = new int[num_edges];
    std::fill_n(this->row, num_edges, -1);

}

std::ostream &operator<<(std::ostream &os, const CompressedSparseColumn &col) {



    os << "row_ptr:" << std::endl;
    for (int i = 0; i < col.num_cols; ++i) {
        os << "(" << i << ", " << col.col_ptr[i] << "), ";
    }

    auto begin = col.temp_storage->begin();
    auto end = col.temp_storage->end();
    os << "temp_storage:" << std::endl;
    while(begin != end) {
        os << "(" << begin->val << ", " << begin->row << "), ";
        ++begin;
    }

    return os;
}
