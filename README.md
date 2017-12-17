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

0 0 5  
6 0 8  
0 7 9

Would have the following values for val/col:  
(5, 3), (6, 1), (8, 3), (7, 2), (9, 3)  
[Note: columns are 1 indexed]

Note that all entries are in order of their row (row 1 comes before row 2) but within a row sublist, we are sorted by columns (in row 2, 6 comes before 8 since 6 is in column 1).

Now that we have this list, we can fill out rowPtr so we can easily access a given row. We fill our rowPtr with the number of elements in this row + the number of elements in all previous rows. We start the array with 0 since there is no 0th row.

Our val/col is split up into rows as such  
(5, 3) || (6, 1), (8, 3) || (7, 1), (9, 3)  
Therefore, our rowPtr will be the following  
[0, 1, 3, 5]  
Since there is 1 entry in row 1, 2 entries in row 2, and 2 entries in row 3.

Now, we have our full structure as follows  
val/col: (5, 3), (6, 1), (8, 3), (7, 2), (9, 3)  
rowPtr: [0, 1, 3, 5]

We can now access a given row by simply iterating from rowPtr[currRowNum-1] to rowPtr[currRowNum], as rowPtr[currRowNum-1] will return the start index into col/val of the current row, while rowPtr[currRowNum] will return the end index into col/val of the current row. So, if I wanted to access all entries in val/col that are in row 2, I would start at index rowPtr[2-1] = rowPtr[1] = 1, and end at index rowPtr[2] = 3. This would give me exactly (6, 1), (8, 3) which is exactly row 2 of the matrix.

The CompressedSparseColumn structure mimics exactly this structure, but instead holds (val, row) tuples and has a colPtr instead of a rowPtr.

### Algorithm
The algorithm for multiplying these structures is very simple. In essence, these structures provide us access to a Linked List representing a row and a LinkedList representing a column, and we want to multiply these. These are multiplied as a normal dot product, so our goal is to find all entries in the same "index" into the row/column, multiply them, and add those numbers together to get our result.

For example, say we have the row [0 0 2 0] and the column [1 1 4 0]. The result of our multiplication would be 0*1 + 0*1 + 2*4 + 0*0 = 8. As we can see, the only numbers to actually result in any calculation are 2 and 4 since they are at the same index and are both non-zero. In our structure we do not have any representation for zeros, so we instead have our row as [(2, 3)] and our column as [(1, 1), (1, 2), (4, 3)]. Since we no longer have the zeros, we need to add a bit to our multiplication algorithm.

Instead of just multiplying entry by entry, we have to find all matching entries (i.e. an entry that is non-zero in both the row and the column at the same index) in our structure. We do this with an approach similar to the "merge" from mergesort. When merging in mergesort, we iterate over two arrays, picking an item from either list and moving that list's pointer over. In this case, we'll attempt something similar.

We start with pointers at the beginning of the row and column. We check the index of the current entry. If the row entry index < column entry index, we move the row pointer forward. If column entry index < row entry index, we move the column pointer forward. If the row entry index == the column entry index, we multiply the two values, add them to the total, and increment both pointers. When we've reached the end of either the row or the column, we stop and write the total to the correct slot of the matrix.

This algorithm provides itself well to multithreading (just as normal matrix multiplication does) if we split up every row and column mult. into a single function. Since we only read from the input matrices and write only once to each location in the output matrix, there is no need for any amount of locking. All in all, this algorithm runs extremely quickly, and I'm very happy with how it came out.
