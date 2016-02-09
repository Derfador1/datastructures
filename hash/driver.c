
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
	hash_insert(hashy, "dickerson", 2003);
	hash_insert(hashy, "eggbert", 2005);
	hash_insert(hashy, "follensbee", 2600);
	hash_insert(hashy, "graham", 2090);
	hash_insert(hashy, "hillock", 2200);
	hash_insert(hashy, "igloo", 2031);
	hash_insert(hashy, "jamiroquai", 2900);
	hash_insert(hashy, "killua", 2080);


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

	printf("capacity: %zu\n", hashy->capacity);


	hash_destroy(hashy);
}
