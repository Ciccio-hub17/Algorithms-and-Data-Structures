#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafo.h"

#define MAX_S 30

typedef struct node_s *link;
typedef struct st_s *ST;

typedef struct node_s{
    int v;
    int wt;
    link next;
}node_t;

typedef struct grafo_s{
    int V;
    int E;
    int **madj;
    link *ladj;
    link z;
    ST tab;
}grafo_t;

typedef struct st_s{
    int count;
    char **table;
}st_t;

void swap (int index1, int index2, int *v){
    int tmp;

    tmp = v[index2];
    v[index2] = v[index1];
    v[index1] = tmp;
    return;
}

int partition (char **table, int l, int r, int * vet_index){
    int i = l, j = r-1;

    for ( ; ; ){
        while (i <= r && strcmp (table[vet_index[i]], table[vet_index[r]]) < 0){
            i++;
        }
        while (j >= l && strcmp (table[vet_index[j]], table[vet_index[r]]) > 0){
            j--;
        }
        if (i >= j){
            break;
        }
        swap (i, j, vet_index);
    }
    swap (r, i, vet_index);

    return i;
}

void quick_sort (int n, char **table, int l, int r, int *vet_index){
    if (l >= r){
        return;
    }

    int q = partition (table, l, r, vet_index);
    quick_sort (n, table, l, q-1, vet_index);
    quick_sort (n, table, q+1, r, vet_index);
    return;
}

void merge (int l, int r, int c, int *vet, Graph G){
    int tmp[r+1];
    int i = l, j = c+1, k = l;

    while (i <= c && j <= r){
        if (strcmp (G->tab->table[vet[i]], G->tab->table[vet[j]]) <= 0){
            tmp[k] = vet[i];
            i++;
        }
        else{
            tmp[k] = vet[j];
            j++;
        }
        k++;
    }

    while (i <= c){
        tmp[k++] = vet[i++];
    }

    while (j <= r){
        tmp[k++] = vet[j++];
    }

    for (k = l; k <= r; k++){
        vet[k] = tmp[k];
    }
    return;
}

void merge_sort (int n, int *vet, int l, int r, Graph G){
    if (l >= r){
        return ;
    }

    int c = (l+r)/2;

    merge_sort (n, vet, l, c, G);
    merge_sort (n, vet, c+1, r, G);
    merge (l, r, c, vet, G);
}

link newNode (int v, int wt, link next){
    link x = malloc (sizeof (node_t));
    x->v = v;
    x->wt = wt;
    x->next = next;
    return x;
}

ST STIinit (int V){
    ST tab = malloc (sizeof(st_t));
    tab->count = 0;
    tab->table = malloc (V*sizeof (char*));
    for (int i = 0; i < V; i++){
        tab->table[i] = malloc (MAX_S*sizeof(char));
    }
    return tab;
}

int **madjInit (int V, int val){
    int **t = malloc (V*sizeof (int*));
    for (int i = 0; i < V; i++){
        t[i] = malloc (V*sizeof (int));
    }

    for (int i = 0; i < V; i++){
        for (int j = 0; j < V; j++){
            t[i][j] = val;
        }
    }

    return t;
}

link* ladjInit (int V, link z){
    link *A = malloc (V*sizeof (link));
    for (int i = 0; i < V; i++){
        A[i] = z;
    }
    return A;
}

Graph grafoInit (int V){
    Graph G = malloc (sizeof (grafo_t));
    G->V = V;
    G->E = 0;
    G->madj = madjInit (V, 0);
    G->z = newNode (-1, -1, NULL);
    G->ladj = ladjInit (G->V, G->z);
    G->tab = STIinit (V);
    return G;
}

void STFree (ST tab){
    for (int i = 0; i < tab->count; i++){
        free (tab->table[i]);
    }
    free (tab->table);
}

void madjFree (int ** madj, Graph G){
    for (int i = 0; i < G->V; i++){
        free (madj[i]);
    }
    free (madj);
}

void ladjFree (link *A, Graph G){
    link x, next;
    for (int i = 0; i < G->V; i++){
        for (x = A[i]; x != G->z; x = next){
            next = x->next;
            free (x);
        }
    }
    free (A);
}

void GFree (Graph G){
    madjFree (G->madj, G);
    ladjFree (G->ladj, G);
    free (G->z);
    STFree (G->tab);
    free (G);
}

