
#ifndef HASH_H
 #define HASH_H

#include <stdlib.h>

struct h_llist {
	char *key;
	double value;
	struct h_llist *next;
};

typedef struct {
	size_t len;
	struct h_llist **data;
} hash;

hash *hash_create(void);
void hash_destroy(hash *h);

void hash_insert(hash *h, const char *key, double value);
double hash_fetch(hash *h, const char *key);

#endif
