#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrix.h"

// ================= CREATE & FREE =================

Matrix *createMatrix(int rows, int cols){
    Matrix *m = malloc(sizeof(Matrix));
    m->rows = rows;
    m->cols = cols;

    m->data = malloc(rows * sizeof(double *));
    for(int i=0; i<rows; i++){
        m->data[i] = malloc(cols * sizeof(double));
    }

    return m;
}

void freeMatrix(Matrix *m){
    for(int i=0; i<m->rows; i++){
        free(m->data[i]);
    }

    free(m->data);
    free(m);
}

// ================= PRINT =================

void printMatrix(Matrix *m){
    for(int i=0; i<m->rows; i++){
        for(int j=0; j<m->cols; j++){
            printf("%.2lf ", m->data[i][j]);
	}
        printf("\n");
    }
}

void writeMatrixToFile(FILE *fp, Matrix *m){
	for(int i=0; i<m->rows; i++){
		for(int j=0; j<m->cols;j++){
			fprintf(fp, "%.2lf ", m->data[i][j]);
		}
		fprintf(fp, "\n");
	}
}

// ================= BASIC OPERATIONS =================

Matrix *addMatrix(Matrix *a, Matrix *b){
    Matrix *res = createMatrix(a->rows, a->cols);
    for(int i=0; i<a->rows; i++){
        for (int j=0; j<a->cols; j++){
            res->data[i][j] = a->data[i][j] + b->data[i][j];
	}
    }
    return res;
}

Matrix *subtractMatrix(Matrix *a, Matrix *b){
    Matrix *res = createMatrix(a->rows, a->cols);
    for (int i=0; i<a->rows; i++){
        for (int j=0; j<a->cols; j++){
            res->data[i][j] = a->data[i][j] - b->data[i][j];
	}
    }
    return res;
}

Matrix *multiplyMatrix(Matrix *a, Matrix *b){
    Matrix *res = createMatrix(a->rows, b->cols);

    for (int i=0; i<a->rows; i++){
        for (int j=0; j<b->cols; j++){
            res->data[i][j] = 0;
            for (int k = 0; k < a->cols; k++){
                res->data[i][j] += a->data[i][k] * b->data[k][j];
	    }
        }
    }
    return res;
}

// ================= TRANSFORMATIONS =================

Matrix *transposeMatrix(Matrix *m){
    Matrix *t = createMatrix(m->cols, m->rows);
    for(int i=0; i<m->rows; i++){
        for(int j=0; j<m->cols; j++){
            t->data[j][i] = m->data[i][j];
	}
    }
    return t;
}

Matrix *scalarMultiply(Matrix *m, double k){
	Matrix *res = createMatrix(m->rows, m->cols);
	for(int i=0; i<m->rows; i++){
		for(int j=0; j<m->cols; j++){
			res->data[i][j] = m->data[i][j] * k;
	}
   }
   return res;
}

// ================= UTILITIES =================

int isSquare(Matrix *m){
    return (m->rows == m->cols);
}

double trace(Matrix *m){
    if(!isSquare(m)){
	    return 0;
    }
    double sum = 0;
    for(int i=0; i<m->rows; i++){
        sum += m->data[i][i];
    }
    return sum;
}

Matrix *copyMatrix(Matrix *m){
	Matrix *copy = createMatrix(m->rows, m->cols);

	for(int i=0; i<m->rows; i++){
		for(int j=0; j<m->cols; j++){
			copy->data[i][j] = m->data[i][j];
		}
	}
	return copy;
}

// ================= SPECIAL MATRICES =================

Matrix *identityMatrix(int n){
    Matrix *I = createMatrix(n, n);
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            I->data[i][j] = (i == j) ? 1 : 0;
	}
    }
    return I;
}

int isIdentity(Matrix *m){
    if(!isSquare(m)){
	   return 0;
    }
    for(int i=0; i<m->rows; i++){
        for(int j=0; j<m->cols; j++){
            if(i == j && m->data[i][j] != 1) return 0;
            if(i != j && m->data[i][j] != 0) return 0;
        }
    }
    return 1;
}

int isSymmetric(Matrix *m){
    if(!isSquare(m)) return 0;
    for(int i=0; i<m->rows; i++){
        for(int j=0; j<m->cols; j++){
            if (m->data[i][j] != m->data[j][i]){
	 	    return 0;
	    }
	}
    }
    return 1;
}

// ================= DETERMINANT =================

Matrix *getMinor(Matrix *m, int row, int col){
    Matrix *minor = createMatrix(m->rows - 1, m->cols - 1);

    int r = 0;
    for(int i=0; i<m->rows; i++){
        if(i == row){
		continue;//skip row we want to remove
	}

        int c = 0;
        for(int j=0; j<m->cols; j++){
            if(j == col){
		    continue;//skip col we wamt to remove
	    }
            minor->data[r][c++] = m->data[i][j];
        }
        r++;
    }

    return minor;
}

double determinant(Matrix *m){
    if(m->rows == 1)
        return m->data[0][0];

    double det = 0;

    for(int i=0; i<m->cols; i++){
        Matrix *minor = getMinor(m, 0, i);//remove row=0,col=i
        double sign = (i % 2 == 0) ? 1 : -1;
        det += sign * m->data[0][i] * determinant(minor);
        freeMatrix(minor);
    }

    return det;
}

// ================= COFACTOR & ADJOINT =================

Matrix *cofactorMatrix(Matrix *m){
    Matrix *cof = createMatrix(m->rows, m->cols);

    for(int i=0; i<m->rows; i++){
        for(int j=0; j<m->cols; j++){
            Matrix *minor = getMinor(m, i, j);
            double sign = ((i + j) % 2 == 0) ? 1 : -1;
            cof->data[i][j] = sign * determinant(minor);
            freeMatrix(minor);
        }
    }

    return cof;
}

