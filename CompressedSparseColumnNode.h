//
// Created by Daniel Giaime on 12/8/17.
//

#ifndef SPARSEMATRIXMULTIPLICATION_COMPRESSEDSPARSECOLUMNNODE_H
#define SPARSEMATRIXMULTIPLICATION_COMPRESSEDSPARSECOLUMNNODE_H


class CompressedSparseColumnNode {
public:
    float val;
    int row;
    CompressedSparseColumnNode(float val = 0, int row = 0);
    virtual ~CompressedSparseColumnNode() = default;
};


#endif //SPARSEMATRIXMULTIPLICATION_COMPRESSEDSPARSECOLUMNNODE_H
