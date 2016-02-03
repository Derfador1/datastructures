
#ifndef SEARCH_H
 #define SEARCH_H

#include <stdbool.h>
#include <stdlib.h>

// Finds needle in the sorted array
bool cbinary_search(const char needle,
		const char *arr, const size_t sz);

bool binary_search(const void *needle,
		const void *arr[], const size_t sz,
		int (*cmp)(const void *, const void *)
		);

unsigned int find_max(const unsigned int *arr,
		const size_t sz);

#endif
