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
	edge * parent;
};
typedef struct element * edge_list;
	

	/* functions creation */


void sort_by_cost(edge * tab_edge[], unsigned int size_tab_edge);

int find(int parent[], int id_node);

void Union(int * parent[], int id_node1, int id_node2);

int* kruskal(edge tab_edge[], unsigned int size_tab_node, unsigned int size_tab_edge);

char** str_split(char* a_str, const char a_delim);

void read_get_sizes(char * filename, int * number_vertices, int * number_edges);

void read_create_arrays(char * filename, node * nodes, edge * edges, int number_vertices, int number_edges);

void head_latex_file(edge tab_edge[], node tab_node[], unsigned int size_tab_node, unsigned int size_tab_edge, char * file_name);

void create_latex_file(edge tab_edge[], node tab_node[], unsigned int size_tab_node, unsigned int size_tab_edge);

void create_latex_file_MST(edge tab_edge[], node tab_node[], int * tab_edge_MST, unsigned int size_tab_node, unsigned int size_tab_edge);

#endif
