
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