int GetIndexByLabel (char label[], Graph G){
    for (int i = 0; i < G->tab->count; i++){
        if (strcmp (G->tab->table[i], label) == 0){
            return i;
        }
    }
    return -1;
}

char * GetLabelByIndex (Graph G, int index){
    return G->tab->table[index];
}

void search_sotto_grafo_mat (Graph G, char label1[], char label2[], char label3[]){
    int index1 = GetIndexByLabel (label1, G);
    int index2 = GetIndexByLabel (label2, G);
    int index3 = GetIndexByLabel (label3, G);
    if (G->madj[index1][index2] && G->madj[index1][index3] && G->madj[index2][index3]){
        printf ("I vertici scelti formano un sotto-grafo\n");
    }
    else{
        printf ("I vertici scelti non formano un sotto-grafo\n");
    }
}

void search_sotto_grafo_lista (Graph G, char label1[], char label2[], char label3[]){
    int index1 = GetIndexByLabel (label1, G);
    int index2 = GetIndexByLabel (label2, G);
    int index3 = GetIndexByLabel (label3, G);
    link x;
    int trovato1 = 0, trovato2 = 0, trovato3 = 0;
    for (x = G->ladj[index1]; x != G->z; x = x->next){
        if (x->v == index2){
            trovato1 = 1;
        }
        if (x->v == index3){
            trovato2 = 1;
        }
    }
    for (x = G->ladj[index2]; x != NULL && !trovato3; x = x->next){
        if (x->v == index3){
            trovato3 = 1;
        }
    }
    if (trovato1 && trovato2 && trovato3){
        printf ("I vertici scelti formano un sottografo\n");
    }
    else{
        printf ("I vertici scelti non formano un sottografo\n");
    }

}

void genera_lista(Graph G){
    for (int i = 0; i < G->V; i++){
        for (int j = 0; j < G->V; j++){
            if (G->madj[i][j] != 0){
                G->ladj[i] = newNode (j, G->madj[i][j], G->ladj[i]);
            }
        }
    }
    printf ("Lista di adiacenza generata\n");
}

void print_order (Graph G){
    int *vet_vertex_ordered = malloc (G->V*sizeof (int));
    int *vet_edges = malloc (G->V*sizeof (int));
    int count;
    for (int i = 0; i < G->V; i++){
        vet_vertex_ordered[i] = i;
    }
    quick_sort (G->V, G->tab->table, 0, G->V-1, vet_vertex_ordered);
    for (int i = 0; i < G->V; i++){
        count = 0;
        printf ("%s\n", G->tab->table[vet_vertex_ordered[i]]);
        for (int j = 0; j < G->V; j++){
            if (G->madj[vet_vertex_ordered[i]][j]){
                vet_edges[count++] = j;
            }
        }
        merge_sort (count, vet_edges, 0, count-1, G);
        printf ("Il vertice è connesso a questi altri vertici\n");
        for (int j = 0; j < count; j++){
            printf ("\t%s, wt: %d\n", G->tab->table[vet_edges[j]], G->madj[vet_vertex_ordered[i]][vet_edges[j]]);
        }
    }

    free (vet_edges);
    free (vet_vertex_ordered);
}

Graph read_file (char filename[]){
    FILE *input;
    if ((input = fopen(filename, "r")) == NULL){
        printf("Errore nell'apertura del file: \"%s\"", filename);
        exit(-1);
    }
    
    char id_elab1[MAX_S], id_elab2[MAX_S];
    int flusso, prov_v = 0, presente1, presente2, index1, index2, count_edges = 0;
    while (fscanf (input, "%*s %*s %*s %*s %*d") != EOF){
        prov_v++;
    }
    prov_v = prov_v*2;
    Graph G = grafoInit (prov_v);
    prov_v = prov_v / 2;
    G->E = prov_v;
    
    rewind (input);

    while (fscanf (input, "%s %*s %s %*s %d", id_elab1, id_elab2, &flusso) == 3){
        index1 = GetIndexByLabel (id_elab1, G);
        index2 = GetIndexByLabel (id_elab2, G);
        if (index1 == -1){
            strcpy (G->tab->table[G->tab->count], id_elab1);
            index1 = G->tab->count;
            G->tab->count++;
        }
        if (index2 == -1){
            strcpy (G->tab->table[G->tab->count], id_elab2);
            index2 = G->tab->count;
            G->tab->count++;
        }
        G->madj[index1][index2] = flusso;
        G->madj[index2][index1] = flusso;
    }
    G->V = G->tab->count;

    
    fclose(input);
    return G;
}