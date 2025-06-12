#include "binary_search_recursive.h"

int binary_search_recursive(int *arr, int l, int r, int key, long long *comparacoes) {
    if (l > r) return -1;
    (*comparacoes)++;
    int m = l + (r - l) / 2;
    if (arr[m] == key) return m;
    if (arr[m] < key) return binary_search_recursive(arr, m+1, r, key, comparacoes);
    else return binary_search_recursive(arr, l, m-1, key, comparacoes);
}
