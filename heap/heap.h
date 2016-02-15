
#ifndef HEAP_H
 #define HEAP_H

// Min heap (max heap just requires the inverse of the cmp function)

#include <stdbool.h>
#include <stdlib.h>

typedef struct {
	size_t size;
	size_t capacity;
	int (*cmp)(const void *, const void *);
	void **data;
} heap;

heap *heap_create(int (*cmp)(const void *, const void *));
void heap_disassemble(heap *h);
void heap_destroy(heap *h);

bool heap_is_empty(heap *h);
size_t heap_size(heap *h);

bool heap_add(heap *h, void *value);
void *heap_peek_min(heap *h);
void *heap_remove_min(heap *h);

#endif
