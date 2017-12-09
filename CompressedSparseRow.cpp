//
// Created by Daniel Giaime on 12/1/17.
//

#include <iostream>
#include "CompressedSparseRow.h"

/// Add an edge to the row structure
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

        auto end_of_list_itr = temp_storage->end();
        end_of_list_itr++;


        // If we haven't inserted put at end of list
        if (itr == end_of_list_itr) {
            this->temp_storage->push_back(CompressedSparseRowNode(val, col));
        }
        else {
            this->temp_storage->insert(itr, CompressedSparseRowNode(val, col));
        }
    }

    //Add 1 to this row
    for (int k = row; k < num_rows; ++k) {
        this->row_ptr[k]++;
    }

    // If we've read in every edge, write to our arrays
    if(row_ptr[num_rows - 1] == num_edges) {
        ConvertFromTempStorage();
    }

    //std::cout << *this;

}

/// Create a CompressedSparseRow from a number of edges and rows
CompressedSparseRow::CompressedSparseRow(int num_edges, int num_rows) : num_rows(num_rows), num_edges(num_edges){
    this->temp_storage = new std::list<CompressedSparseRowNode>();

    // Don't init any values here since we will not use this until we're ready
    this->val = new float[num_edges];

    // Init row counts to zero (all rows begin with 0 items in them)
    this->row_ptr = new int[num_rows];
    std::fill_n(this->row_ptr, num_rows, 0);

    // Init columns to -1 sentinel value (there is no column -1)
    this->col = new int[num_edges];
    std::fill_n(this->col, num_edges, -1);

}

/// Print out structure
std::ostream &operator<<(std::ostream &os, const CompressedSparseRow &row) {

    os << "row_ptr:" << std::endl;
    for (int i = 0; i < row.num_rows; ++i) {
        os << "(" << i << ", " << row.row_ptr[i] << "), ";
    }

    os << "columns and vals:" << std::endl;
    for (int j = 0; j < row.num_edges; ++j) {
        os << "(" << row.val[j] << ", " << row.col[j] << "), ";
    }

    return os;
}

/// Returns the index into col[] that is the start of the given row
int CompressedSparseRow::GetStartOfRow(int row) {
    int start_index = (row == 0) ? 0 : this->row_ptr[row - 1];
    return start_index;
}

/// Returns the index into col[] that is the end of the given row
int CompressedSparseRow::GetEndOfRow(int row) {
    int end_index = this->row_ptr[row];
    return end_index;
}

/// Once we've ordered all the edges, move them into the array
void CompressedSparseRow::ConvertFromTempStorage() {
    auto curr = temp_storage->begin();
    for (int i = 0; i < num_edges; ++i) {
        val[i] = curr->val;
        col[i] = curr->col;
        ++curr;
    }
}

CompressedSparseRow::~CompressedSparseRow() {
    delete temp_storage;
    delete [] col;
    delete [] val;
    delete [] row_ptr;
}


