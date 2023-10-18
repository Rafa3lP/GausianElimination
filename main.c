#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int n;
    float **A;
    float *b;
    float *x;
} linearSystem;

void allocateSystem(linearSystem *s);

void freeSystem(linearSystem *s);

void gausianElimination(linearSystem *s);

void swapRows(linearSystem *s, int row1, int row2);

void readSystem(linearSystem *s, FILE *file);

void printSolution(linearSystem *s);

void printSystem(linearSystem *s);

int main(int argc, char *argv[]) {
    linearSystem s;

    if(argc != 2) {
        printf("Usage: %s <file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *file = fopen(argv[1], "r");

    if(file == NULL) {
        printf("Error: cannot open file %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    readSystem(&s, file);

    fclose(file);

    gausianElimination(&s);

    printSolution(&s);

    freeSystem(&s);

    return EXIT_SUCCESS;
}

void readSystem(linearSystem *s, FILE *file) {
    fscanf(file, "%d", &s->n);

    allocateSystem(s);

    // Ler matriz A
    for(int i = 0; i < s->n; i++) {
        for(int j = 0; j < s->n; j++) {
            fscanf(file, "%f", &s->A[i][j]);
        }
    }

    // Ler vetor b
    for(int i = 0; i < s->n; i++)
        fscanf(file, "%f", &s->b[i]);
}

void printSolution(linearSystem *s) {
    printf("\n-------------SOLUTION----------------\n");
    for(int i = 0; i < s->n; i++)
        printf("x[%d] = %.1f\n", i+1, s->x[i]);
    printf("-------------------------------------\n");
}

void allocateSystem(linearSystem *s) {
    s->A = (float **) malloc(s->n * sizeof (float *));
    for (int i = 0; i < s->n; i++)
        s->A[i] = (float *) malloc(s->n * sizeof (float)) ;
    
    s->b = (float *) malloc(s->n * sizeof(float));
    s->x = (float *) malloc(s->n * sizeof(float));
}

void freeSystem(linearSystem *s) {
    for(int i = 0; i < s->n; i++)
        free(s->A[i]);
    free(s->A);
    free(s->b);
    free(s->x);
}

void swapRows(linearSystem *s, int row1, int row2) {
    float *temp = s->A[row1];
    s->A[row1] = s->A[row2];
    s->A[row2] = temp;

    float temp2 = s->b[row1];
    s->b[row1] = s->b[row2];
    s->b[row2] = temp2;
}

void printSystem(linearSystem *s) {
    for(int i = 0; i < s->n; i++) {
        putchar('[');
        for(int j = 0; j < s->n; j++)
            printf("%*.2f ", 10, s->A[i][j]);
        printf("] | [" );
        printf("%*.2f", 10, s->b[i]);
        printf("]\n");
    }
}

void gausianElimination(linearSystem *s) {
    #ifdef DEBUG
    printf("Dimension: %d X %d\n\n", s->n, s->n);
    printSystem(s);
    printf("\n");
    #endif

    for(int k = 0; k < s->n - 1; k++) {
        // pivoteamento das linhas
        int idx = k;
        for(int i = k+1; i < s->n; i++) {
            if(fabs(s->A[i][k]) > fabs(s->A[idx][k])) {
                idx = i;
            }
        }

        swapRows(s, k, idx);

        #ifdef DEBUG
        printf("Swap line %d with line %d:\n\n", k+1, idx + 1);
        printSystem(s);
        printf("\n");
        #endif

        // zerar elementos abaixo da diagonal principal
        for(int i = k + 1; i < s->n; i++) {
            // Calcular o multiplicador m
            float m = s->A[i][k] / s->A[k][k];

            #ifdef DEBUG
            printf("m[%d][%d] = %.2f / %.2f = %.2f\n", i+1, k+1, s->A[i][k], s->A[k][k], m);
            printf("L%d = L%d - (%.2f * L%d):\n\n", i+1, i+1, m, k+1);
            #endif

            // aplicar o multiplicador m na linha i
            for(int j = k; j < s->n; j++) {
                s->A[i][j] -= m * s->A[k][j];
            }

            // Calcular b
            s->b[i] -= m * s->b[k];

            #ifdef DEBUG
            printSystem(s);
            printf("\n");
            #endif
        }
    }
    
    // substituição regressiva
    for(int i = s->n - 1; i >= 0; i--) {
        float sum = 0;
        for(int j = i + 1; j < s->n; j++) {
            sum += s->A[i][j] * s->x[j];
        }
        s->x[i] = (s->b[i] - sum) / s->A[i][i];
    }
}