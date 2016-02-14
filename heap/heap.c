
#include "heap.h"

static const size_t DEFAULT_HEAP_CAPACITY = 8;

#define PARENT(n) (((n)-1)/2)
#define LEFT(n) (2*(n) + 1)
#define RIGHT(n) (2*(n) + 2)

static bool __resize_heap(heap *h);
static void __heapify(heap *h, size_t n);

heap *heap_create(int (*cmp)(const void *, const void *))
{
	if(!cmp) {
		return NULL;
	}

	heap *h = malloc(sizeof(*h));
	if(!h) {
		return NULL;
	}

	h->data = malloc(DEFAULT_HEAP_CAPACITY * sizeof(*h->data));
	if(!h->data) {
		free(h);
		return NULL;
	}

	h->size = 0;
	h->capacity = DEFAULT_HEAP_CAPACITY;
	h->cmp = cmp;

	return h;
}

void heap_disassemble(heap *h)
{
	if(!h) {
		return;
	}

	free(h->data);
	free(h);
}

void heap_destroy(heap *h)
{
	if(!h) {
		return;
	}

	for(size_t n = 0; n < h->size; ++n) {
		free(h->data[n]);
	}

	free(h->data);
	free(h);
}

bool heap_add(heap *h, void *value)
{
	if(!h) {
		return false;
	}

	size_t n = h->size;

	h->data[n] = value;
	if(h->size == h->capacity) {
		if(!__resize_heap(h)) {
			return false;
		}
	}

	while(n > 0 && h->cmp(value, h->data[PARENT(n)]) > 0) {
		h->data[n] = h->data[PARENT(n)];
		n = PARENT(n);
		h->data[n] = value;
	}

	++h->size;

	return true;
}

void *heap_peek_max(heap *h)
{
	if(!h || h->size == 0) {
		return NULL;
	}

	return h->data[0];
}

void *heap_remove_max(heap *h)
{
	if(!h || h->size == 0) {
		return NULL;
	}

	void *value = h->data[0];

	h->data[0] = h->data[--h->size];

	__heapify(h, 0);

	return value;
}

static bool __resize_heap(heap *h)
{
	void **tmp = realloc(h->data, 2*h->capacity * sizeof(*h->data));
	if(!tmp) {
		return false;
	}

	h->data = tmp;
	return true;
}

static void __heapify(heap *h, size_t n)
{
	while(LEFT(n) < h->size) {
		size_t best = n;
		size_t left = LEFT(n);
		size_t right = RIGHT(n);

		if(h->cmp(h->data[best], h->data[left]) < 0) {
			best = left;
		}
		if(right < h->size && h->cmp(h->data[best], h->data[right]) < 0) {
			best = right;
		}

		if(best == n) {
			break;
		}

		void *tmp = h->data[best];
		h->data[best] = h->data[n];
		h->data[n] = tmp;
		n = best;
	}
}
