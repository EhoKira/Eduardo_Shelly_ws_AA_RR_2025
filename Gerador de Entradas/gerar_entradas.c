#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <errno.h>

// Função para criar o diretório
void criar_pasta(const char *caminho) {
    // Tenta criar a pasta e verifica se foi bem-sucedido
    if (mkdir(caminho, 0777) == -1) {
        // Se a pasta já existir, não faz nada
        if (errno != EEXIST) {
            perror("Erro ao criar pasta");
            exit(1);
        }
    }
}

void gerar_ordenado(int *arr, int n) {
    for (int i = 0; i < n; i++)
        arr[i] = i + 1;
}

void gerar_decrescente(int *arr, int n) {
    for (int i = 0; i < n; i++)
        arr[i] = n - i;
}

void embaralhar(int *arr, int n) {
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
    }
}

void salvar_em_arquivo(int *arr, int n, const char *nome_arquivo) {
    FILE *fp = fopen(nome_arquivo, "w");
    if (!fp) {
        perror("Erro ao criar arquivo");
        exit(1);
    }
    for (int i = 0; i < n; i++)
        fprintf(fp, "%d\n", arr[i]);
    fclose(fp);
}

int main() {
    int tamanhos[] = {1000, 5000, 10000, 50000, 100000, 500000, 1000000};
    const int num_tamanhos = sizeof(tamanhos) / sizeof(tamanhos[0]);
    char nome_arquivo[100];
    
    // Criação da pasta "../entradas"
    criar_pasta("../Entradas");  // Ajuste o caminho relativo conforme onde executa

    srand(time(NULL)); // semente para números aleatórios

    for (int i = 0; i < num_tamanhos; i++) {
        int n = tamanhos[i];
        int *arr = malloc(n * sizeof(int));
        if (!arr) {
            fprintf(stderr, "Erro de memória para tamanho %d\n", n);
            exit(1);
        }

        // Ordenado crescente
        gerar_ordenado(arr, n);
        snprintf(nome_arquivo, sizeof(nome_arquivo), "../Entradas/entrada_%d_sorted.txt", n);
        salvar_em_arquivo(arr, n, nome_arquivo);

        // Aleatório
        gerar_ordenado(arr, n);
        embaralhar(arr, n);
        snprintf(nome_arquivo, sizeof(nome_arquivo), "../Entradas/entrada_%d_random.txt", n);
        salvar_em_arquivo(arr, n, nome_arquivo);

        free(arr);
    }

    printf("Arquivos gerados com sucesso.\n");
    return 0;
}