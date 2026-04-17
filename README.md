# Matrix-Library
A powerful C library for matrix manipulation and linear algebra. This project provides a structured way to handle matrices, solve systems of equations, and perform complex algebraic operations with memory safety in mind.
Key Features:
   1. Basic Arithmetic: Addition, subtraction, and multiplication of two Matrices.
   2. Transformations: Transpose and scalar multiplication of a Matrix.
   3. Properties: Check for Identity, Symmetry, and Square matrices.
   4. Advanced Algebra:
      -> Determinant Calculation: Recursive calculation using minors.
      -> Matrix Inversion: Using the Adjoint formula (inverse = ajoint / determinant) .
      -> Rank Determination: Finding the rank of any m×n matrix.
   5. System Solver: Solve Ax=B using Gaussian Elimination.
      ->Supports detection of Unique Solutions, No Solution, and Infinite Solutions.
   6. Specialized Functions:
      ->Saddle Point Detection: Finds elements that are row-minima and column-maxima.
      ->Trace: Sum of diagonal elements.

Prerequisites

You need a C compiler (gcc) and make.
Installation
1. Clone the repository:
    git clone https://github.com/mehtabpreetsingh/Matrix-Library.git
    cd Matrix-Library

2. Compile the project:
    gcc main.c matrix.c -o matrix_tool -lm
    
The program reads operations from an input.txt file and writes the results to output.txt.
Input Format

The input.txt should follow this structure:
Plaintext

[operation]
[rows] [cols]
[data...(matrix)]

Example (Solving a System):
To solve 2x+y=5 and x+3y=6:
Plaintext

solve
2
2 1 5
1 3 6
