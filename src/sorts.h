
#ifndef SORTS_H
 #define SORTS_H

#include <stdbool.h>
#include <stdlib.h>

void shuffle(const void *arr[], size_t len);

void insertion_sort(const void *arr[], size_t len, int (*cmp)(const void *, const void *));
void selection_sort(const void *arr[], size_t len, int (*cmp)(const void *, const void *));
void heapsort(const void *arr[], size_t len, int (*cmp)(const void *, const void *));
void quicksort(const void *arr[], size_t len, int (*cmp)(const void *, const void *));
bool mergesort(const void *arr[], size_t len, int (*cmp)(const void *, const void *));

#endif
