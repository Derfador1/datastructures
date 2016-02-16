#ifndef GRAPH_H
 #define GRAPH_H

#include <stdbool.h>
#include <stdlib.h>

#include "llist.h"


typedef struct _adjllist_graph graph;

graph *graph_create(void);
void graph_disassemble(graph *g);
void graph_destroy(graph *g);

bool graph_add_node(graph *g, const void *data);
bool graph_add_edge(graph *g, const void *from, const void *to, int weight);

bool graph_has_node(graph *g, const void *data);

bool graph_remove_node(graph *g, const void *data);
bool graph_remove_edge(graph *g, const void *from, const void *to);

size_t graph_node_count(const graph *g);
size_t graph_edge_count(const graph *g);

int graph_edge_weight(const graph *g, const void *from, const void *to);

struct llist *graph_adjacent_to(const graph *g, const void *data);

void graph_print(const graph *g, void to_print(const void *, bool is_node));

#endif
