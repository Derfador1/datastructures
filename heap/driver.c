
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

#include "heap.h"

int int_lt(const void *a, const void *b)
{
	return (intptr_t)a - (intptr_t)b;
}

int main(void)
{
	heap *heapy = heap_create(int_lt);

	heap_add(heapy, (void *)8);
	heap_add(heapy, (void *)7);
	heap_add(heapy, (void *)5);
	heap_add(heapy, (void *)2);
	heap_add(heapy, (void *)9);
	heap_add(heapy, (void *)1);

	while(!heap_is_empty(heapy)) {
		printf("%" PRIdPTR "\n", (intptr_t)heap_remove_min(heapy));
	}
	heap_add(heapy, (void *)7);
	heap_add(heapy, (void *)5);
	heap_add(heapy, (void *)5);
	heap_add(heapy, (void *)2);
	heap_add(heapy, (void *)9);
	heap_add(heapy, (void *)5);
	heap_add(heapy, (void *)2);
	heap_add(heapy, (void *)9);
	heap_add(heapy, (void *)2);
	heap_add(heapy, (void *)9);
	heap_add(heapy, (void *)1);
	while(!heap_is_empty(heapy)) {
		printf("%" PRIdPTR "\n", (intptr_t)heap_remove_min(heapy));
	}

	heap_disassemble(heapy);
}
