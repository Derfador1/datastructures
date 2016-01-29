
#ifndef TREE_H
 #define TREE_H


struct tree {
	double data;
	struct tree *left;
	struct tree *right;
};

struct tree *tree_create(double data);
void tree_destroy(struct tree *t);

void tree_iterate(struct tree *t, void (*func)(double));

bool tree_add(struct tree *t, double data);
double tree_remove(struct tree *t);

#endif
