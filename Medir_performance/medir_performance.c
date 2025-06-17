#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include "../Algoritmos/binary_search.h"

// Função para carregar o array de um arquivo
int* carregar_array(const char *nome, int *tamanho) {
    FILE *fp = fopen(nome, "r");
    if (!fp) { perror("Erro ao abrir arquivo"); exit(1); }
    int capacidade = 1000, val, count = 0;
    int *vetor = malloc(capacidade * sizeof(int));
    while (fscanf(fp, "%d", &val) == 1) {
        if (count == capacidade) {
            capacidade *= 2;
            vetor = realloc(vetor, capacidade * sizeof(int));
        }
        vetor[count++] = val;
    }
    fclose(fp);
    *tamanho = count;
    return vetor;
}

// Função para medir o tempo de execução e comparações
void medirPerformance(int *arr, int size, int chave, const char *tipoEntrada, FILE *saida) {
    long long total_comp = 0;
    double total_tempo = 0.0;
    int resultado = -1;

    for (int i = 0; i < 20; i++){
        long long comparacoes = 0;
        
        struct timeval start, end;
        gettimeofday(&start, NULL);

        resultado = binarySearch(arr, 0, size - 1, chave);

        gettimeofday(&end, NULL);
        total_comp += comparacoes;
        total_tempo += (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);

         fprintf(saida, "binary_recursive,%s,%d,%d,%d,%lld,%.8f\n",
            tipoEntrada, size, chave, resultado, comparacoes,
            (double)(end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec) / 1000000.0);
    }

}

int main() {
    const char *entradas[] = {
        "../Entradas/entrada_1000_sorted.txt",
        "../Entradas/entrada_5000_sorted.txt",
        "../Entradas/entrada_10000_sorted.txt",
        "../Entradas/entrada_50000_sorted.txt",
        "../Entradas/entrada_100000_sorted.txt",
        "../Entradas/entrada_500000_sorted.txt",
        "../Entradas/entrada_1000000_sorted.txt",
        "../Entradas/entrada_5000000_sorted.txt",
        "../Entradas/entrada_10000000_sorted.txt",

        "../Entradas/entrada_1000_uniform.txt",
        "../Entradas/entrada_5000_uniform.txt",
        "../Entradas/entrada_10000_uniform.txt",
        "../Entradas/entrada_50000_uniform.txt",
        "../Entradas/entrada_100000_uniform.txt",
        "../Entradas/entrada_500000_uniform.txt",
        "../Entradas/entrada_1000000_uniform.txt",
        "../Entradas/entrada_5000000_uniform.txt",
        "../Entradas/entrada_10000000_uniform.txt"
    };

    const int num_entradas = sizeof(entradas) / sizeof(entradas[0]);
    FILE *saida = fopen("../Resultados/test_binary.csv", "w");
    if (!saida) { perror("Erro ao abrir arquivo CSV"); return 1; }
    fprintf(saida, "algoritmo,arquivo,tamanho,chave,indice,comparacoes,tempo\n");

    for (int i = 0; i < num_entradas; i++) {
        int *arr;
        int tamanho;
        const char *tipoEntrada = strstr(entradas[i], "sorted") ? "Ordenado" : "Uniforme";

        // Ler o arquivo de entrada
        arr = carregar_array(entradas[i], &tamanho);

        // Definir a chave que será buscada
        int chave = arr[tamanho - 1];  // Busca o último valor (pior caso)

        // Medir performance
        medirPerformance(arr, tamanho, chave, tipoEntrada, saida);

        free(arr);
    }

    fclose(saida);  // Fechar arquivo CSV
    printf("Todos os resultados salvos em test_binary.csv\n");
    return 0;
}