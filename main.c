#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void printFloatMat(float *mat[], int rows, int cols);

void allocateSystem(int n, float **A[], float **b, float **x);

void freeSystem(float *A[], float *b, float *x);

void gausianElimination(int n, float *A[], float *b, float *x);

int main(int argc, char *argv[]) {
    int n;
    float **A, *b, *x;

    if(argc != 2) {
        printf("Usage: %s <file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *file = fopen(argv[1], "r");

    if(file == NULL) {
        printf("Error: cannot open file %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    fscanf(file, "%d", &n);

    printf("Dimension: %d X %d\n\n", n, n);

    allocateSystem(n, &A, &b, &x);

    // Ler matriz A
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            fscanf(file, "%f", &A[i][j]);
        }
    }

    // Ler vetor b
    for(int i = 0; i < n; i++)
        fscanf(file, "%f", &b[i]);

    fclose(file);

    printFloatMat(A, n, n);
    printf("\n");
    printFloatMat(&b, 1, n);

    gausianElimination(n, A, b, x);

    printf("-----------------------------\n");
   /* printFloatMat(A, n, n);
    printf("\n");
    printFloatMat(&b, 1, n);*/

    freeSystem(A, b, x);

    return EXIT_SUCCESS;
}

void printFloatMat(float *mat[], int rows, int cols) {
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++)
            printf("%.1f ", mat[i][j]);
        printf("\n");
    }
}

void allocateSystem(int n, float **A[], float **b, float **x) {
    *A = (float **) malloc(n * sizeof(float *));
    (*A)[0] = (float *) malloc(n * n * sizeof(float));
    for(int i = 1; i < n; i++)
        (*A)[i] = (*A)[0] + i * n;
    
    *b = (float *) malloc(n * sizeof(float));
    *x = (float *) malloc(n * sizeof(float));
}

void freeSystem(float *A[], float *b, float *x) {
    free(A[0]);
    free(A);
    free(b);
    free(x);
}

void swapRows(float *A[], float *b, int row1, int row2) {
    float *temp = A[row1];
    A[row1] = A[row2];
    A[row2] = temp;

    float temp2 = b[row1];
    b[row1] = b[row2];
    b[row2] = temp2;
}

void gausianElimination(int n, float *A[], float *b, float *x) {
    
    for(int k = 0; k < n - 1; k++) {
        // pivoteamento das linhas
        int idx = k;
        for(int i = k+1; i < n; i++) {
            if(fabs(A[i][k]) > fabs(A[k][k])) {
                idx = i;
            }
        }
        printf("Trocar linha %d por linha %d\n", k+1, idx + 1);
        swapRows(A, b, k, idx);
        printFloatMat(A, n, n);
        printf("\n");
        printFloatMat(&b, 1, n);
        printf("\n");

        // zerar elementos abaixo da diagonal principal
        for(int i = k + 1; i < n; i++) {
            // Calcular o multiplicador m
            float m = A[i][k] / A[k][k];
            printf("m = %.1f\n", m);

            // aplicar o multiplicador m na linha i
            for(int j = k; j < n; j++) {
                A[i][j] -= m * A[k][j];
            }

            // Calcular b
            b[i] -= m * b[k];
        }
    }

    // substituição regressiva
    for(int i = n - 1; i >= 0; i--) {
        float sum = 0;
        for(int j = i + 1; j < n; j++) {
            sum += A[i][j] * x[j];
        }
        x[i] = (b[i] - sum) / A[i][i];
    }

    printf("\n");
    printFloatMat(A, n, n);
    printf("\n");
    printFloatMat(&b, 1, n);

    printf("\n");
    for(int i = 0; i < n; i++)
        printf("x[%d] = %.1f\n", i+1, x[i]);
}