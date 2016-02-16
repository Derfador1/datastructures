
#include "graph.h"

#include <stdlib.h>

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

struct _adjllist_graph {
	struct node *nodes;
};

void __graph_remove_edges_from_node(struct node *v);

graph *graph_create(void)
{
	graph *g = malloc(sizeof(*g));
	if(!g) {
		return NULL;
	}
	g->nodes = NULL;

	return g;
}

void graph_disassemble(graph *g)
{
	if(!g) {
		return;
	}

	struct node *curr = g->nodes;
	while(curr) {
		struct edge *e = curr->edges;
		while(e) {
			struct edge *tmp = e->next;
			free(e);

			e = tmp;
		}

		struct node *tmp = curr->next;
		free(curr);

		curr = tmp;
	}

	free(g);
}

void graph_destroy(graph *g)
{
	if(!g) {
		return;
	}

	struct node *curr = g->nodes;
	while(curr) {
		struct edge *e = curr->edges;
		while(e) {
			struct edge *tmp = e->next;
			free(e);

			e = tmp;
		}

		struct node *tmp = curr->next;
		free(curr->data);
		free(curr);

		curr = tmp;
	}

	free(g);
}

bool graph_add_node(graph *g, void *data)
{
	if(!g) {
		return false;
	}
	struct node *new_node = malloc(sizeof(*new_node));
	if(!new_node) {
		return false;
	}
	new_node->data = data;
	new_node->edges = NULL;
	new_node->next = g->nodes;

	g->nodes = new_node;

	return true;
}

bool graph_add_edge(graph *g, const void *from, const void *to, int weight)
{
	if(!g) {
		return false;
	}
	struct node *node_from=NULL, *node_to=NULL;

	// Find the two nodes; it is allowed for them to be the same node
	struct node *curr = g->nodes;
	while(curr && !(node_from && node_to)) {
		if(curr->data == from) {
			node_from = curr;
		}
		if(curr->data == to) {
			node_to = curr;
		}
		curr = curr->next;
	}
	if(!(node_from && node_to)) {
		return false;
	}

	// Check if an edge already exists between the two
	struct edge *check = node_from->edges;
	while(check) {
		if(check->to == node_to) {
			check->weight = weight;
			return true;
		}
		check = check->next;
	}

	// Insert new edge at front of list
	struct edge *new_edge = malloc(sizeof(*new_edge));
	if(!new_edge) {
		return false;
	}
	new_edge->weight = weight;
	new_edge->to = node_to;
	new_edge->next = node_from->edges;

	node_from->edges = new_edge;

	return true;
}

bool graph_remove_node(graph *g, const void *data)
{
	if(!g) {
		return false;
	}

	bool removed = false;
	struct node *curr = g->nodes;
	if(!curr) {
		return removed;
	} else if(curr->data == data) {
		g->nodes = curr->next;

		__graph_remove_edges_from_node(curr);
		free(curr);
		removed = true;
	}

	struct node *prev = curr;
	curr = curr->next;
	while(curr) {
		if(curr->data == data) {
			prev->next = curr->next;

			__graph_remove_edges_from_node(curr);
			free(curr);
			removed = true;
		}

		struct edge *check = curr->edges;
		if(!check) {
			break;
		} else if(check->to->data == data) {
			curr->edges = check->next;
			free(check);
			break;
		}

		while(check && check->next) {
			if(check->next->to->data == data) {
				struct edge *to_remove = check->next;
				check->next = to_remove->next;
				free(to_remove);
				break;
			}

			check = check->next;
		}

		prev = curr;
		curr = curr->next;
	}

	return removed;
}

bool graph_remove_edge(graph *g, const void *from, const void *to)
{
	if(!g) {
		return false;
	}

	struct node *curr = g->nodes;
	while(curr) {
		if(curr->data != from) {
			curr = curr->next;
		}

		struct edge *check = curr->edges;
		if(!check) {
			return false;
		} else if(check->to->data == to) {
			curr->edges = check->next;
			free(check);
			return true;
		}

		while(check && check->next) {
			if(check->next->to->data == to) {
				struct edge *to_remove = check->next;
				check->next = to_remove->next;
				free(to_remove);
				return true;
			}

			check = check->next;
		}

		return false;
	}

	return false;
}

size_t graph_node_count(const graph *g)
{
	if(!g) {
		return 0;
	}

	size_t count = 0;
	struct node *curr = g->nodes;
	while(curr) {
		++count;
		curr = curr->next;
	}

	return count;
}

size_t graph_edge_count(const graph *g)
{
	if(!g) {
		return 0;
	}

	size_t count = 0;
	struct node *curr = g->nodes;
	while(curr) {
		struct edge *check = curr->edges;
		while(check) {
			++count;
			check = check->next;
		}
		curr = curr->next;
	}

	return count;
}

void graph_print(const graph *g, void to_print(const void *, bool is_node))
{
	if(!g) {
		return;
	}

	struct node *curr = g->nodes;
	while(curr) {
		to_print(curr->data, true);

		struct edge *check = curr->edges;
		while(check) {
			to_print(check->to->data, false);
			check = check->next;
		}

		curr = curr->next;
	}
}

void __graph_remove_edges_from_node(struct node *v)
{
	struct edge *e = v->edges;
	while(e) {
		struct edge *tmp = e->next;
		free(e);

		e = tmp;
	}
}
