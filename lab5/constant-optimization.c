#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#define N 1000
double a[N*N], b[N*N], c[N*N];

void classic_matrix_multiply() {
	int i,j,k;
	
	for (i=0;i<N;i++){
	   for (j=0;j<N;j++){
	      c[i * N + j] = 0.0;
	      for (k=0;k<N;k++){
		c[i * N + j] += a[i * N + k] * b[k * N + j];
	      }
	   }
	}
}

void register_mulitply () {
	int i,j,k;

	for (i=0;i<N;i++){
	   for (j=0;j<N;j++){
	      register double suma = 0.0;
	      for (k=0;k<N;k++) {
	         suma += a[i * N + k] * b[k * N + j];
	      }
	      c[i * N + j] = suma;
	   }
	}
}

void pointer_multiply () {
	int i,j,k;

	for(i = 0; i < N; i++){
	  double *orig_pa = &a[i * N];
	  for(j = 0; j < N; j++){
	    double *pa = orig_pa;
	    double *pb = &b[j];
	    register double suma = 0;
	    for(k = 0; k < N; k++){
	      suma += *pa * *pb;
	      pa++;
	      pb += N;
	    }
	    c[i * N + j] = suma;
	  }
	}
}

int main() {
	struct timeval tv1, tv2;
    struct timezone tz;
    double elapsed;


    // testare inmultire clasica matrici
    gettimeofday(&tv1, &tz);
    
    classic_matrix_multiply();

    gettimeofday(&tv2, &tz);
    elapsed = (double) (tv2.tv_sec-tv1.tv_sec) + (double) (tv2.tv_usec-tv1.tv_usec) * 1.e-6;
    printf("Classic Multiply Time = %lf \n",elapsed);


    // testare inmultire matrici cu salvare rezultat partial in registru
    gettimeofday(&tv1, &tz);
    
    register_mulitply();

    gettimeofday(&tv2, &tz);
    elapsed = (double) (tv2.tv_sec-tv1.tv_sec) + (double) (tv2.tv_usec-tv1.tv_usec) * 1.e-6;
    printf("Register Multiply Time = %lf \n",elapsed);


    // testare inmultire matrici cu parcurgere folosind pointeri
    gettimeofday(&tv1, &tz);
    
    pointer_multiply();

    gettimeofday(&tv2, &tz);
    elapsed = (double) (tv2.tv_sec-tv1.tv_sec) + (double) (tv2.tv_usec-tv1.tv_usec) * 1.e-6;
    printf("Pointer Multiply Time = %lf \n",elapsed);

}