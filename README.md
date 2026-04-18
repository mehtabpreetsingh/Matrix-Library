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

## Compilation & Execution

This library supports both Static (.a) and Dynamic (.so) linking. A Makefile is provided to automate these builds.
1. Build the Library:

To compile the source code and generate the library files along with the test executables, run:
`make`

This will generate:

    libmatrix.a: The static library.
    libmatrix.so: The shared (dynamic) library.
    main_static: Executable linked statically.
    main_dynamic: Executable linked dynamically.

2. Execution
* Option A: Static Execution

The static version is self-contained. Just run:
`./main_static`

* Option B: Dynamic Execution

The dynamic version is smaller but needs to know where the .so file is located at runtime. You must set the LD_LIBRARY_PATH so the system can find your library in the current folder:

Set the path and run:
```
export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH
./main_dynamic
```

   Note: If you get an error saying libmatrix.so: cannot open shared object file, it means you haven't exported the path as shown above.

3. Cleanup:

To remove all generated object files, libraries, and executables, run:
`make clean`
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
    output.txt: Automatically created with the output.(if not there)

1. Data flow (The "How it Works" section):

  * `main.c`opens `input.txt` and reads the operation string (e.g., add, solve).
* Allocation: Based on the operation, the program reads the matrix dimensions and calls `createMatrix()`, which allocates a Matrix struct and a 2D array on the Heap.

* Execution: `main.c` passes the matrix pointer to the specialized functions in `matrix.c`(like gaussianElimination or determinant).

* output: The results are formatted and written to output.txt.

* Cleanup: `freeMatrix()` is called to deallocate all heap memory, ensuring no memory leaks.
   
2. Memory Management:
   
* This library uses dynamic memory allocation. Every createMatrix call should be paired with a freeMatrix call to prevent memory leaks.

## Constraints & Specifications

To ensure the library works correctly, you have to follow mathematical and code constraints:
1. Matrix Dimensions:

* Maximum Size: While the library uses dynamic allocation (malloc), it is recommended to keep matrices under 500x500 for recursive operations like determinant and inverse.

*  Recursion Limit: The determinant is calculated via Laplace expansion. For matrices larger than 12x12, this method gives time complexity o(n!). (prefer to less than 10X10).

2. Element Values (Data Types)

* Storage Type: All elements are stored as `double`.

 *   Input Range: You can safely input values between approximately ±1.7×10308. However, for readable results and to avoid overflow during multiplication, it is best to stay within the range of `-1,000,000 to 1,000,000`.

 *   Precision: The library handles up to 15-17 significant decimal digits.

3. Output Formatting

*    Decimal Display: All results written to output.txt are rounded to `2 decimal places` (e.g., 3.14159 becomes 3.14) for clarity.

 *   Tolerance: The library uses a tolerance of `10^−9`. Any value smaller than this during Gaussian Elimination is treated as `0.00`.

4. Input File Integrity

  * Formatting: The input.txt must strictly follow the [Rows] [Cols] header followed by the data.
  *  Completeness: If a matrix is defined as 3×3, exactly 9 elements must be provided. Missing elements will cause the parser to read the next available number, leading to corrupted calculations.

*  Characters: Only numeric values (integers and decimals) are accepted. Special characters or letters inside the matrix data will cause the program to fail.

Moreover:

* System Solving: When using solve, ensure you provide an augmented matrix (N rows and N+1 columns).
* Only identify that the operation is wrong or not.






























