/*
 * Tema 2 ASC
 * 2021 Spring
 *
 * Toader Sergiu-Cristian, 335CB
 */
#include "utils.h"
#include <cblas.h>

double* my_solver(int N, double *A, double *B) {
	
	double *result, *prod1, *prod_aux;
	result = (double *) malloc(N * N * sizeof(double));
	if(!result) {
		fprintf(stderr, "Malloc error\n");
		return NULL;
	}
	
	prod_aux = (double *) malloc(N * N * sizeof(double));
	if(!prod_aux) {
		fprintf(stderr, "Malloc error\n");
		return NULL;
	}

	prod1 = (double *) malloc(N * N * sizeof(double));
	if(!prod1) {
		fprintf(stderr, "Malloc error\n");
		return NULL;
	}

	// prod_aux = B
	// copy B matrix into prod_aux matrix
	cblas_dcopy(N * N, B, 1, prod_aux, 1);

	// prod_aux = A * prod_aux
	// Compute matrix multiplication between A and B
	// We know A is upper triangular matrix, therefore we use dtrmm
	cblas_dtrmm(CblasRowMajor, CblasLeft, CblasUpper, CblasNoTrans,
		CblasNonUnit, N, N, 1.0, A, N, prod_aux, N);

	// prod1 = prod_aux * BT
	// Compute matrix multiplication between AB and BT
	cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasTrans, N, N, N, 1.0,
		prod_aux, N, B, N, 0.0, prod1, N);

	// result = A
	// copy A matrix into result matrix
	cblas_dcopy(N * N, A, 1, result, 1);

	// result = AT * result
	// Compute matrix multiplication between AT and A
	// We know AT is lower triangular matrix, therefore we use dtrmm
	cblas_dtrmm(CblasRowMajor, CblasLeft, CblasUpper, CblasTrans, CblasNonUnit,
		N, N, 1.0, A, N, result, N);


	// result = prod1 + result
	// Compute addition to obtain final result
	// Using daxpy since matrices are liniarized
	cblas_daxpy(N * N, 1, prod1, 1, result, 1);


	free(prod1);
	free(prod_aux);
	return result;
}