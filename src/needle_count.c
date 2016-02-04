
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *data[] = {
	"Bashful", "Bashful",
	"Doc", "Doc", "Doc", "Doc", "Doc", "Doc", "Doc",
	"Dopey", "Dopey", "Dopey", "Dopey", "Dopey", "Dopey",
	"Grumpy", "Grumpy",
	"Happy", "Happy", "Happy", "Happy", "Happy", "Happy", "Happy", "Happy", "Happy", "Happy", "Happy", "Happy", "Happy", "Happy", "Happy", "Happy", "Happy", "Happy", "Happy", "Happy",
	"Sleepy",
	"Sneezy", "Sneezy", "Sneezy", "Sneezy", "Sneezy", "Sneezy", "Sneezy", "Sneezy", "Sneezy", "Sneezy", "Sneezy"
};

size_t data_size(void)
{
	return sizeof(data)/sizeof(data[0]);
}


size_t needle_count(const char *needle, const char *arr[], size_t n)
{

	size_t start = 0;
	size_t end = n - 1;

	// Find the start
	size_t low = start;
	size_t high = end;

	while(low < high) {
		size_t idx = low + (high - low)/2;
		int result = strcmp(needle, arr[idx]);

		// If we found the needle we are looking for,
		// we need to keep looking backward until we
		// find the transition point between our needle
		// and "not-our-needle"
		if(result <= 0) {
			high = idx - 1;
		} else if(result > 0) {
			low = idx + 1;
		}
	}
	// If our markers end on the same spot, they are either
	// on first instance or just to the left of the first
	// instance
	if(low == high) {
		if(0 == strcmp(needle, arr[low])) {
			start = low;
		} else if(0 == strcmp(needle, arr[low + 1])) {
			start = low + 1;
		}
	} else {
		if(0 == strcmp(needle, arr[low])) {
			start = low;
		} else if(0 == strcmp(needle, arr[high])) {
			start = high;
		}
	}
	// TODO: What happens if the needle doesn't exist?



	low = start;
	high = end;

	// Find the end
	while(low < high) {
		size_t idx = low + (high - low)/2;
		int result = strcmp(needle, arr[idx]);

		// If we found the needle we are looking for,
		// we need to keep looking forward until we
		// find the transition point between our needle
		// and "not-our-needle"
		if(result < 0) {
			high = idx - 1;
		} else if(result >= 0) {
			low = idx + 1;
		}
	}
	// If our markers end on the same spot, they are either
	// on first instance or just to the left of the first
	// instance
	if(low == high) {
		if(0 == strcmp(needle, arr[high])) {
			end = high;
		} else if(0 == strcmp(needle, arr[high - 1])) {
			end = high - 1;
		}
		// TODO: What happens if the needle doesn't exist?
	} else {
		if(0 == strcmp(needle, arr[low])) {
			end = low;
		} else if(0 == strcmp(needle, arr[high])) {
			end = high;
		}
	}


	return end - start + 1;
}

int main(void)
{

	printf("There are %zu lights\n", data_size());
	printf("Happy  %zu (20)\n", needle_count("Happy", data, data_size()));
	printf("Sleepy %zu (1)\n", needle_count("Sleepy", data, data_size()));
	printf("Tyrion %zu (0)\n", needle_count("Tyrion", data, data_size()));

}
