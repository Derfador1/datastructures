
#ifndef LLIST_H
 #define LLIST_H

struct llist {
	double data;
	struct llist *next;
};

struct llist *ll_create(double data);
void ll_destroy(struct llist *l);

void ll_add(struct llist **l, double data);
void ll_remove(struct llist **l);


double ll_sum(struct llist *l);

#endif
