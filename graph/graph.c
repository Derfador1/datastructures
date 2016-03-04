
#include "graph.h"

#include <stdlib.h>

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

graph *graph_copy(const graph *g) 
{
	graph *tmp = graph_create();

	struct node *tmp_node = g->nodes;
	while(tmp_node) {
		graph_add_node(tmp, tmp_node->data);
		tmp_node = tmp_node->next;
	}
	tmp_node = g->nodes;
	while(tmp_node) {
		struct edge *test = tmp_node->edges;
		while(test) {
			graph_add_edge(tmp, tmp_node->data, test->to->data, test->weight);
			test = test->next;
		}
		tmp_node = tmp_node->next;
	}
	return tmp;
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
		free((void*)curr->data);
		free(curr);

		curr = tmp;
	}

	free(g);
}

bool graph_add_node(graph *g, const void *data)
{
	if(!g) {
		return false;
	}
	struct node *new_node = malloc(sizeof(*new_node));
	if(!new_node) {
		return false;
	}
	new_node->data = (struct device *)data;
	new_node->edges = NULL;
	new_node->next = g->nodes;

	g->nodes = new_node;

	return true;
}

bool graph_add_edge(graph *g, const void *from, const void *to, double weight)
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
	//printf("input: %lf\n", weight);
	new_edge->to = node_to;
	new_edge->next = node_from->edges;

	node_from->edges = new_edge;

	return true;
}

bool graph_has_node(graph *g, const void *data)
{
	if(!g) {
		return false;
	}

	struct node *curr = g->nodes;
	while(curr) {
		if(curr->data == data) {
			return true;
		}

		curr = curr->next;
	}

	return false;
}

bool graph_remove_node(graph *g, const void *data)
{
	if(!g) {
		return false;
	}

	bool removed = false;
	struct node *curr_node = g->nodes;
	struct node *prev_node = curr_node;
	struct node *target = NULL;

	if(!curr_node) {
		return removed;
	} else if(curr_node->data == data) {
		g->nodes = curr_node->next;

		__graph_remove_edges_from_node(curr_node);

		target = curr_node;
		free(curr_node);
		curr_node = g->nodes;
		removed = true;
	}

	while(curr_node) {
		if(curr_node->data == data) {
			prev_node->next = curr_node->next;

			__graph_remove_edges_from_node(curr_node);

			target = curr_node;
			free(curr_node);
			curr_node = prev_node->next;
			removed = true;
			continue;
		}

		struct edge *curr_edge = curr_node->edges;
		struct edge *prev_edge = curr_edge;

		if(!curr_edge) {
			goto NEXT_NODE;
		} else if((target && curr_edge->to == target) || curr_edge->to->data == data) {
			curr_node->edges = curr_edge->next;
			free(curr_edge);
			goto NEXT_NODE;
		}

		while(curr_edge) {
			if((target && curr_edge->to == target) || curr_edge->to->data == data) {
				prev_edge->next = curr_edge->next;
				free(curr_edge);
				break;
			}

			prev_edge = curr_edge;
			curr_edge = curr_edge->next;
		}

NEXT_NODE:
		prev_node = curr_node;
		curr_node = curr_node->next;
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

double graph_edge_weight(const graph *g, const void *from, const void *to)
{
	if(!g) {
		return 0;
	}

	struct node *curr = g->nodes;
	while(curr && curr->data != from) {
		curr = curr->next;
	}
	if(!curr) {
		return 0;
	}

	struct edge *check = curr->edges;
	while(check && check->to->data == to) {
			check = check->next;
	}
	if(!check) {
		return 0;
	}

	return check->weight;
}

struct llist *graph_adjacent_to(const graph *g, const void *data)
{
	if(!g || !data) {
		return NULL;
	}

	struct node *curr = g->nodes;
	while(curr) {
		if(curr->data == data) {
			if(!curr->edges) {
				return NULL;
			}

			struct llist *head = NULL;
			struct edge *adj = curr->edges;
			while(adj) {
				ll_add(&head, adj->to->data);
				adj = adj->next;
			}

			return head;
		}
		curr = curr->next;
	}

	return NULL;
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

void print_item(const void *data, bool is_node)
{
	struct device *print = (struct device *)data;
	if(is_node) {
		printf("\n%d", print->source_dev_id);
	} 
	else {
		printf(" → %d", print->source_dev_id);
	}
}
