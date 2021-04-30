/*
 * Tema 2 ASC
 * 2021 Spring
 */
#include "utils.h"

#define BLOCK_LEN 40

/*
 * Add your optimized implementation here
 */
// calculates transpose of upper triangular matrix
double *transposeUpperTriangular(double *A, int N) {
	double *result = (double *) calloc(N * N, sizeof(double));
	if(!result) {
		fprintf(stderr, "malloc error\n");
		return NULL;
	}

	for(int i = 0; i < N; i++) {
		register double *p = &A[i * N];
		for(int j = i; j < N; j++) {
			result[j * N + i] = *(p + j);
			//result[j * N + i] = A[i * N + j];
		}
	}

	return result;
}


// calculates transpose of regular matrix
double *transposeRegular(double *A, int N) {
	register double *result = (double *) calloc(N * N, sizeof(double));
	if(!result) {
		fprintf(stderr, "malloc error\n");
		return NULL;
	}

	for(int i = 0; i < N; i++) {
		register double *p = &A[i * N];
		for(int j = 0; j < N; j++) {
			result[j * N + i] = *(p + j);
			//result[j * N + i] = A[i * N + j];
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
	// for(int i = 0; i < N; i++) {
	// 	for(int j = 0; j < N; j += 4) {
	// 		register double sum0 = 0;
	// 		register double sum1 = 0;
	// 		register double sum2 = 0;
	// 		register double sum3 = 0;

	// 		for(int k = 0; k < N; k++) {
	// 			sum0 +=  A[N * i + k] * B[N * k + j];
	// 			sum1 +=  A[N * i + k] * B[N * k + j + 1];
	// 			sum2 +=  A[N * i + k] * B[N * k + j + 2];
	// 			sum3 +=  A[N * i + k] * B[N * k + j + 3];
	// 		}

	// 		AB[N * i + j] = sum0;
	// 		AB[N * i + j + 1] = sum1;
	// 		AB[N * i + j + 2] = sum2;
	// 		AB[N * i + j + 3] = sum3;

	// 	}
	// }

	for(int k = 0; k < N; k++) {

		register double *b_k = &B[N * k];

		for(int i = 0; i < N; i++) {
			register double *ab_i = &AB[N * i];
			register double a_i = A[N * i + k];
			for(int j = 0; j < N; j += 8) {

				// AB[N * i + j] += a_i * B[N * k + j];
				// AB[N * i + j + 1] += a_i * B[N * k + j + 1];
				// AB[N * i + j + 2] += a_i * B[N * k + j + 2];
				// AB[N * i + j + 3] += a_i * B[N * k + j + 3];

				// AB[N * i + j + 4] += a_i * B[N * k + j + 4];
				// AB[N * i + j + 5] += a_i * B[N * k + j + 5];
				// AB[N * i + j + 6] += a_i * B[N * k + j + 6];
				// AB[N * i + j + 7] += a_i * B[N * k + j + 7];


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

	// prod1 =  AB * BT
	// for(int i = 0; i < N; i++) {
	// 	for(int j = 0; j < N; j += 4) {
	// 		register double sum0 = 0;
	// 		register double sum1 = 0;
	// 		register double sum2 = 0;
	// 		register double sum3 = 0;

	// 		for(int k = 0; k < N; k++) {
	// 			sum0 +=  AB[N * i + k] * BT[N * k + j];
	// 			sum1 +=  AB[N * i + k] * BT[N * k + j + 1];
	// 			sum2 +=  AB[N * i + k] * BT[N * k + j + 2];
	// 			sum3 +=  AB[N * i + k] * BT[N * k + j + 3];
	// 		}

	// 		prod1[N * i + j] = sum0;
	// 		prod1[N * i + j + 1] = sum1;
	// 		prod1[N * i + j + 2] = sum2;
	// 		prod1[N * i + j + 3] = sum3;
	// 	}
	// }

	// for(int k = 0; k < N; k++) {

	// 	for(int i = 0; i < N; i++) {
	// 		double aux = AB[N * i + k];
	// 		for(int j = 0; j < N; j+=8) {
	// 			prod1[N * i + j] +=  aux * BT[N * k + j];
	// 			prod1[N * i + j + 1] +=  aux * BT[N * k + j + 1];
	// 			prod1[N * i + j + 2] +=  aux * BT[N * k + j + 2];
	// 			prod1[N * i + j + 3] +=  aux * BT[N * k + j + 3];
				
	// 			prod1[N * i + j + 4] +=  aux * BT[N * k + j + 4];
	// 			prod1[N * i + j + 5] +=  aux * BT[N * k + j + 5];
	// 			prod1[N * i + j + 6] +=  aux * BT[N * k + j + 6];
	// 			prod1[N * i + j + 7] +=  aux * BT[N * k + j + 7];
	// 		}
	// 	}
	// }


	for(int k = 0; k < N; k++) {

		register double *bt_k = &BT[N * k];

		for(int i = 0; i < N; i++) {
			register double *prod1_i = &prod1[N * i];
			register double ab_i = AB[N * i + k];
			for(int j = 0; j < N; j += 8) {

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
	double *prod2 = (double *) calloc(N * N, sizeof(double));
	if(!prod2) {
		fprintf(stderr, "malloc error\n");
		return NULL;
	}

	// prod2 = AT * A
	// for(int i = 0; i < N; i++) {
	// 	for(int j = 0; j < N; j += 4) {
	// 		register double sum0 = 0;
	// 		register double sum1 = 0;
	// 		register double sum2 = 0;
	// 		register double sum3 = 0;

	// 		for(int k = 0; k < N; k++) {
	// 			sum0 +=  AT[N * i + k] * A[N * k + j];
	// 			sum1 +=  AT[N * i + k] * A[N * k + j + 1];
	// 			sum2 +=  AT[N * i + k] * A[N * k + j + 2];
	// 			sum3 +=  AT[N * i + k] * A[N * k + j + 3];
	// 		}

	// 		prod2[N * i + j] = sum0;
	// 		prod2[N * i + j + 1] = sum1;
	// 		prod2[N * i + j + 2] = sum2;
	// 		prod2[N * i + j + 3] = sum3;
	// 	}
	// }


	// for(int k = 0; k < N; k++) {
	// 	for(int i = 0; i < N; i++) {
	// 		register double aux = AT[N * i + k];
	// 		for(int j = 0; j < N; j += 8) {
	// 			prod2[N * i + j] +=  aux * A[N * k + j];
	// 			prod2[N * i + j + 1] +=  aux * A[N * k + j + 1];
	// 			prod2[N * i + j + 2] +=  aux * A[N * k + j + 2];
	// 			prod2[N * i + j + 3] +=  aux * A[N * k + j + 3];
				
	// 			prod2[N * i + j + 4] +=  aux * A[N * k + j + 4];
	// 			prod2[N * i + j + 5] +=  aux * A[N * k + j + 5];
	// 			prod2[N * i + j + 6] +=  aux * A[N * k + j + 6];
	// 			prod2[N * i + j + 7] +=  aux * A[N * k + j + 7];
	// 		}
	// 	}
	// }

	for(int k = 0; k < N; k++) {

		register double *a_k = &A[N * k];

		for(int i = 0; i < N; i++) {
			register double *prod2_i = &prod2[N * i];

			register double at_i = AT[N * i + k];
			for(int j = 0; j < N; j += 8) {

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


	// result = prod1 + prod2
	for(int i = 0; i < N; i++) {
		register double *r = &result[N * i];
		register double *prod1_i = &prod1[N * i];
		register double *prod2_i = &prod2[N * i];
		for(int j = 0; j < N; j++) {
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

/*

int main () {
	printf("OPT SOLVER\n");

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
