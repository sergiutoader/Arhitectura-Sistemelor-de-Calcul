/*
 * Tema 2 ASC
 * 2021 Spring
 *
 * Toader Sergiu-Cristian, 335CB
 */
#include "utils.h"

// calculates transpose of upper triangular matrix
double *transposeUpperTriangular(double *A, int N) {
	int i, j;
	double *result = (double *) calloc(N * N, sizeof(double));
	if(!result) {
		fprintf(stderr, "malloc error\n");
		return NULL;
	}

	// second for goes from i to N (knowing that all values are 
	// located above or on the main diagonal)
	for(i = 0; i < N; i++) {
		for(j = i; j < N; j++) {
			result[j * N + i] = A[i * N + j];
		}
	}

	return result;
}


// calculates transpose of regular matrix
double *transposeRegular(double *A, int N) {
	int i, j;
	double *result = (double *) calloc(N * N, sizeof(double));
	if(!result) {
		fprintf(stderr, "malloc error\n");
		return NULL;
	}

	for(i = 0; i < N; i++) {
		for(j = 0; j < N; j++) {
			result[j * N + i] = A[i * N + j];
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

	// compute transpose for A and B
	AT = transposeUpperTriangular(A, N);
	BT = transposeRegular(B, N);

 	prod1 = (double *) calloc(N * N, sizeof(double));
	if(!prod1) {
		fprintf(stderr, "malloc error\n");
		return NULL;
	}

	AB = (double *) calloc(N * N, sizeof(double));
	if(!AB) {
		fprintf(stderr, "malloc error\n");
		return NULL;
	}


	// AB = A * B
	// A is triangukar, therefore, k can only go from i to N
	// (above the main diagonal)
	for(i = 0; i < N; i++) {
		for(j = 0; j < N; j++) {
			for(k = i; k < N; k++) {
				AB[N * i + j] += A[N * i + k] * B[N * k + j];
			}
		}
	}

	// prod1 =  AB * BT
	for(i = 0; i < N; i++) {
		for(j = 0; j < N; j++) {
			for(k = 0; k < N; k++) {
				prod1[N * i + j] += AB[N * i + k] * BT[N * k + j];
			}
		}
	}


	prod2 = (double *) calloc(N * N, sizeof(double));
	if(!prod2) {
		fprintf(stderr, "malloc error\n");
		return NULL;
	}

	// prod2 = AT * A
	// AT is lower triangular, therefore k can only go from 0 to i
	// (below the main diagonal)
	for(i = 0; i < N; i++) {
		for(j = 0; j < N; j++) {
			for(k = 0; k <= i; k++) {
				prod2[N * i + j] += AT[N * i + k] * A[N * k + j];
			}
		}
	}

	// result = prod1 + prod2
	// add each element from the product matrices
	for(i = 0; i < N; i++) {
		for(j = 0; j < N; j++) {
			result[N * i + j] += prod1[N * i + j] + prod2[N * i + j];
		}
	}

	free(AB);
	free(prod1);
	free(prod2);
	free(AT);
	free(BT);

	return result;
}
