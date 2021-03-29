#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <sys/time.h>

// din grafice se observa o scadere pronuntata pentru L1 in jurul valorii de 35KB
// si 250KB pentru L2

int main(int argc, char* argv[])
{
    if(argc != 4)
    {
        printf("apelati cu %s <line_size> <vector_size> <iterations>\n", argv[0]);
        return -1;
    }

    int64_t l = atoi(argv[1]);  // dimensiunea liniei de cache
    int64_t n = atoi(argv[2]);  // dimensiunea vectorului
    int64_t c = atoi(argv[3]);  // numarul de iteratii

    // TODO alocari si initializari
    char *a = (char*) malloc(sizeof(char) * n);
    if(!a) {
        fprintf(stderr, "Eroare malloc\n");
        exit(12);
    }

    struct timeval start, end;
    gettimeofday(&start, NULL);

    // TODO bucla de test
    // in variabila ops calculati numarul de operatii efectuate
    int64_t ops = 0;
    for(long step = 0; step < c; step++) {
        for(long i = 0; i < n; i+=l) {
            a[i]++;
            ops++;
        }
    }

    

    gettimeofday(&end, NULL);

    float elapsed = ((end.tv_sec - start.tv_sec)*1000000.0f + end.tv_usec - start.tv_usec)/1000000.0f;
    printf("%12lld, %12lld, %12f, %12g\n", n, ops, elapsed, ops/elapsed);

    free(a);

    return 0;
}

