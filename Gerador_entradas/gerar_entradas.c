#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <errno.h>

// Função para criar o diretório
void criar_pasta(const char *caminho) {
    if (mkdir(caminho, 0777) == -1) {
        if (errno != EEXIST) {
            perror("Erro ao criar pasta");
            exit(1);
        }
    }
}

// Função para gerar uma sequência ordenada
void gerar_ordenado(int *arr, int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = i + 1;
    }
}

// Função para gerar uma distribuição uniforme de números inteiros, de 1 a n
void gerar_uniforme(int *arr, int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % n + 1;
    }
}

// Função para salvar os dados no arquivo
void salvar_em_arquivo(int *arr, int n, const char *nome_arquivo) {
    FILE *fp = fopen(nome_arquivo, "w");
    if (!fp) {
        perror("Erro ao criar arquivo");
        exit(1);
    }
    for (int i = 0; i < n; i++) {
        fprintf(fp, "%d\n", arr[i]);
    }
    fclose(fp);
}

int main() {
    int tamanhos[] = {1000, 5000, 10000, 50000, 100000, 500000, 1000000, 5000000, 10000000};
    const int num_tamanhos = sizeof(tamanhos) / sizeof(tamanhos[0]);
    char nome_arquivo[100];
    
    // Criação da pasta "../Entradas"
    criar_pasta("../Entradas");

    srand(time(NULL));  // Semente para gerar números aleatórios

    for (int i = 0; i < num_tamanhos; i++) {
        int n = tamanhos[i];
        int *arr = malloc(n * sizeof(int));
        if (!arr) {
            fprintf(stderr, "Erro de memória para tamanho %d\n", n);
            exit(1);
        }

        // Gerar entrada ordenada crescente
        gerar_ordenado(arr, n);
        snprintf(nome_arquivo, sizeof(nome_arquivo), "../Entradas/entrada_%d_sorted.txt", n);
        salvar_em_arquivo(arr, n, nome_arquivo);

        // Gerar entrada uniforme (valores gerados entre 1 e n)
        gerar_uniforme(arr, n);
        snprintf(nome_arquivo, sizeof(nome_arquivo), "../Entradas/entrada_%d_uniform.txt", n);
        salvar_em_arquivo(arr, n, nome_arquivo);

        free(arr);
    }

    printf("Arquivos gerados com sucesso.\n");
    return 0;
}