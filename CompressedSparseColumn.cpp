//
// Created by Daniel Giaime on 12/8/17.
//

#include <iostream>
#include "CompressedSparseColumn.h"

/// Add an edge to the column structure
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
        // If we're at the literal end of the entire list, emplace_back so we don't go too far
        if (itr == temp_storage->end()) {
            this->temp_storage->push_back(CompressedSparseColumnNode(val, row));
        }
        else {
            this->temp_storage->insert(itr, CompressedSparseColumnNode(val, row));
        }
    }

    //Add 1 to this row, update other columns correspondingly
    for (int k = col; k < num_cols; ++k) {
        this->col_ptr[k]++;
    }

    // If we've read in every edge, write to our arrays
    if(col_ptr[num_cols - 1] == num_edges) {
        ConvertFromTempStorage();
    }
}

/// Create a CompressedSparseColumn from a number of edges and cols
CompressedSparseColumn::CompressedSparseColumn(int num_edges, int num_cols) : num_cols(num_cols), num_edges(num_edges){
    this->temp_storage = new std::list<CompressedSparseColumnNode>();

    // Don't init any values here since we will not use this until we're ready
    this->val = new float[num_edges];

    // Init row counts to zero (all rows begin with 0 items in them)
    this->col_ptr = new int[num_cols];
    std::fill_n(this->col_ptr, num_cols, 0);

    // Init columns to -1 sentinel value (there is no row -1)
    this->row = new int[num_edges];
    std::fill_n(this->row, num_edges, -1);

}

std::ostream &operator<<(std::ostream &os, const CompressedSparseColumn &col) {

    os << "col_ptr:" << std::endl;
    for (int i = 0; i < col.num_cols; ++i) {
        os << "(" << i << ", " << col.col_ptr[i] << "), ";
    }
    os << std::endl;


    os << "rows and vals:" << std::endl;
    for (int j = 0; j < col.num_edges; ++j) {
        os << "(" << col.val[j] << ", " << col.row[j] << "), ";
    }


    return os;
}

/// Once we've ordered all the edges, move them into the array
void CompressedSparseColumn::ConvertFromTempStorage() {
    auto curr = temp_storage->begin();
    for (int i = 0; i < num_edges; ++i) {
        val[i] = curr->val;
        row[i] = curr->row;
        ++curr;
    }
}

/// Returns the index into row[] that is the start of the given row
int CompressedSparseColumn::GetStartOfColumn(int col) {
    int begin_index = (col == 0) ? 0 : this->col_ptr[col - 1];
    return begin_index;
}

/// Returns the index into row[] that is the end of the given row
int CompressedSparseColumn::GetEndOfColumn(int col) {
    int end_index = this->col_ptr[col];
    return end_index;
}

CompressedSparseColumn::~CompressedSparseColumn() {
    delete temp_storage;
    delete [] row;
    delete [] val;
    delete [] col_ptr;
}

