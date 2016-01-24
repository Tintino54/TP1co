#include "fonctions.h"

/*
 * Trie un tableau d'arc par poids croissant
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
/*
 * Détermine le noeud représentant du sous_ensemble de noeud contenant id_node
 * */
int find(int parent[], int id_node){
	if (parent[id_node] != id_node) { printf(""); 
		parent[id_node] = find(parent, parent[id_node]);}
	return parent[id_node];
}

/*
 * Uni deux sous_ensemble de noeuds
 * */
void Union(int * parent[], int id_node1, int id_node2){
	
	int root_node2 = find(*parent, id_node2);
	if (id_node1 != id_node2) 
		(*parent)[root_node2] = find(*parent, id_node1); //Le noeud représentant du sous_ensemble de id_node2 prend la valeur du noeud représentant du sous ensemble de id_node1
}

/*
 * Calcul et retourne un tableau contenant les indices des arcs présent dans le MST 
 * */
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
	while (G_size < size_tab_node-1) { //Tant que le nombre d'arc trouvé est inérieur aux nombre de noeuds -1
		if (find(parent, tab_edge[e].node_a) != find(parent, tab_edge[e].node_b)) {
			edge_MST[G_size] = e;
			Union(&parent, tab_edge[e].node_a, tab_edge[e].node_b);
			G_size++;
		}
		e++;
	}
	return edge_MST;
}

/*
 * Fragmente une chaine de caractère par un délimiteur et renvoi un tableau contenant chaque fragment de la chaine de caractère
 * */
char** str_split(char* a_str, const char a_delim)
{
    char** result = 0;
    size_t count = 0;
    char* tmp = a_str;
    char* last_comma = 0;
    char delim[2];
    delim[0] = a_delim;
    delim[1] = 0;

    //Compte combien d'éléments seront extraits
    while (*tmp)
    {
        if (a_delim == *tmp)
        {
            count++;
            last_comma = tmp;
        }
        tmp++;
    }

    // Add space for trailing token.
    count += last_comma < (a_str + strlen(a_str) - 1);

    //Add space for terminating null string so caller knows where the list of returned strings ends.
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

/*
 * Lit dans le fichier text contenant le graphe le nombre d'arcs et le nombre de noeuds
 * */
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
        exploded_string = str_split(line, ' ');
        *number_vertices = atoi(exploded_string[0]);
        *number_edges = atoi(exploded_string[1]);
        fclose(fp);
       if (line)
           free(line);
}

/*
 * Créer le tableaux contenant tout les arcs, et celui contenant tout les noeuds
 * */
void read_create_arrays(char * filename, node * nodes, edge * edges, int number_vertices, int number_edges){
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
        int node_counter = 0;
        int edge_counter = 0;

       while ((read = getline(&line, &len, fp)) != -1) {
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

/*
 * Ecris le début du fichier latex, ainsi que tout les noeuds
 * */
void head_latex_file(edge tab_edge[], node tab_node[], unsigned int size_tab_node, unsigned int size_tab_edge, char * file){
	FILE * fichier = NULL;
	fichier = fopen(file, "w+");
	int i;
	if (fichier != NULL) {
		fputs("\\documentclass{article}\n\\usepackage{pstricks}\n\\usepackage{pst-node}\n\\usepackage[top=2cm, bottom=2cm, left=2cm , right=2cm]{geometry}\n\\begin{document}\n\\centering \\large{\\tt G.tex}\n", fichier);
		fputs("\\psscalebox{0.35}\n{", fichier);
		fputs("\\begin{pspicture*}(0,0)(50,50)\n", fichier);
		for (i = 0; i < size_tab_node; ++i) 
			fprintf(fichier, "\\cnode(%d,%d){1cm}{%d}\\rput(%d,%d){\\tt %d}\n",tab_node[i].x_node, tab_node[i].y_node, tab_node[i].id_node, tab_node[i].x_node, tab_node[i].y_node, tab_node[i].id_node);
		
		fputs("% edges\n",fichier);
	}
	else exit(EXIT_FAILURE);
	fclose(fichier);
	
}


/*
 * Ecris le fichier latex "G.tex" qui affiche tout les arcs du graphe 
 * */
void create_latex_file(edge tab_edge[], node tab_node[], unsigned int size_tab_node, unsigned int size_tab_edge) {
	FILE * fichier = NULL;
	char * file_name = "G.tex";
	int i;
	head_latex_file(tab_edge, tab_node, size_tab_node, size_tab_edge, file_name);
	fichier = fopen(file_name, "a");
	if (fichier != NULL) { 	
		for (i = 0; i < size_tab_edge; ++i) 
			fprintf(fichier, "\\ncline {-}{%d}{%d}\n", tab_edge[i].node_a, tab_edge[i].node_b);
			
		fputs("\\end{pspicture*}}\n", fichier);
		fputs("\\end{document}", fichier);
	}
	else exit(EXIT_FAILURE);
	fclose(fichier);
}

/*
 * Ecris le fichier latex "G.kruskal.tex" qui contient seulement les arcs présent dans le MST
 * */
void create_latex_file_MST(edge tab_edge[], node tab_node[], int * tab_edge_MST, unsigned int size_tab_node, unsigned int size_tab_edge){
	FILE * fichier = NULL;
	int i;
	char * file_name = "G.kruskal.tex";
	head_latex_file(tab_edge, tab_node, size_tab_node, size_tab_edge, file_name);
	fichier = fopen(file_name, "a");
	if (fichier != NULL) {
		for (i = 0; i < size_tab_node-1; ++i)
			fprintf(fichier,"\\ncline[linecolor=red,linewidth = 3pt]{-}{%d}{%d}\n", tab_edge[tab_edge_MST[i]].node_a, tab_edge[tab_edge_MST[i]].node_b);
		
		fputs("\\end{pspicture*}}\n", fichier);
		fputs("\\end{document}", fichier);
	}
	else exit(EXIT_FAILURE);
	fclose(fichier);
}

