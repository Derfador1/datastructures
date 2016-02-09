
#include <stdio.h>

#include "hash.h"

int main(void)
{
	hash *hashy = hash_create();

	hash_insert(hashy, "able", 13);
	hash_insert(hashy, "baker", 97);
	hash_insert(hashy, "charlie",2);


	printf("baker: %lf\n",
			hash_fetch(hashy, "baker"));


	hash_destroy(hashy);
}
