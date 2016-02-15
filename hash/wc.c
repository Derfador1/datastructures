
#include <stdio.h>

#include "double_hash.h"

void print_pair(const char *key, double value)
{
	printf("%lf %s", value, key);
}

int main(int argc, char *argv[])
{
	if(argc != 2) {
		fprintf(stderr, "Usage: %s <file>\n", argv[0]);
		return 1;
	}

	FILE *fp = fopen(argv[1], "r");
	if(!fp) {
		perror("Could not open file");
		return 2;
	}

	hash *words = hash_create();
	if(!words) {
		fprintf(stderr, "Out of memory");
		fclose(fp);
		return 4;
	}

	char buf[128];
	while(!feof(fp)) {
		if(!fgets(buf, sizeof(buf), fp)) {
			continue;
		}

		hash_insert(words, buf, 1 + hash_fetch(words, buf));
	}

	hash_traverse(words,
			print_pair);


	hash_destroy(words);
	fclose(fp);
}
