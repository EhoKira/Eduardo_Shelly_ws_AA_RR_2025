#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

// Incluindo os cabeçalhos dos algoritmos de busca
#include "../Algoritmos/binary_search.h"
#include "../Algoritmos/interpolation_search.h"

// Função para carregar o array de um arquivo
int* carregar_array(const char* nome, int* tamanho) {
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

void medirComparacoesBinaria(int *arr, int size, int chave, const char *tipoEntrada, FILE *saida) {
    long long total_comp = 0;
    int resultado = -1;

    for (int i = 0; i < 20; i++) {
        long long comparacoes = 0;

        resultado = binarySearch(arr, 0, size - 1, chave, &comparacoes);

        total_comp += comparacoes;

        fprintf(saida, "binary_recursive,%s,%d,%d,%d,%lld\n",
            tipoEntrada, size, chave, resultado, comparacoes);
    }
}

void medirComparacoesInterpolacao(int *arr, int size, int chave, const char *tipoEntrada, FILE *saida) {
    long long total_comp = 0;
    int resultado = -1;

    for (int i = 0; i < 20; i++) {
        long long comparacoes = 0;

        // Realiza a busca por interpolação
        resultado = busca_interpolacao(arr, size, chave, &comparacoes);

        total_comp += comparacoes;


        fprintf(saida, "interpolation_search,%s,%d,%d,%d,%lld\n",
            tipoEntrada, size, chave, resultado, comparacoes);
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

    // Arquivo CSV para busca binária
    FILE *saida_binaria = fopen("../Resultados/test_binary_uniform.csv", "w");
    if (!saida_binaria) { perror("Erro ao abrir arquivo CSV de busca binária"); return 1; }
    fprintf(saida_binaria, "algoritmo,arquivo,tamanho,chave,indice,comparacoes\n");

    // Arquivo CSV para busca por interpolação
    FILE *saida_interpolacao = fopen("../Resultados/test_interpolation_uniform.csv", "w");
    if (!saida_interpolacao) { perror("Erro ao abrir arquivo CSV de busca por interpolação"); return 1; }
    fprintf(saida_interpolacao, "algoritmo,arquivo,tamanho,chave,indice,comparacoes\n");

    for (int i = 0; i < num_entradas; i++) {
        int *arr;
        int tamanho;
        const char *tipoEntrada = strstr(entradas[i], "sorted") ? "Ordenado" : "Uniforme";

        arr = carregar_array(entradas[i], &tamanho);

        int chave = arr[tamanho - 1];

        medirComparacoesBinaria(arr, tamanho, chave, tipoEntrada, saida_binaria);

        medirComparacoesInterpolacao(arr, tamanho, chave, tipoEntrada, saida_interpolacao);

        free(arr);
    }

    fclose(saida_binaria);
    fclose(saida_interpolacao);
    printf("Todos os resultados salvos em test_binary.csv e test_interpolation.csv\n");
    return 0;
}