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
		}
	}

	return result;
}


double* my_solver(int N, double *A, double* B) {

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
		for(int j = 0; j < N; j++) {
			for(int k = 0; k < N; k++) {
				AB[N * i + j] += A[N * i + k] * B[N * k + j];
			}
		}
	}

	// prod1 =  AB * BT
	for(int i = 0; i < N; i++) {
		for(int j = 0; j < N; j++) {
			for(int k = 0; k < N; k++) {
				prod1[N * i + j] += AB[N * i + k] * BT[N * k + j];
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
		for(int j = 0; j < N; j++) {
			for(int k = 0; k < N; k++) {
				prod2[N * i + j] += AT[N * i + k] * A[N * k + j];
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

/*

int main () {
	printf("NEOPT SOLVER\n");

	double *a = (double *)calloc(16, sizeof(double));
	double *b = (double *)calloc(16, sizeof(double));

	
		// a:
		// 1 2 3 4
		// 0 5 6 7
		// 0 0 8 9
		// 0 0 0 10

		// at:

		// 1 0 0 0
		// 2 5 0 0
		// 3 6 8 0
		// 4 7 9 10

		// b:
		// 1 1 1 1
		// 1 1 1 1
		// 1 1 1 1
		// 1 1 1 1


		// c = abbt + ata
	

		// ab =

		// 10 10 10 10
		// 18 18 18 18
		// 17 17 17 17
		// 10 10 10 10

		// abbt = ab * bt =
		
		// 40 40 40 40
		// 72 72 72 72
		// 68 68 68 68
		// 40 40 40 40

		// ata =
		// 1  2   3   4
		// 2 49  36  43
		// 3 36 109 126
		// 4 43 126 246

		// c = abbt + ata =

		// 41 	42 	43 	44
		// 74 101 108 115
		// 71 104 177 194
		// 44  83 166 286

	

	a[0] = 1;
	a[1] = 2;
	a[2] = 3;
	a[3] = 4;

	a[4] = 0;
	a[5] = 5;
	a[6] = 6;
	a[7] = 7;

	a[8] = 0;
	a[9] = 0;
	a[10] = 8;
	a[11] = 9;

	a[12] = 0;
	a[13] = 0;
	a[14] = 0;
	a[15] = 10;


	b[0] = 1;
	b[1] = 1;
	b[2] = 1;
	b[3] = 1;

	b[4] = 1;
	b[5] = 1;
	b[6] = 1;
	b[7] = 1;

	b[8] =  1;
	b[9] =  1;
	b[10] = 1;
	b[11] = 1;

	b[12] = 1;
	b[13] = 1;
	b[14] = 1;
	b[15] = 1;


	double *c = my_solver(4, a, b);

	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < 4; j++) {
			printf("%lf ", c[4 * i + j]);
		}
		printf("\n");
	}


	free(a);
	free(b);
	free(c);
	return 0;

}
*/	