

#include <stdio.h>

// ===== STRUCT =====
typedef struct {
    int rows;
    int cols;
    double **data;
} Matrix;

// ===== MEMORY =====
Matrix* createMatrix(int rows, int cols);
void freeMatrix(Matrix *m);

// ===== I/O =====
void printMatrix(Matrix *m);
void writeMatrixToFile(FILE *fp, Matrix *m);

// ===== BASIC OPERATIONS =====
Matrix* addMatrix(Matrix *a, Matrix *b);
Matrix* subtractMatrix(Matrix *a, Matrix *b);
Matrix* multiplyMatrix(Matrix *a, Matrix *b);

// ===== TRANSFORMATIONS =====
Matrix* transposeMatrix(Matrix *m);
Matrix* scalarMultiply(Matrix *m, double k);

// ===== UTILITIES =====
Matrix* copyMatrix(Matrix *m);
int isSquare(Matrix *m);
double trace(Matrix *m);

// ===== PROPERTIES =====
//int isZeroMatrix(Matrix *m);
int isIdentity(Matrix *m);
int isSymmetric(Matrix *m);

// ===== ROW OPERATIONS =====
void swapRows(double **mat, int r1, int r2);
//void scaleRow(Matrix *m, int r, double factor);
//void addRowMultiple(Matrix *m, int src, int dest, double factor);

// ===== DETERMINANT =====
Matrix* getMinor(Matrix *m, int row, int col);
double determinant(Matrix *m);

// ===== INVERSE =====
Matrix* inverse(Matrix *m);

// ===== GAUSSIAN =====
void gaussianElimination(Matrix *m);

// ===== RANK =====
int matrixRank(Matrix *m);
void findSaddlePoint(Matrix *m, FILE *fout);
// ===== LU DECOMP =====
void luDecomposition(Matrix *A, Matrix *L, Matrix *U, Matrix *P);


