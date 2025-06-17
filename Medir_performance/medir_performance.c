#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "../Algoritmos/binary_search.h"

void medirPerformance(int arr[], int size, int valorProcurado,
                      int repeticao, const char* tipoEntrada) {
    struct timeval start, end;
    FILE *file = fopen("resultados/performance.csv", "a");
    if (!file) { perror("fopen"); return; }

    gettimeofday(&start, NULL);
    int result = binarySearch(arr, 0, size - 1, valorProcurado);
    gettimeofday(&end,   NULL);

    long us = (end.tv_sec - start.tv_sec)*1000000
            + (end.tv_usec - start.tv_usec);

    fprintf(file, "%d,%d,%ld,%s,%d,%s\n",
            size, repeticao, us,
            (result != -1) ? "Encontrado" : "Não Encontrado",
            valorProcurado, tipoEntrada);
    fclose(file);
}

int main() {
    int entradas[] = {1000,5000,50000,100000,500000,1000000,10000000};
    for (int i = 0; i < 7; i++) {
        int n = entradas[i];
        int *arr = malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) arr[j] = j+1;
        int alvo = arr[n-1];
        for (int rep = 1; rep <= 3; rep++)
            medirPerformance(arr, n, alvo, rep, "Crescente");
        free(arr);
    }
    return 0;
}