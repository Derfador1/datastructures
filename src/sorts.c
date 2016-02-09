
#include "sorts.h"

void shuffle(const void *arr[], size_t len)
{
	if(!arr || len < 2) {
		return;
	}

	for (size_t i = 0; i < len - 1; i++) {
		size_t j = i + rand() / (RAND_MAX / (len - i) + 1);
		// SWAP
		const void *tmp = arr[j];
		arr[j] = arr[i];
		arr[i] = tmp;
	}
}

bool insertion_sort(const void *arr[], size_t len, int (*cmp)(const void *, const void *))
{
	if(!arr || !cmp || len < 2) {
		return false;
	}
	for(size_t n = 1; n < len; ++n) {
		size_t k = n;
		const void *tmp = arr[k];
		while(k > 0 && cmp(arr[k-1], tmp) > 0) {
			// SWAP
			arr[k] = arr[k-1];
			--k;
		}
		// SWAP
		arr[k] = tmp;
	}

	return true;
}

bool selection_sort(const void *arr[], size_t len, int (*cmp)(const void *, const void *))
{
	if(!arr || !cmp || len < 2) {
		return false;
	}
	for(size_t n = 0; n < len; ++n) {
		size_t cur = n;
		for(size_t m = cur+1; m < len; ++m) {
			if(cmp(arr[m], arr[cur]) < 0) {
				cur = m;
			}
		}
		// SWAP
		const void *tmp = arr[cur];
		arr[cur] = arr[n];
		arr[n] = tmp;
	}

	return true;
}

static void heapify(size_t pos, const void *arr[], size_t len,
		int (*cmp)(const void *, const void *))
{
	size_t left = 2*pos+1;
	size_t right = left+2;
	size_t cur = pos;
	if(left < len && cmp(arr[left], arr[cur]) > 0) {
		cur = left;
	}
	if(right < len && cmp(arr[right], arr[cur]) > 0) {
		cur = right;
	}
	if(cur != pos) {
		// SWAP
		const void *tmp = arr[cur];
		arr[cur] = arr[pos];
		arr[pos] = tmp;
		heapify(cur, arr, len, cmp);
	}
}

static void build_heap(const void *arr[], size_t len, int (*cmp)(const void *, const void *))
{
	size_t pos = (len-1)/2;
	while(pos) {
		heapify(pos, arr, len, cmp);
		--pos;
	}
}

bool heapsort(const void *arr[], size_t len, int (*cmp)(const void *, const void *))
{
	if(!arr || !cmp || len < 2) {
		return false;
	}
	build_heap(arr, len, cmp);

	while(--len) {
		// SWAP
		const void *tmp = arr[0];
		arr[0] = arr[len];
		arr[len] = tmp;
		heapify(0, arr, len, cmp);
	}

	return true;
}

static size_t partition(const void *arr[], size_t len, int (*cmp)(const void *, const void *))
{
	const void *pivot = arr[len-1];
	size_t slot = 0;

	for(size_t n=0; n < len-1; ++n) {
		if(cmp(arr[n], pivot) < 1) {
			// SWAP
			const void *tmp = arr[slot];
			arr[slot] = arr[n];
			arr[n] = tmp;
			++slot;
		}
	}

	// SWAP
	const void *tmp = arr[slot];
	arr[slot] = arr[len-1];
	arr[len-1] = tmp;
	return slot;
}

bool quicksort(const void *arr[], size_t len, int (*cmp)(const void *, const void *))
{
	if(!arr || !cmp || len < 2) {
		return false;
	}
	shuffle(arr, len);
	size_t pivot = partition(arr, len, cmp);

	if(pivot > 0) {
		quicksort(arr, pivot, cmp);
	}
	if(pivot < len) {
		// +1, since the pivot is sorted
		quicksort(arr + pivot+1, len - (pivot+1), cmp);
	}

	return true;
}

static void merge(const void *arr[], size_t midpoint, size_t len,
		int (*cmp)(const void *, const void *), const void **tmp)
{
	size_t pos = 0;
	size_t p1 = 0;
	size_t p2 = midpoint;
	while(p1 < midpoint && p2 < len) {
		if(cmp(arr[p2], arr[p1]) < 0) {
			tmp[pos++] = arr[p2++];
		} else {
			tmp[pos++] = arr[p1++];
		}
	}

	while(p1 < midpoint) {
		tmp[pos++] = arr[p1++];
	}
	while(p2 < len) {
		tmp[pos++] = arr[p2++];
	}

	while(--pos) {
		arr[pos] = tmp[pos];
	}
}

static void mergesort_range(const void *arr[], size_t len,
		int (*cmp)(const void *, const void *), const void **tmp)
{
	if(len < 2) {
		return;
	}

	size_t middle = len / 2;
	mergesort_range(arr, middle, cmp, tmp);
	mergesort_range(arr + middle, len - middle, cmp, tmp);
	merge(arr, middle, len, cmp, tmp);
}

bool mergesort(const void *arr[], size_t len, int (*cmp)(const void *, const void *))
{
	if(!arr || !cmp || len < 2) {
		return false;
	}
	const void **tmp = malloc(len * sizeof(*tmp));
	if(!tmp) {
		return false;
	}
	mergesort_range(arr, len, cmp, tmp);

	free(tmp);
	return true;
}

