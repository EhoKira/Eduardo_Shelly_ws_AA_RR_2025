#include <stdio.h>
#include <stdlib.h>
#include "interpolation_search.h"

int busca_interpolacao(int arr[], int tamanho, int elemento, long long *comparacoes) {
    int esquerda = 0, direita = tamanho - 1;
    (*comparacoes)++;

    while (esquerda <= direita && elemento >= arr[esquerda] && elemento <= arr[direita]) {
        if (esquerda == direita) {
            (*comparacoes)++;
            if (arr[esquerda] == elemento) 
                return esquerda;
            return -1;
        }

        int pos = esquerda + ((double)(direita - esquerda) / (arr[direita] - arr[esquerda])) * (elemento - arr[esquerda]);

        (*comparacoes)++;
        if (arr[pos] == elemento)
            return pos;
        if (arr[pos] < elemento)
            esquerda = pos + 1;
        else
            direita = pos - 1;
    }
    return -1;
}