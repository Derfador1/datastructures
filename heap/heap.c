
#include "heap.h"

heap *heap_create(void)
{
	heap *h = malloc(sizeof(*h));
	if(!h) {
		return NULL;
	}

	h->size = h->capacity = 0;
	h->data = NULL;

	return h;
}

void heap_destroy(heap *h)
{
	if(!h) {
		return;
	}

	free(h->data);
	free(h);
}

bool heap_add(heap *h, double value)
{
	if(!h) {
		return false;
	}
}

double heap_get_max(heap *h)
{
	if(!h || h->size == 0) {
		return 0;
	}

	return h->data[0];
}
