/*
 * Tema 2 ASC
 * 2021 Spring
 */
#include "utils.h"

/*
 * Add your unoptimized implementation here
 */

// calculates transpose of upper triangular matrix
double *transposeUpperTriangular(double *A, int N) {
	double *result = (double *) calloc(N * N, sizeof(double));
	if(!result) {
		fprintf(stderr, "malloc error\n");
		return NULL;
	}

	for(int i = 0; i < N; i++) {
		for(int j = i; j < N; j++) {
			result[j * N + i] = A[i * N + j];
			result[i * N + j] = 0;
		}
	}

	return result;
}


// calculates transpose of regular matrix
double *transposeRegular(double *A, int N) {
	double *result = (double *) calloc(N * N, sizeof(double));
	if(!result) {
		fprintf(stderr, "malloc error\n");
		return NULL;
	}

	for(int i = 0; i < N; i++) {
		for(int j = 0; j < N; j++) {
			result[j * N + i] = A[i * N + j];
			result[i * N + j] = 0;
		}
	}

	return result;
}


double* my_solver(int N, double *A, double* B) {
	printf("NEOPT SOLVER\n");

	double *result = (double *) calloc(N * N,  sizeof(double));
	if(!result) {
		fprintf(stderr, "malloc error\n");
		return NULL;
	}

	double *AT = transposeUpperTriangular(A, N);
	if(!AT) {
		return NULL;
	}

	double *BT = transposeRegular(B, N);

	// first product
	double *prod1 = (double *) calloc(N * N, sizeof(double));
	if(!prod1) {
		fprintf(stderr, "malloc error\n");
		return NULL;
	}

	// partial first product 
	double *AB = (double *) calloc(N * N, sizeof(double));
	if(!AB) {
		fprintf(stderr, "malloc error\n");
		return NULL;
	}

	// AB = A * B
	for(int i = 0; i < N; i++) {
		for(int j = i; j < N; j++) {
			for(int k = 0; k < N; k++) {
				AB[N * i + j] += A[N * i + k] + B[N * k + j];
			}
		}
	}

	// prod1 =  AB * BT
	for(int i = 0; i < N; i++) {
		for(int j = 0; j < N; j++) {
			for(int k = 0; k < N; k++) {
				prod1[N * i + j] += AB[N * i + k] + BT[N * k + j];
			}
		}
	}


	// second product
	double *prod2 = (double *) calloc(N * N, sizeof(double));
	if(!prod2) {
		fprintf(stderr, "malloc error\n");
		return NULL;
	}

	// prod2 = AT * A
	for(int i = 0; i < N; i++) {
		for(int j = 0; j <= i; j++) {
			for(int k = 0; k < N; k++) {
				prod2[N * i + j] += AT[N * i + k] + A[N * k + j];
			}
		}
	}

	// result = prod1 + prod2
	for(int i = 0; i < N; i++) {
		for(int j = 0; j < N; j++) {
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
