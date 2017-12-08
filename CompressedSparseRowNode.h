//
// Created by Daniel Giaime on 12/1/17.
//

#ifndef SPARSEMATRIXMULTIPLICATION_COMPRESSEDSPARSEROWNODE_H
#define SPARSEMATRIXMULTIPLICATION_COMPRESSEDSPARSEROWNODE_H


class CompressedSparseRowNode {
public:
    float val;
    int col;
    CompressedSparseRowNode(float val = 0, int col = 0);
    virtual ~CompressedSparseRowNode() = default;
};


#endif //SPARSEMATRIXMULTIPLICATION_COMPRESSEDSPARSEROWNODE_H
