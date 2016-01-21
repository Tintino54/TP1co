#include "fonctions.h"

void sort_by_cost(edge * tab_edge[], unsigned int size_tab_edge) {
	int i, j;
	edge tmp;
	for (i = 0; i < size_tab_edge-1; ++i) {
		for (j = i+1; j < size_tab_edge; ++j) {
			if ((*tab_edge)[i].cost > (*tab_edge)[j].cost) {
				tmp = *tab_edge[i];
				(*tab_edge)[i] = (*tab_edge)[j];
				(*tab_edg)e[j] = tmp;
			}
		}
	}
}


edge_list kruskal(node tab_node[], edge tab_edge[], unsigned int size_tab_node, unsigned int size_tab_edge) {
	edge_list G = NULL;
	sort_by_cost(&tab_edge, size_tab_edge);

	return G;
}
