
#ifndef HEAP_H
 #define HEAP_H

#include <stdlib.h>

typedef struct {
	size_t size;
	size_t capacity;
	double *data;
} heap;

heap *heap_create(void);
void heap_destroy(heap *h);

bool heap_add(heap *h, double value);
double heap_get_max(heap *h);

#endif
