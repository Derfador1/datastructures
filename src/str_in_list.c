
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool str_in_list(const char *needle, const char *arr[], size_t sz)
{
	size_t low = 0;
	size_t high = sz-1;

	while(low < high) {
		size_t n = low + (high - low)/2;
		int result = strcmp(needle, arr[n]);

		if(result == 0) {
			return true;
		} else if(result < 0) {
			high = n-1;
		} else {
			low = n+1;
		}
	}

	return !strcmp(needle, arr[low + (high - low)/2]);
}

const char *data[] = {
	"Bashful",
	"Doc",
	"Dopey",
	"Grumpy",
	"Happy",
	"Sleepy",
	"Sneezy"
};

int main(void)
{

	if(str_in_list("Sneezy", data, 7)) {
		printf("Sneezy is a member\n");
	} else {
		printf("Sneezy is NOT a member\n");
	}

	if(str_in_list("Sleepy", data, 7)) {
		printf("Sleepy is a member\n");
	} else {
		printf("Sleepy is NOT a member\n");
	}

	if(str_in_list("Tyrion", data, 7)) {
		printf("Tyrion is a member\n");
	} else {
		printf("Tyrion is NOT a member\n");
	}

	if(str_in_list("Edward", data, 7)) {
		printf("Edward is a member\n");
	} else {
		printf("Edward is NOT a member\n");
	}



}
