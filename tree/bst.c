
#include "bst.h"

#include <stdlib.h>

bst *bst_create(void)
{
	bst *b = malloc(sizeof(*b));
	if(b) {
		b->root = NULL;
	}

	return b;
}

void bst_destroy(bst *b);
