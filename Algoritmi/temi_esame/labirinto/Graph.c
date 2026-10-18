#include <stdio.h>
#include "Graph.h"
#include "ST.h"

struct stanza_s {
    int prof;
    int tesoro;
    int oro;
};

struct graph {
    int S;
    int **madj;
    ST st;
    struct stanza_s *stanze;
};

struct path {
    int *stanze;
    int N_stanze;
    int *visited;
    int ricchezza;
    int ricchezza_max;
    int max_tesoro;
};

Graph GRAPHLoad (FILE *fp){

    int S;
    fscanf (fp, "%d", &S);
    //GRaphinit (S);
    Graph g;

    char *nome;
    for (int i = 0; i < g->S; i++){
        fscanf (fp, "%s %d %d %d", nome, &g->stanze[i].prof, &g->stanze[i].tesoro, &g->stanze[i].oro);
        STinsert (g->st, nome, i);
    }

    char *nome1, *nome2;
    int flag, v, w;
    while (fscanf (fp, "%s %s", nome1, nome2, &flag) == 3){
        v = STsearch (g->st, nome1);
        w = STsearch (g->st, nome2);
        g->madj[v][w] = flag;
        g->madj[w][v] = flag;
    }

    fclose (fp);

    return g;
}

Path GRAPHpathLoad(Graph g, FILE *fp) {
    int n;
    fscanf (fp, "%d", &n);
    Path p; //PathInit (p);
    for (int i = 0; i < p->N_stanze; i++){
        p->stanze[i] = i;
    }

    fclose (fp);

    return p;
}

int calculate (Path p, int ultima_stanza, Graph g){
    if (p->visited[ultima_stanza] == 0){
        p->ricchezza += g->stanze[ultima_stanza].oro;
    }

    if (g->stanze[ultima_stanza].tesoro > p->max_tesoro){
        p->max_tesoro = g->stanze[ultima_stanza].tesoro;
    }

    if (g->stanze[ultima_stanza].prof > 2){
        p->ricchezza = 0;
        return 0;
    }

    p->ricchezza += p->max_tesoro;

    if (g->stanze[ultima_stanza].prof == 0){
        return 1;
    }
    else if (g->stanze[ultima_stanza].prof == 1){
        p->ricchezza *= (2/3);
        return 1;
    }

    p->ricchezza *= (0.5);
    return 1;
    
}

int GRAPHpathCheck(Graph g, Path p, int M, int PF){
    if (g->stanze[p->stanze[0]].prof != 0){
        return 0;
    }

    Path p = GRAPHpathLoad (g, fopen ("proposta.txt", "r"));

    int v, w, i;
    for (i = 0; i < p->N_stanze-1; i++){
        v = p->stanze[i]; w = p->stanze[i+1];
        if (p->visited[w] == 0){
            p->visited[w] = 1;
            p->ricchezza += g->stanze[w].oro;
        }
        if (g->stanze[v].tesoro > p->max_tesoro){
            p->max_tesoro = g->stanze[v].tesoro;
        }
        if (g->madj[v][w] == -1){
            return 0;
        }
        if (g->madj[v][w] == 1){
            PF--;
        }
        M--;
        if (PF <= 0 || M <= 0){
            return calculate (p, i+1, g);
        }
    }

    return calculate (p, i, g);
}

int possible (Graph g, int M, int stanza){
    if (M == 1 && g->stanze[stanza].prof > 2){
        return 0;
    }
    return 1;
}

void insert_backtrack (Graph g, int *M, int *PF, int v, int w, int parametro, Path p){
    if (parametro == 0){
        if (p->visited[w] == 0){
            p->visited[w] = 1;
            if (g->stanze[w].tesoro > p->max_tesoro){
                p->max_tesoro = g->stanze[w].tesoro;
            }
            p->ricchezza += g->stanze[w].oro;
        }
        else{
            p->visited[w]++;
        }
        (*M)--;
        if (g->madj[v][w] == 1){
            (*PF)--;
        }
    }
    else{
        if (p->visited[w] == 1){
            p->visited[w] = 0;
            p->ricchezza -= g->stanze[w].oro;
        }
        else{
            p->visited[w]--;
        }
        (*M)++;
        if (g->madj[v][w] == 1){
            (*PF)++;
        }
    }
}

Path GRAPHpathBestR(Graph g, int *M, int *PF, Path p, int v, int pos){

    if ((*PF) <= 0 || (*M) <= 0){
        int stanza = p->stanze[pos-1];
        int ricchezza;
        if (g->stanze[stanza].prof == 1){
            ricchezza = p->ricchezza + p->max_tesoro * 2/3;
        }
        else if (g->stanze[stanza].prof == 2){
            ricchezza = p->ricchezza + p->max_tesoro * 0.5;
        }
        else if (g->stanze[stanza].prof == 0){
            ricchezza = p->ricchezza + p->max_tesoro;
        }
        else{
            ricchezza = 0;
        }
        if (ricchezza > p->ricchezza_max){
            p->ricchezza_max = ricchezza;
            //copysol (p);
        }
        return p;
    }

    for (int i = 0; i < g->S; i++){
        if (g->madj[v][i] != -1){
            if (possible (g, M, i)){
                p->stanze[pos] = i;

                insert_backtrack (g, M, PF, v, i, 0, p);

                GRAPHpathBestR (g, M, PF, p, i, pos+1);

                insert_backtrack (g, M, PF, v, i, 1, p);
            }
        }
    }
}

Path GRAPHpathBest(Graph g, int M, int PF){
    Path p;

    int i = 0;
    while (g->stanze[i].prof != 0){
        i++;
    }

    p->stanze[0] = i;
    p->visited[i] = 1;
    p->ricchezza += g->stanze[i].oro;
    p->max_tesoro = g->stanze[i].tesoro;

    GRAPHpathBestR (g, &M, &PF, p, i, 1);
    return p;
}