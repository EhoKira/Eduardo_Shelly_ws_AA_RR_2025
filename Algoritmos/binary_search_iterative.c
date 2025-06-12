#include "binary_search_iterative.h"

int binary_search_iterative(int *arr, int n, int key, long long *comparacoes) {
    int l = 0, r = n - 1;
    while (l <= r) {
        (*comparacoes)++;
        int m = l + (r - l) / 2;
        if (arr[m] == key) return m;
        if (arr[m] < key) l = m + 1;
        else r = m - 1;
    }
    return -1;
}
