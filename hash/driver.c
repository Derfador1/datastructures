
#include <stdio.h>

#include "double_hash.h"

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

	hash_insert(hashy, "follensbee", 56);
	hash_insert(hashy, "follensbee", 170);
	hash_insert(hashy, "follensbee", 64);

	printf("hillock: %lf\n",
			hash_fetch(hashy, "hillock"));
	printf("graham: %lf\n",
			hash_fetch(hashy, "graham"));
	printf("eggbert: %lf\n",
			hash_fetch(hashy, "eggbert"));
	printf("dickerson: %lf\n",
			hash_fetch(hashy, "dickerson"));
	printf("follensbee: %lf\n",
			hash_fetch(hashy, "follensbee"));

	printf("size: %zu\n", hashy->item_count);

	hash_destroy(hashy);
}
