#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Inclua os headers dos seus algoritmos
#include "binary_search_iterative.h"
#include "binary_search_recursive.h"
// #include "interpolation_search.h" // descomente quando quiser incluir

#define REPETICOES 3

// Função para ler o vetor do arquivo
int* ler_arquivo(const char *nome, int *tamanho) {
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

// Função para testar cada algoritmo
void testar_algoritmo(const char *algoritmo, const char *arquivo, int chave, FILE *saida) {
    int n;
    int *vetor = ler_arquivo(arquivo, &n);
    long long total_comp = 0;
    double total_tempo = 0.0;
    int resultado = -1;

    for (int i = 0; i < REPETICOES; i++) {
        long long comparacoes = 0;
        clock_t ini = clock();

        if (strcmp(algoritmo, "binary_iterative") == 0)
            resultado = binary_search_iterative(vetor, n, chave, &comparacoes);
        else if (strcmp(algoritmo, "binary_recursive") == 0)
            resultado = binary_search_recursive(vetor, 0, n-1, chave, &comparacoes);
        // else if (strcmp(algoritmo, "interpolation") == 0)
        //     resultado = interpolation_search(vetor, n, chave, &comparacoes);
        else {
            printf("Algoritmo %s não reconhecido\n", algoritmo);
            free(vetor);
            return;
        }

        clock_t fim = clock();
        total_comp += comparacoes;
        total_tempo += (double)(fim - ini) / CLOCKS_PER_SEC;
        // Salva cada repetição no CSV
        fprintf(saida, "%s,%s,%d,%d,%d,%lld,%.8f\n",
            algoritmo, arquivo, n, chave, resultado, comparacoes,
            (double)(fim - ini)/CLOCKS_PER_SEC);
    }

    printf("Arquivo: %s, Algoritmo: %s, Chave: %d, Média Comparações: %.2f, Média Tempo: %.8fs\n",
           arquivo, algoritmo, chave, (double)total_comp/REPETICOES, total_tempo/REPETICOES);

    free(vetor);
}

int main() {
    const char *algoritmos[] = {"binary_iterative", "binary_recursive"};
    const char *tipos[] = {"sorted", "random"}; // ajuste conforme os arquivos que você tem!
    int tamanhos[] = {1000, 5000, 10000, 50000, 100000, 500000, 1000000};
    int qtd_alg = 2;
    int qtd_tipos = 2;
    int qtd_tam = 7;

    FILE *saida = fopen("test_binary.csv", "w");
    if (!saida) { perror("Erro ao abrir arquivo CSV"); return 1; }
    fprintf(saida, "algoritmo,arquivo,tamanho,chave,indice,comparacoes,tempo\n");

    for (int a = 0; a < qtd_alg; a++) {
        for (int t = 0; t < qtd_tipos; t++) {
            for (int s = 0; s < qtd_tam; s++) {
                char nome_arquivo[200];
                sprintf(nome_arquivo, "Entradas/entrada_%d_%s.txt", tamanhos[s], tipos[t]);
                int chave = tamanhos[s] / 2; // Exemplo: busca o elemento do meio
                printf("Rodando %s em %s (chave %d)...\n", algoritmos[a], nome_arquivo, chave);
                testar_algoritmo(algoritmos[a], nome_arquivo, chave, saida);
                printf("----------\n");
            }
        }
    }
    fclose(saida);

    printf("Todos os resultados salvos em test_binary.csv\n");
    return 0;
}

