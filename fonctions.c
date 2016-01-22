#include "fonctions.h"

/*
 * Trie un tableau de 
 * */
void sort_by_cost(edge * tab_edge[], unsigned int size_tab_edge) {
	int i, j;
	edge tmp;
	for (i = 0; i < size_tab_edge-1; ++i) {
		for (j = i+1; j < size_tab_edge; ++j) {
			if ((*tab_edge)[i].cost > (*tab_edge)[j].cost) {
				tmp = *tab_edge[i];
				(*tab_edge)[i] = (*tab_edge)[j];
				(*tab_edge)[j] = tmp;
			}
		}
	}
}

int find(int parent[], int id_node){
	if (parent[id_node-1] != id_node) 
		parent[id_node-1] = find(parent, parent[id_node-1]);
	
	return parent[id_node+1];
}

void Union(int * parent[], int id_node1, int id_node2){
	
	int root_node2 = find(*parent, id_node2);
	if (id_node1 != id_node2) 
		(*parent)[root_node2] = find(*parent, id_node1); //Le noeud représentant du sous_ensemble de id_node2 prend la valeur du noeud représentant du sous ensemble de id_node1
}


int* kruskal(edge tab_edge[], unsigned int size_tab_node, unsigned int size_tab_edge) {
	int * edge_MST; // Tableau d'indices des arcs présent dans l'arbre couvrant minimum
	int G_size = 0; // nombre d'arc rentré dans l'arbre couvrant minimum
	int e = 0; // nombre d'arc de tab_edge déjà traité
	int edge_MST_index = 0;
	int * parent;
	int i;
	edge_MST = (int *)malloc((size_tab_node-1)*sizeof(int));
	parent = (int *)malloc((size_tab_node+1)*sizeof(int));
	sort_by_cost(&tab_edge, size_tab_edge); //trie des arêtes de G par cout croissant
	for (i=1; i <= size_tab_node; ++i) { // Chaque noeud est initialisé comme son propre parent
		parent[i] = i;
	}
	while (G_size < size_tab_node - 1) {
		if (find(parent, tab_edge[e].node_a) != find(parent, tab_edge[e].node_b)) {
			edge_MST[edge_MST_index] = e;
			Union(&parent, tab_edge[e].node_a, tab_edge[e].node_b);
			G_size++;
		}
		e++;
	}
	return edge_MST;
}


/*char** str_split(char* a_str, const char a_delim)
{
    char** result    = 0;
    size_t count     = 0;
    char* tmp        = a_str;
    char* last_comma = 0;
    char delim[2];
    delim[0] = a_delim;
    delim[1] = 0;*/

    /* Count how many elements will be extracted. */
 /*   while (*tmp)
    {
        if (a_delim == *tmp)
        {
            count++;
            last_comma = tmp;
        }
        tmp++;
    }*/

    /* Add space for trailing token. */
    /*count += last_comma < (a_str + strlen(a_str) - 1);*/

    /* Add space for terminating null string so caller
       knows where the list of returned strings ends. */
   /* count++;

    result = malloc(sizeof(char*) * count);

    if (result)
    {
        size_t idx  = 0;
        char* token = strtok(a_str, delim);

        while (token)
        {
            *(result + idx++) = strdup(token);
            token = strtok(0, delim);
        }
        *(result + idx) = 0;
    }

    return result;
}*/
