#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrix.h"

// Read matrix from the file
Matrix *readMatrix(FILE *fp, int r, int c){
    Matrix *m = createMatrix(r, c);

    for(int i=0; i<r; i++){
        for (int j = 0; j < c; j++){
            fscanf(fp, "%lf", &m->data[i][j]);
	}
    }

    return m;
}

int main(){
    FILE *fin = fopen("input.txt", "r");
    FILE *fout = fopen("output.txt", "w");

    if(!fin || !fout){
        printf("File error!\n");
        return 1;
    }

    char op[20];

    //multiple finction
    while(fscanf(fin, "%s", op) != EOF){

        fprintf(fout, "Operation: %s\n", op);
	
        // ADDITION
	if(strcmp(op, "add") == 0){
            int r1,c1,r2,c2;

            fscanf(fin,"%d %d",&r1,&c1);
            Matrix *A = readMatrix(fin,r1,c1);

            fscanf(fin,"%d %d",&r2,&c2);
            Matrix *B = readMatrix(fin,r2,c2);

            if(r1 == r2 && c1 == c2){
                Matrix *res = addMatrix(A,B);
                writeMatrixToFile(fout,res);
                freeMatrix(res);
            }else{
                fprintf(fout,"Addition not possible\n");
            }

            freeMatrix(A);
	    freeMatrix(B);
        }

        // SUBSTRATION
        else if(strcmp(op, "sub") == 0){
            int r1,c1,r2,c2;

            fscanf(fin,"%d %d",&r1,&c1);
            Matrix *A = readMatrix(fin,r1,c1);

            fscanf(fin,"%d %d",&r2,&c2);
            Matrix *B = readMatrix(fin,r2,c2);

            if(r1 == r2 && c1 == c2){
                Matrix *res = subtractMatrix(A,B);
                writeMatrixToFile(fout,res);
                freeMatrix(res);
            } else{
                fprintf(fout,"Subtraction not possible\n");
            }

            freeMatrix(A); freeMatrix(B);
        }

        // MULTIPLICATION
        else if(strcmp(op, "mul") == 0){
            int r1,c1,r2,c2;

            fscanf(fin,"%d %d",&r1,&c1);
            Matrix *A = readMatrix(fin,r1,c1);

            fscanf(fin,"%d %d",&r2,&c2);
            Matrix *B = readMatrix(fin,r2,c2);

            if(c1 == r2){
                Matrix *res = multiplyMatrix(A,B);
                writeMatrixToFile(fout,res);
                freeMatrix(res);
            } else{
                fprintf(fout,"Multiplication not possible\n");
            }

            freeMatrix(A);
	    freeMatrix(B);
        }

        // DETERMINANT
        else if(strcmp(op, "det") == 0){
            int r,c;
            fscanf(fin,"%d %d",&r,&c);

            Matrix *A = readMatrix(fin,r,c);

            if(isSquare(A)){
                double d = determinant(A);
                fprintf(fout,"Determinant: %.2lf\n", d);
            } else{
                fprintf(fout,"Not square matrix\n");
            }

            freeMatrix(A);
        }

        // INVERSE OF MATRIX
        else if(strcmp(op, "inv") == 0){
            int r,c;
            fscanf(fin,"%d %d",&r,&c);

            Matrix *A = readMatrix(fin,r,c);

            Matrix *inv = inverse(A);

            if(inv != NULL){
                writeMatrixToFile(fout,inv);
                freeMatrix(inv);
            } else{
                fprintf(fout,"Inverse not possible\n");
            }

            freeMatrix(A);
        }

	// TRACE OF MATRIX
	else if(strcmp(op, "trace") == 0){
		int r, c;
		fscanf(fin, "%d %d", &r, &c);

		Matrix *A = readMatrix(fin, r,c);

		if(r == c){
			fprintf(fout, "trace is %.2lf\n", trace(A));
		}
		else{
			fprintf(fout, "trace not possible\n");
		}
		freeMatrix(A);
	}
	
	// TRANSPOSE OF MATRIX
	else if(strcmp(op, "transpose") == 0){
		int r,c;
		fscanf(fin, "%d %d", &r, &c);

		Matrix *a = readMatrix(fin, r, c);
		Matrix *T = transposeMatrix(a);

		writeMatrixToFile(fout,T);

		freeMatrix(a);
		freeMatrix(T);
	}

	// RANK OF MATRIX
	else if(strcmp(op, "rank")== 0){
		int r,c;
		fscanf(fin, "%d %d", &r, &c);

		Matrix *A = readMatrix(fin, r, c);

		fprintf(fout, "Rank is: %d\n", matrixRank(A));

		freeMatrix(A);
	}

	// IDENTITY MATRIX
	else if(strcmp(op, "identity") == 0){
		int r,c;
		fscanf(fin, "%d %d", &r, &c);

		Matrix *A = readMatrix(fin, r,c);

		if(isIdentity(A)){
			fprintf(fout, "Matrix is identity\n");
		}
		else{
			fprintf(fout, "Not identity\n");
		}
		freeMatrix(A);
		
	}
	
	// SYMMETRIX MATRIX
	else if(strcmp(op, "symmetric") == 0){
		int r,c;
		fscanf(fin, "%d %d", &r, &c);

		Matrix *A = readMatrix(fin, r,c);

		if(isSymmetric(A)){
			fprintf(fout, "Matrix is Symmetric\n");
		}
		else{
			fprintf(fout, "Not Symmetric\n");
		}
		freeMatrix(A);
		
	}

	// SADDLE POINT
	else if(strcmp (op, "saddle") == 0){
		int r,c;
		fscanf(fin, "%d %d", &r, &c);

		Matrix *A = readMatrix(fin,r,c);

		findSaddlePoint(A, fout);
		freeMatrix(A);
	}

      // SOLVE SYSTEM 
      else if (strcmp(op, "solve") == 0) {
   	 int n;
	 if (fscanf(fin, "%d", &n) != 1) continue;

    	Matrix *G = createMatrix(n, n + 1);

    	for (int i = 0; i < n; i++) {
        	for (int j = 0; j < n + 1; j++) {
            	fscanf(fin, "%lf", &G->data[i][j]);
        	}
    	}

   	 // Perform Gaussian Elimination
    	gaussianElimination(G);

    	int noSolution = 0;
    	int zeroRows = 0;

    	for (int i = 0; i < n; i++) {
        	int allZerosLeft = 1;

        // Check left side (coefficients)
        for (int j = 0; j < n; j++) {
            if (G->data[i][j] != 0) {
                allZerosLeft = 0;
                break;
            }
        }

        // Check constant term
        if (allZerosLeft) {
            if (G->data[i][n] != 0) {
                // 0 = non-zero → inconsistent
                noSolution = 1;
                break;
            } else {
                // 0 = 0 → dependent row
                zeroRows++;
            }
        }
    }

    	// RESULT
    	if (noSolution) {
        	fprintf(fout, "Result: No Solution (Inconsistent System)\n");
    	}
    	else if (zeroRows > 0) {
        	fprintf(fout, "Result: Infinite Solutions (Dependent System)\n");
    	}
    	else {
        	fprintf(fout, "Result: Unique Solution\n");

        for (int i = 0; i < n; i++) {
            	fprintf(fout, "x%d = %.2lf\n", i + 1, G->data[i][n]);
	}
    }

    freeMatrix(G);
}
	else if (strcmp(op,"lu")==0) {
	       	int n;
		fscanf(fin,"%d",&n);
		Matrix *A = readMatrix(fin,n,n);
	 	Matrix *L = createMatrix(n,n);
	 	Matrix	*U = createMatrix(n,n);
		Matrix	*P = createMatrix(n,n);
		
		luDecomposition(A, L, U, P);
                
		fprintf(fout,"L matrix:\n");
		writeMatrixToFile(fout, L);

		fprintf(fout,"U matrix:\n");
		writeMatrixToFile(fout, U);

		freeMatrix(A);
		freeMatrix(L);
		freeMatrix(U);
		freeMatrix(P);
	}


	// end
        else {
            fprintf(fout,"Invalid operation\n");
        
	}
        fprintf(fout,"\n");
    }	

    fclose(fin);
    fclose(fout);

    return 0;
  }
