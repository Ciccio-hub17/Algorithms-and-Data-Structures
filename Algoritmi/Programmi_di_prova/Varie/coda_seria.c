#include<stdio.h>
#include<stdlib.h>
#include "Graph.h"
#include "UF.h"

typedef struct item_s{
    int alberto;
    int ciccio;
}Item;

typedef struct cell_s {
    int r;
    int c;
    int d;
}cella;

void krusksal (Edge *edges, Graph G){

    Edge *select = malloc (G->E*sizeof (Edge));
    int index = 0;
    
    //Faccio un sort sugli archi mettendo in ordine ascendente i pesi
    for (int i =0, i < G->E; i++){
        if (!UFfind (edges->v, edges->w)){
            UFunion (edges->v, edges->w);
            select[index++] = edges[i];
        }
    }
}

int coloraBFS (int nr, int nc, int **mat, int r, int c, int k, int id){
    int r_new; int c_new;
    int dr[4] = {1, -1, 0, 0};
    int dc [4] = {0, 0, 1, -1};

    cella *queue = malloc (nr*nc*sizeof (cella));

    int head = 0; int tail = 0;

    cella cell;
    cell.r = r; cell.c = c; cell.d = 0;

    queue[tail++] = cell;
    mat[r][c] = id;

    while (head < tail){
        cella current = queue[head++];

        for (int i = 0; i < 4; i++){
            r_new = r + dr[i];
            c_new = c + dc [i];

            if (r_new >= 0 && r_new < r && c_new >= 0 && c_new < c){
                if (mat[r_new][c_new] != id){

                    if (mat[r_new][c_new] == -1){
                        continue;
                    }

                    if (mat[r_new][c_new] > 0){
                        free (queue);
                        return 0;
                    }
                    else{
                        cella next = {r_new, c_new, current.d+1};
                        mat[next.r][next.c] = id;

                        if (next.d < k){
                            queue [tail++] = next;
                        }
                    }
                }
            }
        }
    }

    return 1;
}

int main(int argc, char* argv[]){
    
    printf("\n");
    return 0;
}