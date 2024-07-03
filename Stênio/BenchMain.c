#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define M 4096
#define N 4096

// Aloca uma matriz por linhas na forma de um array 1D
double *alocaMatriz1d(const int n, const int m);

// gemm -> C = alpha * A * B + beta * C (A: n x m, B: m x l, C: n x l)
// matrizes alocadas na forma de um array 1D, uma linha após a outra
void dgemm1d(const int nAC, const int mAB, const int lBC, double alpha, double *A, double *B, double beta, double *C);

int main(void)
{
    int n, m, l;

    // declaração as matrizes
    double *matA, *matB, *matC;

    // As matrizes e seus parâmetros serão lidas
    // do arquivo gemmMatrixBench.bin


    // para alocação das matrizes
    matA = alocaMatriz1d(n, m);

    matB = alocaMatriz1d(m, n);

    matC = alocaMatriz1d(n, n);

    // para quantificar o tempo de execução
    clock_t start_t, end_t;
    double total_t;
    start_t = clock();

    // chamando a rotina dgemm
    dgemm1d(n, m, n, 0.5, matA, matB, 2.0, matC);

    end_t = clock();
    total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    printf("Total time taken by CPU: %f\n", total_t);

    // liberando a memória alocada
    // free(matA[0]);
    free(matA);
    // free(matB[0]);
    free(matB);
    // free(matC[0]);
    free(matC);

    return 0;
}

double *alocaMatriz1d(const int n, const int m)
{
    double *mat;
    // aqui vc implementa a sua alocação de matriz 1D
    return mat;
}

void dgemm1d(const int n, const int m, const int l, double alpha, double *A, double *B, double beta, double *C)
{
    // aqui vc implementa a sua rotina dgemm1d
}