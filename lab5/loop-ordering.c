#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define N 300

double *a, *b, *c;

void ijk_muliply() {
	int i, j, k;
	double sum;

	for (i=0;i<N;i++){
	   for (j=0;j<N;j++){
	      sum=0;
	      for (k=0;k<N;k++)
	         sum+=a[i * N + k]*b[k * N + j];
	      c[i * N + j] = sum; 
	   }
	}
}

void ikj_muliply() {
	int i, j, k;
	double sum;

	for (i=0;i<N;i++){
	   for (k=0;k<N;k++){
	      sum=0;
	      for (j=0;j<N;j++)
	         sum+=a[i * N + k]*b[k * N + j];
	      c[i * N + j] = sum; 
	   }
	}
}

void jik_muliply() {
	int i, j, k;
	double sum;

	for (j=0;j<N;j++){
	   for (i=0;i<N;i++){
	      sum=0;
	      for (k=0;k<N;k++)
	         sum+=a[i * N + k]*b[k * N + j];
	      c[i * N + j] = sum; 
	   }
	}
}


void jki_muliply() {
	int i, j, k;
	double sum;

	for (j=0;j<N;j++){
	   for (k=0;k<N;k++){
	      sum=0;
	      for (i=0;i<N;i++)
	         sum+=a[i * N + k]*b[k * N + j];
	      c[i * N + j] = sum; 
	   }
	}
}

void kij_muliply() {
	int i, j, k;
	double sum;

	for (k=0;k<N;k++){
	   for (i=0;i<N;i++){
	      sum=0;
	      for (j=0;j<N;j++)
	         sum+=a[i * N + k]*b[k * N + j];
	      c[i * N + j] = sum; 
	   }
	}
}

void kji_muliply() {
	int i, j, k;
	double sum;

	for (k=0;k<N;k++){
	   for (j=0;j<N;j++){
	      sum=0;
	      for (i=0;i<N;i++)
	         sum+=a[i * N + k]*b[k * N + j];
	      c[i * N + j] = sum; 
	   }
	}
}

int main () {
	struct timeval tv1, tv2;
    struct timezone tz;
    double elapsed;

    a = (double *)malloc(N*N * sizeof(double));
    b = (double *)malloc(N*N * sizeof(double));
    c = (double *)malloc(N*N * sizeof(double));

    // inmultire ijk
    gettimeofday(&tv1, &tz);
    
    ijk_muliply();

    gettimeofday(&tv2, &tz);
    elapsed = (double) (tv2.tv_sec-tv1.tv_sec) + (double) (tv2.tv_usec-tv1.tv_usec) * 1.e-6;
    printf("ijk time = %lf \n",elapsed);


    // inmultire ikj
    gettimeofday(&tv1, &tz);
    
    ikj_muliply();

    gettimeofday(&tv2, &tz);
    elapsed = (double) (tv2.tv_sec-tv1.tv_sec) + (double) (tv2.tv_usec-tv1.tv_usec) * 1.e-6;
    printf("ikj time = %lf \n",elapsed);


    // inmultire jik
    gettimeofday(&tv1, &tz);
    
    jik_muliply();

    gettimeofday(&tv2, &tz);
    elapsed = (double) (tv2.tv_sec-tv1.tv_sec) + (double) (tv2.tv_usec-tv1.tv_usec) * 1.e-6;
    printf("jik time = %lf \n",elapsed);



    // inmultire jki
    gettimeofday(&tv1, &tz);
    
    jki_muliply();

    gettimeofday(&tv2, &tz);
    elapsed = (double) (tv2.tv_sec-tv1.tv_sec) + (double) (tv2.tv_usec-tv1.tv_usec) * 1.e-6;
    printf("jki time = %lf \n",elapsed);


    // inmultire kij
    gettimeofday(&tv1, &tz);
    
    kij_muliply();

    gettimeofday(&tv2, &tz);
    elapsed = (double) (tv2.tv_sec-tv1.tv_sec) + (double) (tv2.tv_usec-tv1.tv_usec) * 1.e-6;
    printf("kij time = %lf \n",elapsed);


    // inmultire kji
    gettimeofday(&tv1, &tz);
    
    kji_muliply();

    gettimeofday(&tv2, &tz);
    elapsed = (double) (tv2.tv_sec-tv1.tv_sec) + (double) (tv2.tv_usec-tv1.tv_usec) * 1.e-6;
    printf("kji time = %lf \n",elapsed);


    free(a);
    free(b);
    free(c);
}