#include<stdio.h>
#include <stdlib.h>

#include "quotazione.h"
#include "info_tempo.h"

typedef struct BSTNode_s* link;

typedef struct BSTNode_s {
    quotazione_t quotazione;
    link l;
    link r;
    int N;
}BSTNode_t;

struct BSTWrapper {
    link root;
    link z;
};

quotazione_t ItemSetVoid (){
    quotazione_t quotazione;
    quotazione.data.anno = 0;
    quotazione.data.mese = 0;
    quotazione.data.giorno = 0;
    quotazione.quotazione = 0;
    return quotazione;
}


link BSTNewNode (quotazione_t quotazione, link l, link r, int N){
    link x = malloc (sizeof (BSTNode_t));
    x->l = l;
    x->r = r;
    x->quotazione = quotazione;
    x->N = N;
    return x;

}

BST BSTinit (){
    BST bst = malloc (sizeof (struct BSTWrapper));
    bst->root = (bst->z = BSTNewNode (ItemSetVoid(), NULL, NULL, 0));
    return bst;
}

void BSTFreeR (link h, link z){
    if (h == z){
        return;
    }
    BSTFreeR (h->l, z);
    BSTFreeR (h->r, z);
    free (h);
}
void BSTFree (BST bst){
    BSTFreeR (bst->root, bst->z);
    free (bst);

}

void BSTVisit (link h, link z){
    if (h == z){
        return;
    }
    BSTVisit (h->l, z);
    printf ("Quotazione giornaliera %.2f in data %d/%d/%d\n", h->quotazione.quotazione, h->quotazione.data.giorno, h->quotazione.data.mese, h->quotazione.data.anno);
    BSTVisit (h->r, z);
}
void BSTPrint (BST bst){
    BSTVisit (bst->root, bst->z);

}

void SearchDataR (link h, link z, data_t data_da_cercare){
    int cmp;
    if (h == z){
        printf ("Data non trovata\n");
        return;
    }
    cmp = cmpData (data_da_cercare, h->quotazione.data);
    if (cmp == 0){
        printf ("Quotazione giornaliera nella data selezionata: %.2f\n", h->quotazione.quotazione);
        return;
    }
    if (cmp == -1){
        SearchDataR (h->l, z, data_da_cercare);
        return;
    }
    SearchDataR (h->r, z, data_da_cercare);
    return;
}
void SearchData (BST bst, data_t data_da_cercare){
    SearchDataR (bst->root, bst->z, data_da_cercare);
}

link insertLeafR (link h, link z, quotazione_t val){
    if (h == z){
        return BSTNewNode (val, z, z, 1);
    }
    if (cmpData (val.data, h->quotazione.data) == 1){
        h->r = insertLeafR (h->r, z, val);
    }
    else{
        h->l = insertLeafR (h->l, z, val);
    }
    (h->N)++;
    return h;
}
void InsertInBST (BST bst, quotazione_t val){
    bst->root = insertLeafR (bst->root, bst->z, val);
}

data_t searchMinR (link h, link z){
    if (h == z){
        data_t non_trovato;
        non_trovato.anno = 0; non_trovato.mese = 0; non_trovato.giorno = 0;
        return non_trovato;
    }
    if (h->l == z){
        return h->quotazione.data;
    }
    return searchMinR (h->l, z);
}
data_t searchMaxR (link h, link z){
    if (h == z){
        data_t non_trovato;
        non_trovato.anno = 0; non_trovato.mese = 0; non_trovato.giorno = 0;
        return non_trovato;
    }
    if (h->r == z){
        return h->quotazione.data;
    }
    return searchMaxR (h->r, z);
}

data_t searchMin (BST bst){
    return searchMinR (bst->root, bst->z);
}
data_t searchMax (BST bst){
    return searchMaxR (bst->root, bst->z);
}

void SearchQuotR(link h, link z, data_t data1, data_t data2, float* max, float* min) {
    if (h == z) {
        return;
    }
    
    // Se la data corrente è maggiore di data1, esplora il sottoalbero sinistro
    if (cmpData(h->quotazione.data, data1) > 0) {
        SearchQuotR(h->l, z, data1, data2, max, min);
    }
    
    // Se la data corrente è nell'intervallo [data1, data2]
    
    // Aggiorna min e max
    if (h->quotazione.quotazione > *max) {
        *max = h->quotazione.quotazione;
    }
    if (h->quotazione.quotazione < *min) {
        *min = h->quotazione.quotazione;
    }
    
    
    // Se la data corrente è minore di data2, esplora il sottoalbero destro
    if (cmpData(h->quotazione.data, data2) < 0) {
        SearchQuotR(h->r, z, data1, data2, max, min);
    }
}
void SearchQuot_max_min_date(BST bst, data_t data1, data_t data2) {
    float max = 0, min = __FLT_MAX__;
    
    if (data1.anno != 0 && data2.anno != 0){
        SearchQuotR(bst->root, bst->z, data1, data2, &max, &min);
    }
    
    if (min != __FLT_MAX__){
        printf("La quotazione minima nell'intervallo scelto è: %.2f\n", min);
        printf("La quotazione massima nell'intervallo scelto è: %.2f\n", max);
    }
    else{
        printf("Nessuna quotazione trovata nell'intervallo specificato.\n");
    }
}

int prof_maxR (link h, link z){
    if (h == z){
        return 0;
    }
    int profL = prof_maxR (h->l, z);
    int profR = prof_maxR (h->r, z);

    if (profL > profR){
        return 1 + profL;
    }
    return 1 + profR;
}
int prof_max (BST bst){
    return prof_maxR (bst->root, bst->z);
}

int prof_minR (link h, link z){
    if (h == z){
        return 0;
    }
    if (h->l == z){
        return 1 + prof_minR (h->r, z);
    }
    if (h->r == z){
        return 1 + prof_minR (h->l, z);
    }
    int profL = prof_minR (h->l, z);
    int profR = prof_minR (h->r, z);

    if (profL < profR){
        return 1+ profL;
    }
    return 1+ profR;
}
int prof_min (BST bst){
    return prof_minR (bst->root, bst->z);
}

link rotR(link h){
    link x = h->l;
    h->l = x->r;
    x->r = h;
    x->N = h->N;
    h->N = 1;
    h->N += (h->l) ? h->l->N : 0;
    h->N += (h->r) ? h->r->N : 0;
    return x;
}
link rotL (link h){
    link x = h->r;
    h->r = x->l;
    x->l = h;
    x->N = h->N;
    h->N = 1;
    h->N += (h->l) ? h->l->N : 0;
    h->N += (h->r) ? h->r->N : 0;
    return x;
}

link partR(link h, int r) {
    int t = h->l->N;
    if (t > r) {
        h->l = partR(h->l, r);
        h = rotR(h);
    }
    if (t < r) {
        h->r = partR(h->r, r-t-1);
        h = rotL(h);
    }
    return h;
}

link balanceR(link h, link z) {
    int r;
    if (h == z)
        return z;
    r = (h->N+1)/2-1;
    h = partR(h, r);
    h->l = balanceR(h->l, z);
    h->r = balanceR(h->r, z);
    return h;
}
void BSTbalance(BST bst) {
    bst->root = balanceR(bst->root, bst->z);
}