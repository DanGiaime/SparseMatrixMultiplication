#include <iostream>
#include "CompressedSparseRow.h"
#include "CompressedSparseColumn.h"
#include "SparseMatrixMultiplier.h"

int main() {

    // Parse input sizes
    std::cout << "Please enter dimensions of matrix A." << std::endl;
    int a_m;
    int a_n;
    std::cin >> a_m;
    std::cin >> a_n;
    std::cout << "Please enter dimensions of matrix B." << std::endl;
    int b_m;
    int b_n;
    std::cin >> b_m;
    std::cin >> b_n;
    std::cout << "Please enter number of edges in matrix A." << std::endl;
    int a_num_edges;
    std::cin >> a_num_edges;
    std::cout << "Please enter number of edges in matrix b." << std::endl;
    int b_num_edges;
    std::cin >> b_num_edges;

    // Parse edges for A
    auto *A = new CompressedSparseRow(a_num_edges, a_m);
    std::cout << "Please enter each edge in A in val row col order" << std::endl;

    int val;
    int row;
    int col;
    for (int i = 0; i < a_num_edges; ++i) {
        std::cin >> val;
        std::cin >> row;
        std::cin >> col;
        A->AddEdge(val, row, col);
    }

    //std::cout << A;

    auto *B = new CompressedSparseColumn(b_num_edges, b_m);
    std::cout << "Please enter each edge in B in val row col order" << std::endl;

    for (int i = 0; i < b_num_edges; ++i) {
        std::cin >> val;
        std::cin >> row;
        std::cin >> col;
        B->AddEdge(val, col, row);
    }

    //std::cout << B;

    SparseMatrixMultiplier smm(*A, *B);
    float** output = smm.multiply();
//    std::flush(std::cout);
//    std::cout << std::endl;

    for (int j = 0; j < A->num_rows; ++j) {
        for (int i = 0; i < B->num_cols; ++i) {
            std::cout << output[j][i] << "   ";
        }
        std::cout << std::endl;
    }
    //std::flush(std::cout);


    return 0;
}