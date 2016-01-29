
#ifndef TREE_H
 #define TREE_H

struct tree {
	double data;
	struct tree *left;
	struct tree *right;
};

struct tree *tree_create(double data);
void tree_destroy(struct tree *t);

void tree_preorder(struct tree *t, void (*func)(double));
void tree_inorder(struct tree *t, void (*func)(double));
void tree_postorder(struct tree *t, void (*func)(double));

void tree_levelorder(struct tree *t, void (*func)(double));


#endif
