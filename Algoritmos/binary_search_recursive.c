#include <stdio.h>
#include "binary_search.h"

int binarySearch(int arr[], int low, int high, int x, long long *comparacoes) {
    (*comparacoes)++;

    if (high >= low) {
        int mid = low + (high - low) / 2;

        if (arr[mid] == x)
            return mid;

        if (arr[mid] < x)
            return binarySearch(arr, mid + 1, high, x, comparacoes);

        return binarySearch(arr, low, mid - 1, x, comparacoes);
    }

    return -1;
}