Matrix *adjointMatrix(Matrix *m){
    Matrix *cof = cofactorMatrix(m);
    Matrix *adj = transposeMatrix(cof);
    freeMatrix(cof);
    return adj;
}

// ================= INVERSE =================
// using basic formula {inverse = adj(A) / det(A)}

Matrix *inverse(Matrix *m){
    if (!isSquare(m)) return NULL;

    double det = determinant(m);
    if (det == 0) return NULL;

    Matrix *adj = adjointMatrix(m);
    Matrix *inv = scalarMultiply(adj, 1.0 / det);//multiply with every number

    freeMatrix(adj);
    return inv;
}

// ================== GAUSSIAN ELIMINATION =================

void gaussianElimination(Matrix *m){
    int n = m->rows;
    int cols = m->cols;

    for(int i = 0; i < n && i < cols; i++){

        // Find pivot (partial pivoting)
        int maxRow = i;
        for(int r = i + 1; r < n; r++){
            if(fabs(m->data[r][i]) > fabs(m->data[maxRow][i])){
                maxRow = r;
            }
        }

        // Swap rows
        if(maxRow != i){
            double *temp = m->data[i];
            m->data[i] = m->data[maxRow];
            m->data[maxRow] = temp;
        }

        double pivot = m->data[i][i];
        if(fabs(pivot) < 1e-9) continue;

        // Normalize row
        for(int j = 0; j < cols; j++){
            m->data[i][j] /= pivot;
        }

        // Eliminate other rows
        for(int k = 0; k < n; k++){
            if(k == i) continue;

            double factor = m->data[k][i];
            for(int j = 0; j < cols; j++){
                m->data[k][j] -= factor * m->data[i][j];
            }
        }
    }
}

// ================= RANK ==================

int matrixRank(Matrix *m){
    Matrix *temp = copyMatrix(m);
    int rank = temp->cols;

    for (int row=0; row<rank; row++){
        if(temp->data[row][row] != 0){
            for(int col=0; col<temp->rows; col++){
                if(col != row){
                    double mult = temp->data[col][row] / temp->data[row][row];
                    for(int i=0; i<rank; i++){
                        temp->data[col][i] -= mult * temp->data[row][i];
		    }
                }
            }
        } else{
            int reduce = 1;

            for(int i=row + 1; i<temp->rows; i++){
                if(temp->data[i][row] != 0){
                    double *tempRow = temp->data[row];
                    temp->data[row] = temp->data[i];
                    temp->data[i] = tempRow;
                    reduce = 0;
                    break;
                }
            }

            if(reduce){
                rank--;
                for(int i=0; i<temp->rows; i++)
                    temp->data[i][row] = temp->data[i][rank];
            }

            row--;
        }
    }

    freeMatrix(temp);
    return rank;
    }


// ============== SADDLE POINT ================
void findSaddlePoint(Matrix *m, FILE *fout) {
    int found = 0;

    for (int i = 0; i < m->rows; i++) {
        // 1. Find the actual minimum value of the row first
        double rowMin = m->data[i][0];
        for (int j = 1; j < m->cols; j++) {
            if (m->data[i][j] < rowMin) {
                rowMin = m->data[i][j];
            }
        }

        // 2. Now check every element in this row that matches rowMin
        for (int j = 0; j < m->cols; j++) {
            if (m->data[i][j] == rowMin) {
                
                // 3. Check if this specific element is the maximum in its column
                int isMaxInCol = 1;
                for (int k = 0; k < m->rows; k++) {
                    if (m->data[k][j] > m->data[i][j]) {
                        isMaxInCol = 0;
                        break;
                    }
                }

                if (isMaxInCol) {
                    fprintf(fout, "Saddle Point found at [%d][%d] with value: %.2lf\n", i, j, m->data[i][j]);
                    found = 1;
		}
	    }
	}
    }
    

    if (!found) {
        fprintf(fout, "No saddle point found.\n");
    }
}


// ================ LU DECOMPOSITION =================

void swapRows(double **mat, int r1, int r2) {
    double *temp = mat[r1];
    mat[r1] = mat[r2];
    mat[r2] = temp;
}


void luDecomposition(Matrix *A, Matrix *L, Matrix *U, Matrix *P){
    int n = A->rows;

    // Initialize
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            L->data[i][j] = 0;
            U->data[i][j] = A->data[i][j]; // copy A into U
            P->data[i][j] = (i == j) ? 1 : 0;
        }
    }

    for(int i = 0; i < n; i++){

        // ===== PARTIAL PIVOTING =====
        int maxRow = i;
        for(int k = i + 1; k < n; k++){
            if(fabs(U->data[k][i]) > fabs(U->data[maxRow][i])){
                maxRow = k;
            }
        }

        // Swap if needed
        if(maxRow != i){
            swapRows(U->data, i, maxRow);
            swapRows(P->data, i, maxRow);

            for(int j = 0; j < i; j++){
                double temp = L->data[i][j];
                L->data[i][j] = L->data[maxRow][j];
                L->data[maxRow][j] = temp;
            }
        }

        double pivot = U->data[i][i];

        // ⚠️ If pivot is ~0 → skip (IMPORTANT FIX)
        if(fabs(pivot) < 1e-9){
            L->data[i][i] = 1; // still keep diagonal valid
            continue;
        }

        // ===== NORMAL CASE =====
        L->data[i][i] = 1;

        for(int k = i + 1; k < n; k++){
            double factor = U->data[k][i] / pivot;
            L->data[k][i] = factor;

            for(int j = i; j < n; j++){
                U->data[k][j] -= factor * U->data[i][j];
            }
        }
    }
}


