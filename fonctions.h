#ifndef FONCTIONS_H
#define FONCTIONS_H

#include <stdio.h>
#include <stdlib.h>

	/* Structure creation */

struct node{
	int x_node;
	int y_node;
	int id_node;
};
typedef struct node node;


struct edge{
	int node_a;
	int node_b;
	double cost;
};
typedef struct edge edge;


struct element{
	edge val;
	edge * suiv;
};
typedef struct element * edge_list;
	

	/* functions creation */

void sort_by_cost(edge tab_edge[], unsigned int size_tab_edge);

edge_list kruskal(node tab_node[], edge * tab_edge[], unsigned int size_tab_node, unsigned int size_tab_edge);

#endif
