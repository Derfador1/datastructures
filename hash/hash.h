
#ifndef HASH_H
 #define HASH_H

#include <stdbool.h>
#include <stdlib.h>

typedef struct _hash hash;

hash *hash_create(void);
void hash_destroy(hash *h);
void hash_disassemble(hash *h);

bool hash_insert(hash *h, const void *key, void *value);
bool hash_remove(hash *h, const void *key);

bool hash_exists(hash *h, const void *key);
void *hash_fetch(hash *h, const void *key);

void hash_traverse(hash *h, void (*func)(const char *, void *));

#endif
