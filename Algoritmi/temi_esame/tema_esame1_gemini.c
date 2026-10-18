#include<stdio.h>
#include<stdlib.h>

typedef enum{false, true} bool;
#define FILE_MAP "mappa.txt"
#define FILE_PROP "proposta.txt"

typedef struct {
    int r; int c;
}cell;

int **alloc_map (int nr, int nc){
    int *m = malloc(nr*sizeof(int));
    for (int i = 0; i < nr; i ++){
        m[i] = calloc(nc, sizeof(int));
    }
    return m;
}


int **read_map(char *filename, int *nr, int *nc){
    FILE *fp = fopen(filename, "r");
    fscanf(fp, "%d %d", nr, nc);
    int **map = alloc_map(nr, nc);
    int i, j;
    while (fscanf(fp, "%d %d", &i, &j) == 2){
        map[i][j] = -1;
    }
    return map;
}

int coloraBFS(int **m, int id, int NR, int NC, int K, int **mark, int start_r, int start_c) {
    int valido = 1;
    cell *queue = malloc(NR*NC*sizeof(cell));
    int **dist = malloc(NR*sizeof(int));
    int dr[4] = {-1, 0, 1, 0};
    int dc[4] = {0, 1, 0, -1};
    int i, j;
    for (i=0; i<NR; i++) {
        dist[i] = malloc(NC*sizeof(int));
        for (j=0; j<NC; j++) dist[i][j] = -1;
    }
    int tail = 0, head = 0;
    cell start = {start_r, start_c};
    dist[start.r][start.c] = 0;
    if (m[start.r][start.c]) valido = 0;
    queue[tail++] = start;

    while (head < tail && valido) {
        cell curr = queue[head++]; //estraggo dalla testa
        if (m[curr.r][curr.c] == -1 || (mark[curr.r][curr.c] != id && mark[curr.r][curr.c] != 0)) { valido=0; break; }
        mark[curr.r][curr.c] = id; //coloro la soluzione corrente

        for (i=0; i<4; i++) {
            cell next = {curr.r+dr[i], curr.c+dc[i]};
            if (next.r>=0 && next.r<NR && next.c>=0 && next.c<NC && m[next.r][next.c]!=-1) {
                if (dist[next.r][next.c] == -1) { //non sono ancora andato in quella casella
                    dist[next.r][next.c] = dist[curr.r][curr.c] + 1;
                    if (dist[next.r][next.c] <= K) {
                        queue[tail++] = next; //aggiungo in coda tutti gli elementi possibilmente raggiungibili entro la distanza K
                    }
                }
            }
        }
    }
}

bool bfs (int **sol, int **map, int sr, int sc, int NR, int NC, int k, int id, int **check, int flag){
    bool valid = true;
    int **dist = malloc(NR*sizeof(int));
    for (int i = 0; i < NR; i++){
        dist[i] = malloc(NC*sizeof(int));
        for (int j = 0; j < NC; j++){
            dist[i][j] = -1;
        }
    }
    int dr[4] = {1, -1, 0, 0};
    int dc[4] = {0, 0, 1, -1};
    int head = 0, tail = 0;
    cell *queue = malloc(NR*NC*sizeof(cell));
    cell start = {sr, sc};
    queue[tail++] = start;
    dist[sr][sc] = 0;

    if (map[sr][sc] == -1) valid = false;
    int i;
    while (head < tail && valid){
        cell curr = queue[head++];
        if (map[curr.r][curr.c] == -1 || sol[curr.r][curr.c] != id) {
            valid = false; break;
        }

        if (flag == 1) check[curr.r][curr.c] = id;

        for (i = 0; i < 4; i++){
            int nr = curr.r + dr[i];
            int nc = curr.c + dc[i];

            if (0 <= nr && nr < NR && 0 <= nc && nc < NC){
                if (dist[nr][nc] == -1){
                    dist[nr][nc] = dist[curr.r][curr.c] + 1;
                    if (dist[nr][nc] <= k && map[nr][nc] != -1){
                        cell next = {nr, nc};
                        queue[tail++] = next;
                    }
                }
            }
        }
    }
    for (i = 0; i < NR; i++){
        free(dist[i]);
    }
    free(dist);
    free(queue);
    return valid;
}

