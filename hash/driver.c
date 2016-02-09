
#include <stdio.h>

#include "hash.h"

int main(void)
{
	hash *hashy = hash_create();

	hash_insert(hashy, "able", 13);
	hash_insert(hashy, "baker", 97);
	hash_insert(hashy, "charlie",2);
	hash_insert(hashy, "(neato)", 18);
	hash_insert(hashy, "chef", 2000);


	printf("able: %lf\n",
			hash_fetch(hashy, "able"));
	printf("baker: %lf\n",
			hash_fetch(hashy, "baker"));
	printf("charlie: %lf\n",
			hash_fetch(hashy, "charlie"));
	printf("(neato): %lf\n",
			hash_fetch(hashy, "(neato)"));
	printf("chef: %lf\n",
			hash_fetch(hashy, "chef"));


	hash_destroy(hashy);
}
