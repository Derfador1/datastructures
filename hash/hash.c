
#include "hash.h"

// static so that it will only be seen
// in this compilation unit
static const size_t DEFAULT_SIZE = 10;

hash *hash_create(void)
{
	hash *h = malloc(sizeof(*h));
	if(!h) {
		return NULL;
	}

	h->data = calloc(DEFAULT_SIZE,
			sizeof(*h->data));
	if(!h->data) {
		free(h);
		return NULL;
	}

	h->len = DEFAULT_SIZE;

	return h;
}

void hash_destroy(hash *h)
{
	if(h) {
		free(h->data);
		free(h);
	}
}

static size_t hashish(char *key,
		size_t len)
{
	return key[0] % len;
}

void hash_insert(hash *h,
		char *key, double value)
{
	if(!h || !key) {
		return;
	}

	size_t idx = hashish(key, h->len);

	h->data[idx] = value;
}

double hash_fetch(hash *h, char *key)
{
	if(!h || !key) {
		return 0;
	}

	size_t idx = hashish(key, h->len);

	return h->data[idx];
}
