
#ifndef BST_H
 #define BST_H

#include <stdbool.h>

#include "tree.h"

typedef struct {
	struct tree *root;
} bst;

bst *bst_create(void);
void bst_destroy(bst *b);

bool bst_insert(bst *b, double data);
bool bst_search(bst *b, double data);
void bst_remove(bst *b, double data);

#endif
