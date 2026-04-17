# Matrix-Library
A powerful C library for matrix manipulation and linear algebra. This project provides a structured way to handle matrices, solve systems of equations, and perform complex algebraic operations with memory safety in mind.
## Key Features:
   1. Basic Arithmetic: Addition, subtraction, and multiplication of two Matrices.
   2. Transformations: Transpose and scalar multiplication of a Matrix.
   3. Properties: Check for Identity, Symmetry, and Square matrices.
   4. Advanced Algebra:
      * Determinant Calculation: Recursive calculation using minors.
      * Matrix Inversion: Using the Adjoint formula (inverse = ajoint / determinant) .
      * Rank Determination: Finding the rank of any m×n matrix.
   5. System Solver: Solve Ax=B using Gaussian Elimination.
      * Supports detection of Unique Solutions, No Solution, and Infinite Solutions.
   6. Specialized Functions:
      * Saddle Point Detection: Finds elements that are row-minima and column-maxima.
      * Trace: Sum of diagonal elements.

## Prerequisites

You need a C compiler (gcc) and make.
## Installation
1. Clone the repository:
    `git clone https://github.com/mehtabpreetsingh/Matrix-Library.git` and then
    `cd Matrix-Library`.

2. Compile the project:
    `gcc main.c matrix.c -o matrix_tool -lm` or using makefile as `make`
   
The program reads operations from an input.txt file and writes the results to output.txt.
## Running the 
## Input Format

The input.txt should follow this structure:
Plaintext

```
[operation]
[rows] [cols]          // some are using only one: (row = col). You can go through input.txt file.
[data...(matrix)]
```
Example (Solving a System):
To solve 2x+y=5 and x+3y=6:
```
Plaintext
solve
2
2 1 5
1 3 6
```

## Existing operation

| Command  | Description | Defination|
| ------------- |:---------:|:--------------------------:
| add      | Adds two matrices of same dimensions.    |Matrix* addMatrix(Matrix *a, Matrix *b);|
| sub      | Subtracts two matrices of same dimensions.     |Matrix* subtractMatrix(Matrix *a,Matrix *b);|
| mul      | Multiplies two compatible matrices     |Matrix* multiplyMatrix(Matrix *a, Matrix *b);|
| det      | Calculates the determinant of a square matrix.     |double determinant(Matrix *m);
| inv      | Finds the inverse matrix.     |Matrix* inverse(Matrix *m);|
| solve    | Solves a system of equations (Augmented Matrix).    |void gaussianElimination(Matrix *m);
| rank     | Calculates the rank of the matrix.    |int matrixRank(Matrix *m);|
| saddle   | Finds all saddle points in the matrix.    |void findSaddlePoint(Matrix *m, FILE *fout);
| identity | Checks if the matrix is an identity matrix.     |int isIdentity(Matrix *m);
| trace    | Sum of the diagonal element   |double trace(Matrix *m);
| transpose| Transpose of a matrix    |Matrix* transposeMatrix(Matrix *m);|
| symmetric| Checks if the matrix is an symmetric matrix.     |int isSymmetric(Matrix *m);
| lu       | Decompose given matrix in upper and lower matrix.   |void luDecomposition(Matrix *A, Matrix *L, Matrix *U, Matrix *P);


## Project Structure

    matrix.h: Header file containing the Matrix struct and function prototypes.
    matrix.c: Implementation of the matrix logic and algorithms.
    main.c: Driver code that handles file I/O and operation.
    input.txt: File used to give data to the library.
































