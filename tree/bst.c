
#include "bst.h"

#include <math.h>
#include <stdlib.h>

bst *bst_create(void)
{
	bst *b = malloc(sizeof(*b));
	if(b) {
		b->root = NULL;
	}

	return b;
}

void bst_destroy(bst *b)
{
	if(!b) {
		return;
	}
	tree_destroy(b->root);
	free(b);
}

static bool tree_search(struct tree *t, double data)
{
	if(!t) {
		return false;
	}
	if(fabs(data - t->data) < .001) {
		return true;
	}

	if(data > t->data) {
		return tree_search(t->right, data);
	} else {
		return tree_search(t->left, data);
	}
}

bool bst_search(bst *b, double data)
{
	if(!b) {
		return false;
	}

	return tree_search(b->root, data);
}

static bool tree_insert(struct tree **t, double data)
{
	if(!*t) {
		*t = tree_create(data);
		return *t;
	}
	struct tree *node = *t;

	if(data > node->data) {
		return tree_insert(&node->right, data);
	} else {
		return tree_insert(&node->left, data);
	}
}

bool bst_insert(bst *b, double data)
{
	if(!b) {
		return false;
	}
	return tree_insert(&b->root, data);
}

static void tree_remove(struct tree **t, double data)
{
	if(!*t) {
		return;
	}
	struct tree *node = *t;

	// If the data is found, time to remove it
	if(fabs(data - node->data) < .001) {

		if(!node->left) {
			// If there is no left-hand side, the
			// only thing that needs to happen is to
			// promote the right-hand child
			*t = node->right;
		} else {
			*t = node->left;

			// The right-hand side of the DELETED node
			// will always be on the furthest-right
			// edge of the left-hand side.  Walk down
			// the right-hand side of this new root,
			// then...
			struct tree *right_edge = *t;
			while(right_edge->right) {
				right_edge = right_edge->right;
			}

			// ...append the original right-hand side
			// on that far-right edge.
			right_edge->right = node->right;
		}

		// Cut off the legs of the removed node,
		// so it will not cascade to any incidental
		// pointers
		node->left = node->right = NULL;
		tree_destroy(node);

		return;
	}

	if(data > node->data) {
		tree_remove(&node->right, data);
	} else {
		tree_remove(&node->left, data);
	}
}

void bst_remove(bst *b, double data)
{
	if(!b) {
		return;
	}
	tree_remove(&b->root, data);
}

