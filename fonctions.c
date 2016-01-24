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
				tmp = (*tab_edge)[i];
				(*tab_edge)[i] = (*tab_edge)[j];
				(*tab_edge)[j] = tmp;
			}
		}
	}
}

int find(int parent[], int id_node){
	if (parent[id_node] != id_node) { printf(""); 
		parent[id_node] = find(parent, parent[id_node]);}
	return parent[id_node];
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
	int * parent;
	int i;
	edge_MST = (int *)malloc((size_tab_node-1)*sizeof(int));
	parent = (int *)malloc((size_tab_node+1)*sizeof(int));
	sort_by_cost(&tab_edge, size_tab_edge); //trie des arêtes de G par coût croissant
	for (i=1; i <= size_tab_node; ++i) { // Chaque noeud est initialisé comme son propre parent
		parent[i] = i;
	}
	while (G_size < size_tab_node-1) {
		if (find(parent, tab_edge[e].node_a) != find(parent, tab_edge[e].node_b)) {
			edge_MST[G_size] = e;
			Union(&parent, tab_edge[e].node_a, tab_edge[e].node_b);
			G_size++;
		}
		e++;
	}
	return edge_MST;
}


char** str_split(char* a_str, const char a_delim)
{
    char** result = 0;
    size_t count = 0;
    char* tmp = a_str;
    char* last_comma = 0;
    char delim[2];
    delim[0] = a_delim;
    delim[1] = 0;

    /* Count how many elements will be extracted. */
    while (*tmp)
    {
        if (a_delim == *tmp)
        {
            count++;
            last_comma = tmp;
        }
        tmp++;
    }

    /* Add space for trailing token. */
    count += last_comma < (a_str + strlen(a_str) - 1);

    /* Add space for terminating null string so caller
       knows where the list of returned strings ends. */
   count++;

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
}


void read_get_sizes(char * filename, int * number_vertices, int * number_edges){
    FILE * fp;
       char * line = NULL;
       char ** exploded_string;
       size_t len = 0;
       ssize_t read;

       fp = fopen(filename, "r");
       if (fp == NULL)
           exit(EXIT_FAILURE);

        read = getline(&line, &len, fp);
        int line_counter = 1;
        exploded_string = str_split(line, ' ');
        *number_vertices = atoi(exploded_string[0]);
        *number_edges = atoi(exploded_string[1]);
        fclose(fp);
       if (line)
           free(line);
}

void read_create_arrays(char * filename, node * nodes, edge * edges, int number_vertices, int number_edges){
       FILE * fp;
       char * line = NULL;
       char ** exploded_string;
       size_t len = 0;
       ssize_t read;
       int i;

       fp = fopen(filename, "r");
       if (fp == NULL)
           exit(EXIT_FAILURE);

        read = getline(&line, &len, fp);
        int line_counter = 1;
        int node_counter = 0;
        int edge_counter = 0;

       while ((read = getline(&line, &len, fp)) != -1) {
        //line = current line
           //printf("Retrieved line of length %zu :\n", read);
           //pour tous les noeuds
           if (line_counter <= number_vertices) {
                exploded_string = str_split(line, ' ');
                node new_node;
                new_node.x_node = atoi(exploded_string[0]);
                new_node.y_node = atoi(exploded_string[1]);
                new_node.id_node = node_counter+1;
                nodes[node_counter] = new_node;
                node_counter++;
           }
           //pour tous les arcs
           else {
                exploded_string = str_split(line, ' ');
                edge new_edge;
                new_edge.node_a = atoi(exploded_string[0]);
                new_edge.node_b = atoi(exploded_string[1]);
                new_edge.cost = atof(exploded_string[2]);
                edges[edge_counter] = new_edge;
                edge_counter++;
           }
			line_counter++;
		}
		fclose(fp);
		if (line)
			free(line);
}


void create_latex_file(edge tab_edge[], node tab_node[], unsigned int size_tab_edge, unsigned int size_tab_node) {
	FILE * fichier = NULL;
	fichier = fopen("G.tex", "w+");
	int i;
	if (fichier != NULL) {
		fputs("\\documentclass{article}\n\\usepackage{pstricks}\n\\usepackage{pst-node}\n\\usepackage[top=2cm, bottom=2cm, left=2cm , right=2cm]{geometry}\n\\begin{document}\n\\centering \\large{\\tt G.tex}\n", fichier);
		fputs("\\begin{pspicture*}(-0.5,-0.5)(1.5,1.5)\n", fichier);
		for (i = 0; i < size_tab_node; ++i) 
			fprintf(fichier, "\\cnode(%d,%d){0.22cm}{%d}\\rput(%d,%d){\\tt %d}\n",tab_node[i].x_node, tab_node[i].y_node, tab_node[i].id_node, tab_node[i].x_node, tab_node[i].y_node, tab_node[i].id_node);
		
		fputs("% edges\n",fichier);
		
		for (i = 0; i < size_tab_edge; ++i) 
			fprintf(fichier, "\\ncline {-}{%d}{%d}\n", tab_edge[i].node_a, tab_edge[i].node_b);
			
		fputs("\\end{pspicture*}\n", fichier);
		fputs("\\end{document}", fichier);
	}
	else exit(EXIT_FAILURE);
	fclose(fichier);
}


void create_latex_file_MST(edge tab_edge[], node tab_node[], edge tab_edge_MST[]){
	
}

