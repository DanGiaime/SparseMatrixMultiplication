//
// Created by Daniel Giaime on 12/1/17.
//

#include <iostream>
#include "CompressedSparseRow.h"

void CompressedSparseRow::AddEdge(float val, int row, int col) {
    int start_index = (row == 0) ? 0 : this->row_ptr[row - 1];
    auto itr = this->temp_storage->begin();

    // Get to the start of this row
    for (int i = 0; i < start_index; ++i) {
        ++itr;
    }

    // Get the end of the row so we know if we should insert ourselves
    int end_index = this->row_ptr[row];
    bool placed = false;

    // LinkedList insertion within the current row
    for (int j = start_index; j < end_index; ++j) {
        if(itr->col > col) {
            this->temp_storage->insert(itr, CompressedSparseRowNode(val, col));
            std::cout << "Inserted at not end (" << val << ", " << col << ")" << std::endl;
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
            this->temp_storage->insert(itr, CompressedSparseRowNode(val, col));
            std::cout << "Inserted at end (" << val << ", " << col << ")" << std::endl;
        }
    }

    //Add 1 to this row
    for (int k = row; k < num_rows; ++k) {
        this->row_ptr[k]++;
    }


}

CompressedSparseRow::CompressedSparseRow(int num_edges, int num_rows) : num_rows(num_rows), num_edges(num_edges){
    this->temp_storage = new std::list<CompressedSparseRowNode>();

    // Don't init any values here since we will not use this until we're ready
    this->val = new float[num_edges];

    // Init row counts to zero (all rows begin with 0 items in them)
    this->row_ptr = new int[num_edges];
    std::fill_n(this->row_ptr, num_rows, 0);

    // Init additional array locations to -1 sentinel value
    // meaning this row does not exist (there is no row with -1 items in it)
    std::fill_n(this->row_ptr + num_rows, num_edges - num_rows, -1);

    // Init columns to -1 sentinel value (there is no column -1)
    this->col = new int[num_edges];
    std::fill_n(this->col, num_edges, -1);

}

std::ostream &operator<<(std::ostream &os, const CompressedSparseRow &row) {



    os << "row_ptr:" << std::endl;
    for (int i = 0; i < row.num_rows; ++i) {
        os << "(" << i << ", " << row.row_ptr[i] << "), ";
    }

    auto begin = row.temp_storage->begin();
    auto end = row.temp_storage->end();
    os << "temp_storage:" << std::endl;
    while(begin != end) {
        os << "(" << begin->val << ", " << begin->col << "), ";
        ++begin;
    }

    return os;
}

CompressedSparseRow::~CompressedSparseRow() = default;
