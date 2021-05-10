/*
 * Tema 2 ASC
 * 2021 Spring
 *
 * Toader Sergiu-Cristian, 335CB
 */
#include "utils.h"

#define BLOCK_LEN 40

// calculates transpose of upper triangular matrix
double *transposeUpperTriangular(double *A, int N) {
	int i, j;
	double *result = (double *) calloc(N * N, sizeof(double));
	if(!result) {
		fprintf(stderr, "malloc error\n");
		return NULL;
	}
	/*
		Second for goes from i to N (knowing that all values are 
		located above or on the main diagonal)

		Using a pointer variable to beginning of current line, resulting in
		less computation of the addreses of each element in the matrix
	*/
	for(i = 0; i < N; i++) {
		register double *p = &A[i * N];
		for(j = i; j < N; j++) {
			result[j * N + i] = *(p + j);
		}
	}

	return result;
}


// calculates transpose of regular matrix
double *transposeRegular(double *A, int N) {
	int i, j;
	register double *result = (double *) calloc(N * N, sizeof(double));
	if(!result) {
		fprintf(stderr, "malloc error\n");
		return NULL;
	}

	/*
		Using a pointer variable to beginning of current line, resulting in
		less computation of the addreses of each element in the matrix
	*/
	for(i = 0; i < N; i++) {
		register double *p = &A[i * N];
		for(j = 0; j < N; j++) {
			result[j * N + i] = *(p + j);
		}
	}

	return result;
}


double* my_solver(int N, double *A, double* B) {

	int i, j, k;
	double *result, *AT, *BT, *prod1, *AB, *prod2;
	
	result = (double *) calloc(N * N,  sizeof(double));
	if(!result) {
		fprintf(stderr, "malloc error\n");
		return NULL;
	}

	AT = transposeUpperTriangular(A, N);
	BT = transposeRegular(B, N);

	// first product
	prod1 = (double *) calloc(N * N, sizeof(double));
	if(!prod1) {
		fprintf(stderr, "malloc error\n");
		return NULL;
	}

	// partial first product 
	AB = (double *) calloc(N * N, sizeof(double));
	if(!AB) {
		fprintf(stderr, "malloc error\n");
		return NULL;
	}

	/*
	 	AB = A * B

	 	Optimizations:
	 	- Declaring variables as register for fewer instructions in computations
		- using pointers for:
			- saving address of each row start in B matrix
			- saving address of each row start of AB matrix (address saving
			results in fewer address computation)
			- unsing a_i varible to store A[N][k]
			- only computing value for k >= i (we know A is upper triangular)
			- loop unrolling of size 8 (we know N is divisible by 40)
	*/
	for(k = 0; k < N; k++) {

		register double *b_k = &B[N * k];

		for(i = 0; i < N; i++) {

			if(k >= i) {
				register double *ab_i = &AB[N * i];
				register double a_i = A[N * i + k];
				for(j = 0; j < N; j += 8) {

					*(ab_i + j) += a_i * *(b_k + j);
					*(ab_i + j + 1) += a_i * *(b_k + j + 1);
					*(ab_i + j + 2) += a_i * *(b_k + j + 2);
					*(ab_i + j + 3) += a_i * *(b_k + j + 3);

					*(ab_i + j + 4) += a_i * *(b_k + j + 4);
					*(ab_i + j + 5) += a_i * *(b_k + j + 5);
					*(ab_i + j + 6) += a_i * *(b_k + j + 6);
					*(ab_i + j + 7) += a_i * *(b_k + j + 7);
				}
			}
			
		}
	}

	/*
	 	prod1 = AB * BT

	 	Optimizations:
	 	- Declaring variables as register for fewer instructions in computations
		- using pointers for:
			- saving address of each row start in BT matrix
			- saving address of each row start of prod1 matrix (address saving
			results in fewer address computation)
			- unsing ab_i varible to store AB[N][k]
			- loop unrolling of size 8 (we know N is divisible by 40)
	*/
	for(k = 0; k < N; k++) {

		register double *bt_k = &BT[N * k];

		for(i = 0; i < N; i++) {
			register double *prod1_i = &prod1[N * i];
			register double ab_i = AB[N * i + k];
			for(j = 0; j < N; j += 8) {

				*(prod1_i + j) += ab_i * *(bt_k + j);
				*(prod1_i + j + 1) += ab_i * *(bt_k + j + 1);
				*(prod1_i + j + 2) += ab_i * *(bt_k + j + 2);
				*(prod1_i + j + 3) += ab_i * *(bt_k + j + 3);

				*(prod1_i + j + 4) += ab_i * *(bt_k + j + 4);
				*(prod1_i + j + 5) += ab_i * *(bt_k + j + 5);
				*(prod1_i + j + 6) += ab_i * *(bt_k + j + 6);
				*(prod1_i + j + 7) += ab_i * *(bt_k + j + 7);
			}
		}
	}


	// second product
	prod2 = (double *) calloc(N * N, sizeof(double));
	if(!prod2) {
		fprintf(stderr, "malloc error\n");
		return NULL;
	}

	/*
	 	prod2 = AT * A

	 	Optimizations:
	 	- Declaring variables as register for fewer instructions in computations
		- using pointers for:
			- saving address of each row start in A matrix
			- saving address of each row start of prod2 matrix (address saving
			results in fewer address computation)
			- unsing at_i varible to store AT[N][k]
			- only computing value for k <= i (we know AT is lower triangular)
			- loop unrolling of size 8 (we know N is divisible by 40)
	*/
	for(k = 0; k < N; k++) {

		register double *a_k = &A[N * k];

		for(i = 0; i < N; i++) {

			if(k <= i) {
				register double *prod2_i = &prod2[N * i];

				register double at_i = AT[N * i + k];
				for(j = 0; j < N; j += 8) {

						*(prod2_i + j) += at_i * *(a_k + j);
						*(prod2_i + j + 1) += at_i * *(a_k + j + 1);
						*(prod2_i + j + 2) += at_i * *(a_k + j + 2);
						*(prod2_i + j + 3) += at_i * *(a_k + j + 3);

						*(prod2_i + j + 4) += at_i * *(a_k + j + 4);
						*(prod2_i + j + 5) += at_i * *(a_k + j + 5);
						*(prod2_i + j + 6) += at_i * *(a_k + j + 6);
						*(prod2_i + j + 7) += at_i * *(a_k + j + 7);
				}
			}
			
		}
	}

	// result = prod1 + prod2
	// we save addresses for row start of each operand into pointers for fewer
	// address computation
	for(i = 0; i < N; i++) {
		register double *r = &result[N * i];
		register double *prod1_i = &prod1[N * i];
		register double *prod2_i = &prod2[N * i];
		for(j = 0; j < N; j++) {
			*(r + j) = *(prod1_i + j) + *(prod2_i + j);
		}
	}

	free(AB);
	free(prod1);
	free(prod2);
	free(AT);
	free(BT);

	return result;
}
