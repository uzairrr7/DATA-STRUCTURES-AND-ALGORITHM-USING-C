// subarray_sum_k.c
// Count contiguous subarrays with sum == K using prefix sums + hashmap.
// Complexity: O(n) average, Space: O(n)

#include <stdio.h>
#include <stdlib.h>
#include "simple_hash.h"

long long count_subarrays_with_sum_k(const long long arr[], size_t n, long long K) {
    // choose hash table size (a prime-ish bucket count)
    HashTable *ht = ht_create(262144); // power of two ~ big enough
    long long count = 0;
    long long prefix = 0;
    ht_set(ht, 0LL, 1LL); // empty prefix occurs once

    for (size_t i=0;i<n;i++) {
        prefix += arr[i];
        long long need = prefix - K;
        count += ht_get(ht, need);
        ht_add(ht, prefix, 1LL);
    }
    ht_free(ht);
    return count;
}

int main(void) {
    long long arr1[] = {1,1,1};
    size_t n1 = sizeof(arr1)/sizeof(arr1[0]);
    printf("Array: 1 1 1, K=2 => Count = %lld (expected 2)\n",
           count_subarrays_with_sum_k(arr1,n1,2));

    long long arr2[] = {1,-1,0};
    size_t n2 = sizeof(arr2)/sizeof(arr2[0]);
    printf("Array: 1 -1 0, K=0 => Count = %lld (expected 3)\n",
           count_subarrays_with_sum_k(arr2,n2,0));
    return 0;
}
