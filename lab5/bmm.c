#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
 
void BMMultiply(int n, double** a, double** b, double** c)
{
    int bi=0;
    int bj=0;
    int bk=0;
    int i=0;
    int j=0;
    int k=0;
    // set block dimension blockSize
    /*
     * block size = 100 -> 8.20s
     * block size = 50 -> 6.59s
     * block size = 10 -> 5.55s
     * block size = 5 -> 5.34s
     * block size = 125 -> 8.11s
     */
    int blockSize=125; 
 
    for(bi=0; bi<n; bi+=blockSize)
        for(bj=0; bj<n; bj+=blockSize)
            for(bk=0; bk<n; bk+=blockSize)
                for(i=0; i<blockSize; i++)
                    for(j=0; j<blockSize; j++)
                        for(k=0; k<blockSize; k++)
                            c[bi+i][bj+j] += a[bi+i][bk+k]*b[bk+k][bj+j];
}
 
int main(void)
{
    int n;
    double** A;
    double** B;
    double** C;
    int numreps = 10;
    int i=0;
    int j=0;
    struct timeval tv1, tv2;
    struct timezone tz;
    double elapsed;
    // set matrix dimension n
    n = 500;
    // allocate memory for the matrices
 
    // TODO: allocate matrices A, B & C
    ///////////////////// Matrix A //////////////////////////
    A = (double**) malloc(n * sizeof(double *));
    for(i = 0; i < n; i++) {
        A[i] = (malloc)(n * sizeof(double));
    }
 
    ///////////////////// Matrix B ////////////////////////// 
    B = (double**) malloc(n * sizeof(double *));
    for(i = 0; i < n; i++) {
        B[i] = (malloc)(n * sizeof(double));
    }
 
    ///////////////////// Matrix C //////////////////////////
    C = (double**) malloc(n * sizeof(double *));
    for(i = 0; i < n; i++) {
        C[i] = (malloc)(n * sizeof(double));
    }
 
    // Initialize matrices A & B
    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
        {
            A[i][j] = 1;
            B[i][j] = 2;
        }
    }
 
    //multiply matrices
 
    printf("Multiply matrices %d times...\n", numreps);
    for (i=0; i<numreps; i++)
    {
        gettimeofday(&tv1, &tz);
        BMMultiply(n,A,B,C);
        gettimeofday(&tv2, &tz);
        elapsed += (double) (tv2.tv_sec-tv1.tv_sec) + (double) (tv2.tv_usec-tv1.tv_usec) * 1.e-6;
    }
    printf("Time = %lf \n",elapsed);
 
    //deallocate memory for matrices A, B & C
    for(i = 0; i < n; i++) {
        free(A[i]);
        free(B[i]);
        free(C[i]);
    } 
    free(A);
    free(B);
    free(C);

    return 0;
}