# Sparse Matrix Multiplication
### Overview
The goal of this project was to implement a simple Sparse Matrix Multiplication Algorithm. The basic idea is to avoid doing a full matrix multiplication since the matrices are mostly zeros. We achieve this by storing the matrices in structures that store only non-zero entries, then apply a simple algorithm to multiply these structures.

### Structures
This project took advantage of two different, yet very similar Data Structures for an easy multiplication algorithm. The two Data Structures are known as CompressedSparseRow and CompressedSparseColumn. Given their similarity I will describe only one.

__CompressedSparseRow__

The CompressedSparseRow is a structure designed around representing a Sparse Matrix with easy row access. That is to say, we can easily iterate over a row, but not a column. In this project, I choose to represent the first matrix being multiplied in this format, as we will be accessing that matrix in a row by row fashion.

The structure holds 3 arrays - val, col, and rowPtr

val/col are two parallel arrays, holding both the value and the column of different entries. You can in essence think of these two arrays as one, hold tuples of (value, column) for each entry in the matrix.

rowPtr is the key to what makes this structure interesting. the value in each index of rowPtr is the number of entries in that row and all rows prior. We use this structure in combination with val/col for easy row access as follows:

We fill val/col in sorted row, then sorted column order. For example, this matrix:

005  
608  
079

Would have the following values for val/col:  
(5, 3), (6, 1), (8, 3), (7, 2), (9, 3)  
[Note: columns are 1 indexed]

Note that all entries are in order of their row (row 1 comes before row 2) but within a row sublist, we are sorted by columns (in row 2, 6 comes before 8 since 6 is in column 1).

Now that we have this list, we can fill out rowPtr so we can easily access a given row. We fill our rowPtr with the number of elements in this row + the number of elements in all previous rows. We start the array with 0 since there is no 0th row.

Our val/col is split up into rows as such  
(5, 3) || (6, 1), (8, 3) || (7, 1), (9, 3)  
Therefore, our rowPtr will be the following  
[0, 1, 3, 5]  
Since there is 1 entry in row 1, 2 entires in row 2, and 2 entries in row 3.

Now, we have our full structure as follows  
val/col: (5, 3), (6, 1), (8, 3), (7, 2), (9, 3)  
rowPtr: [0, 1, 3, 5]

We can now access a given row by simply iterating from rowPtr[currRowNum-1] to rowPtr[currRowNum], as rowPtr[currRowNum-1] will return the start index into col/val of the current row, while rowPtr[currRowNum] will return the end index into col/val of the current row. So, if I wanted to access all entries in val/col that are in row 2, I would start at index rowPtr[2-1] = rowPtr[1] = 1, and end at index rowPtr[2] = 3. This would give me exactly (6, 1), (8, 3) which is exactly row 2 of the matrix.

The CompressedSparseColumn structure mimics exactly this structure, but instead holds (val, row) tuples and has a colPtr instead of a rowPtr.

### Algorithm
