#ifndef SIMPLE_HASH_H
#define SIMPLE_HASH_H

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef struct HashNode {
    long long key;
    long long val;
    struct HashNode *next;
} HashNode;

typedef struct HashTable {
    size_t size;      // number of buckets
    HashNode **buckets;
} HashTable;

static inline HashTable *ht_create(size_t size) {
    HashTable *ht = (HashTable*)malloc(sizeof(HashTable));
    ht->size = size;
    ht->buckets = (HashNode**)calloc(size, sizeof(HashNode*));
    return ht;
}

static inline void ht_free(HashTable *ht) {
    if (!ht) return;
    for (size_t i = 0; i < ht->size; ++i) {
        HashNode *n = ht->buckets[i];
        while (n) {
            HashNode *t = n->next;
            free(n);
            n = t;
        }
    }
    free(ht->buckets);
    free(ht);
}

static inline size_t ht_hash(HashTable *ht, long long key) {
    // 64-bit mix -> index
    unsigned long long x = (unsigned long long)key;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
    x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
    x = x ^ (x >> 31);
    return (size_t)(x % ht->size);
}

// set key -> val (overwrite)
static inline void ht_set(HashTable *ht, long long key, long long val) {
    size_t idx = ht_hash(ht, key);
    HashNode *n = ht->buckets[idx];
    while (n) {
        if (n->key == key) {
            n->val = val;
            return;
        }
        n = n->next;
    }
    HashNode *nn = (HashNode*)malloc(sizeof(HashNode));
    nn->key = key; nn->val = val; nn->next = ht->buckets[idx];
    ht->buckets[idx] = nn;
}

// get pointer to value (NULL if not present)
static inline HashNode *ht_find(HashTable *ht, long long key) {
    size_t idx = ht_hash(ht, key);
    HashNode *n = ht->buckets[idx];
    while (n) {
        if (n->key == key) return n;
        n = n->next;
    }
    return NULL;
}

// add delta to existing value (if not present, create with delta)
static inline void ht_add(HashTable *ht, long long key, long long delta) {
    HashNode *n = ht_find(ht, key);
    if (n) n->val += delta;
    else ht_set(ht, key, delta);
}

// get value (if absent, return default 0)
static inline long long ht_get(HashTable *ht, long long key) {
    HashNode *n = ht_find(ht, key);
    return n ? n->val : 0LL;
}

#endif // SIMPLE_HASH_H
