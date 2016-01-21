#ifndef FONCTIONS_H
#define FONCTIONS_H

#include <stdio.h>
#include <stdlib.h>

	/* Structure creation */

struct node {
	int x_node;
	int y_node;
	int id_node;
};
typedef struct node node;


struct edge {
	int node_a;
	int node_b;
	double cost;
};
typedef struct edge edge;

	/* functions creation */

char** str_split(char* a_str, const char a_delim);

#endif