void generasolR(int **m, int NR, int NC, int K, int Z, int pos, int *flag, int **mark, int **sol) {
    //controlla solo se esiste una soluzione valida
    if (*flag == 0) return;
    int i, j;
    if (pos == Z) { //possibile soluzione trovata
        *flag = 0; //se arrivo qua per come ho strutturato la ricorsione con prunign e BFS allora certamente la soluzione è accettabile
        for (i=0; i<NR; i++) {
            for (j=0; j<NC; j++) sol[i][j] = mark[i][j];
        }
        return;
    }
    for (i=0; i<NR; i++) {
        for (j=0; j<NC; j++) {
            if (mark[i][j] == 0 && m[i][j] != -1) { //non è già stato colorato - non è un muro
                int **curr_mark = malloc(NR*sizeof(int));
                int k, l;
                for (k=0; k<NR; k++) curr_mark[k] = calloc(NC, sizeof(int));
                for (k=0; k<NR; k++) {
                    for (l=0; l<NC; l++) curr_mark[k][l] = mark[k][l];
                }
                int valido = coloraBFS(m, pos+1, NR, NC, K, curr_mark, i, j);
                if (valido) generasolR(m, NR, NC, K, Z, pos+1, flag, curr_mark, sol); //ricorro solo se andava bene mettere in quella posizione la risorsa
                for (k=0; k<NR; k++) free(curr_mark[k]);
                free(curr_mark);
                if (*flag == 0) return;
            }
        }
    }
}

void generate_sol_wrap(int Z, int **map, int nr, int nc){
    int k = 0, flag = 0, Z, i, j;
    int **sol = malloc (nr*sizeof (int*)), **best_sol = malloc (nr*sizeof (int*));
    for (i = 0; i < nr; i++){
        sol[i] = malloc (nc*sizeof (int));
        best_sol[i] = malloc (nc*sizeof (int));
    }
    int **mark = malloc (nr*sizeof (int*));
    for (i = 0; i < nr; i++){
        mark[i] = calloc (nc, sizeof (int));
    }

    while (!flag){
        printf ("Dammi il numero di risorse che vuoi mettere nella matrice\n");
        scanf ("%d", &Z);
        generasolR (map, nr, nc, k, Z, 0, &flag, mark, sol);
        if (!flag){
            for (i = 0; i < nr; i++){
                for (j = 0; j < nc; j++){
                    best_sol[i][j] = sol[i][j];
                }
            }
            k++;
        }
    }

    printf ("Soluzione ottima trovata con k: %d\n", k-1);
    for (i = 0; i < nr; i++){
        for (j = 0; j < nc; j++){
            printf (" %d ", best_sol[i][j]);
        }
        printf ("\n");
    }

}   

bool read_proposal(char *filename, int *nr, int *nc, int **map){
    FILE *fp = fopen(filename, "r");
    int i, j;
    int k, Z;
    fscanf(fp, "%d %d", &k, &Z);
    int **sources = malloc(Z*sizeof(int));
    for (int i = 0; i < Z; i++){
        sources[i] = malloc(2*sizeof(int));
        fscanf(fp, "%d %d", &sources[i][0], &sources[i][1]);
    }
    int **sol = alloc_map(*nr, *nc);
    for(i = 0; i < *nr; i++){
        for (j = 0; j < *nc; j++){
            fscanf(fp, "%d",  &sol[i][j]);
        }
    }
    int **check = alloc_map(*nr, *nc);
    
    for (i = 0; i < Z; i++){
        if (!(bfs(sol, map, sources[i][0], sources[i][1], *nr, *nc, k, i+1, check, 1))) return false;
    }
    for (i = 0; i < *nr; i ++){
        for (j = 0; j < *nc; j++){
            if (check[i][j] != sol[i][j]){
                return false;
            }
        }
    }
    return true;
}

int main(int argc, char* argv[]){
    int nr, nc;
    
    int **map = readmap(FILE_MAP, &nr, &nc);
    printf("\n");
    return 0;
}