
#include <stdio.h>

#include "search.h"

int main(void)
{
	char data[] = { 2, 5, 7, 12, 65, 98,
		103, 120, 122, 125 };

	char n = 'A';

	if(cbinary_search(n, data, 
				sizeof(data) / sizeof(data[0]))) {
		printf("Found the value %d\n", n);
	} else {
		printf("Could not find value %d\n", n);
	}

}
