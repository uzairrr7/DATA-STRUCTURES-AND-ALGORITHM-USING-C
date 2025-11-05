// prefix_sums.c
// Build prefix sums and answer range queries inclusive.
// Build: O(n), Query: O(1), Space: O(n)

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long long *pref; // pref[0]=0, pref[i]=sum of arr[0..i-1]
    size_t n;
} Prefix;

Prefix *prefix_create(const long long arr[], size_t n) {
    Prefix *p = malloc(sizeof(Prefix));
    p->n = n;
    p->pref = malloc((n+1)*sizeof(long long));
    p->pref[0] = 0;
    for (size_t i=0;i<n;i++) p->pref[i+1] = p->pref[i] + arr[i];
    return p;
}

long long range_sum(Prefix *p, size_t l, size_t r) { // inclusive indices, 0-based
    if (l > r || r >= p->n) {
        fprintf(stderr, "Invalid indices\n");
        return 0;
    }
    return p->pref[r+1] - p->pref[l];
}

void prefix_free(Prefix *p) {
    if (!p) return;
    free(p->pref);
    free(p);
}

int main(void) {
    long long arr[] = {3,1,4,1,5,9};
    size_t n = sizeof(arr)/sizeof(arr[0]);
    Prefix *p = prefix_create(arr,n);
    printf("Array: ");
    for (size_t i=0;i<n;i++) printf("%lld ", arr[i]);
    printf("\nSum(0..2) = %lld\n", range_sum(p,0,2)); // 3+1+4=8
    printf("Sum(2..4) = %lld\n", range_sum(p,2,4)); // 4+1+5=10
    prefix_free(p);
    return 0;
}
