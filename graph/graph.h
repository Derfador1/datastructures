#ifndef GRAPH_H
 #define GRAPH_H

#include <stdbool.h>

struct edge {
	int weight;
	struct node *to;
	struct edge *next;
};

struct node {
	void *data;
	struct edge *edges;
	struct node *next;
};

typedef struct {
	struct node *nodes;
} graph;


graph *graph_create(void);
void graph_disassemble(graph *g);
void graph_destroy(graph *g);

bool graph_add_node(graph *g, void *data);
bool graph_add_edge(graph *g, const void *from, const void *to, int weight);

bool graph_remove_node(graph *g, const void *data);
bool graph_remove_edge(graph *g, const void *from, const void *to);

bool graph_get_adjacent(const graph *g, const void *data);

void graph_print(const graph *g, void to_print(const void *, bool is_node));

#endif
