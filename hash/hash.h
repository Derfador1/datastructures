
#ifndef HASH_H
 #define HASH_H

typedef struct {
	size_t len;
	double *data;
} hash;

hash *hash_create(void);
void hash_destroy(hash *h);

void hash_insert(hash *h, char *key, double value);
double hash_fetch(hash *h, char *key);

#endif
