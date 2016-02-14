
#ifndef HEAP_H
 #define HEAP_H

// Max heap (min heap just requires the inverse of the cmp function)

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

bool heap_add(heap *h, void *value);
void *heap_peek_max(heap *h);
void *heap_remove_max(heap *h);

#endif
