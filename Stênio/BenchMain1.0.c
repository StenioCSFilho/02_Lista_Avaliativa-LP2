#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double *alocaMatriz1d(int nl, int nc);
void dgemm1d(int m, int n, int k, double alpha, double *matA, double *matB, double beta, double *matC);
void print_matrix(const char *desc, int m, int n, double *mat);

int main(void)
{

    FILE *fp = fopen("gemmMatrixBench.bin", "rb");

    if (fp == NULL)
    {
        printf("Arquivo não pode ser aberto\n");
        exit(1);
    }

    double alpha, beta;
    int nla, nlb, nlc, nca, ncb, ncc;
    double *matA, *matB, *matC;

    // Alpha
    fread(&alpha, sizeof(double), 1, fp);
    printf("alpha: %.1lf\n", alpha);

    // Matrix A
    fread(&nla, sizeof(int), 1, fp);
    fread(&nca, sizeof(int), 1, fp);
    printf("Matrix A dimensions: %d x %d\n", nla, nca);

    matA = alocaMatriz1d(nla, nca);
    fread(matA, sizeof(double), nla * nca, fp);

    // Matrix B
    fread(&nlb, sizeof(int), 1, fp);
    fread(&ncb, sizeof(int), 1, fp);
    printf("Matrix B dimensions: %d x %d\n", nlb, ncb);

    matB = alocaMatriz1d(nlb, ncb);
    fread(matB, sizeof(double), nlb * ncb, fp);

    // Beta
    fread(&beta, sizeof(double), 1, fp);
    printf("Beta: %.1lf\n", beta);

    // Matrix C
    fread(&nlc, sizeof(int), 1, fp);
    fread(&ncc, sizeof(int), 1, fp);
    printf("Matrix C dimensions: %d x %d\n", nlc, ncc);

    matC = alocaMatriz1d(nlc, ncc);
    fread(matC, sizeof(double), nlc * ncc, fp);

    // Teste
    clock_t start_t,
        end_t;
    double total_t;
    start_t = clock();

    dgemm1d(nla, ncb, nca, alpha, matA, matB, beta, matC);

    end_t = clock();
    total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    printf("Total time taken by CPU: %f\n", total_t);

    print_matrix("Resulting Matrix C", nlc, ncc, matC);

    free(matA);
    free(matB);
    free(matC);
    return 0;
}

double *alocaMatriz1d(const int n, const int m)
{
    double *mat;
    mat = (double *)malloc(n * m * sizeof(double));
    return mat;
}

void dgemm1d(int m, int n, int k, double alpha, double *matA, double *matB, double beta, double *matC)
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            double cij = beta * matC[i * n + j];
            for (int p = 0; p < k; p++)
            {
                cij += alpha * matA[i * k + p] * matB[p * n + j];
            }
            matC[i * n + j] = cij;
        }
    }
}

void print_matrix(const char *desc, int m, int n, double *mat)
{
    printf("\n %s\n", desc);
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf(" %.2f", mat[i * n + j]);
        }
        printf("\n");
    }
}