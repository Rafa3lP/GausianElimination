#include <stdio.h>
#include <stdlib.h>

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

void gausianElimination(int n, float *A[], float *b, float *x) {

}