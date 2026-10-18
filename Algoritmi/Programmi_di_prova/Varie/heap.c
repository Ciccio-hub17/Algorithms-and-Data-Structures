#include<stdio.h>
#include<stdlib.h>

#define MAX_N 100

typedef int Item;
typedef struct heap *Heap;
typedef struct pqueue *PQ;

typedef struct heap {
    Item *A;
    int heapsize;
}heap_t;

typedef struct pqueue {
    Item *A;
    int heapsize;
} pq_t;

int LEFT (int i) { return ((i*2)+1); }
int RIGHT (int i) { return ((i*2)+2); }
int FATHER (int i) { return ((i-1)/2); }

Heap heap_init (){
    Heap h;
    h = malloc (sizeof (heap_t));
    h->A = malloc (MAX_N*sizeof (Item));
    h->heapsize = 0;
    return h;
}

void heap_free (Heap h){
    free (h->A);
    free (h);
    return ;
}

void heap_fill (Item val, Heap h){
    int index;
    index = h->heapsize++;
    h->A[index] = val;
    return;
}

void swap (int index1, int index2,Heap h){
    int temp;
    temp = h->A[index1];
    h->A[index1] = h->A[index2];
    h->A[index2] = temp;
    return;
}

void heapify (Heap h, int i){
    int l, r, largest = i;
    l = LEFT (i);
    r = RIGHT (i);

    if (l < h->heapsize && h->A[l] > h->A[i]){
        largest = l;
    }

    if (r < h->heapsize && h->A[r] > h->A[i]){
        largest = r;
    }

    if (largest != i){
        swap (i, largest, h);
        heapify (h, largest);
    }
    return;
}

void heap_build (Heap h){
    int index;
    for (index = h->heapsize/2-1; index >= 0; index--){
        heapify (h, index);
    }
}

void heap_sort (Heap h){
    int i, old_size;
    heap_build (h);
    old_size = h->heapsize;
    for (i = h->heapsize-1; i >= 0; i--){
        swap (i, 0, h);
        h->heapsize--;
        heapify (h, 0);
    }
    h->heapsize = old_size;
    return;
}

void pq_insert (PQ pq, Item val){
    int i;
    i = pq->heapsize++;
    while (i>= 1 && val > pq->A[FATHER(i)]){
        pq->A[i] = pq->A[FATHER(i)];
        i = FATHER (i);
    }
    pq->A[i] = val;
    return;
}

int main(int argc, char* argv[]){
    
    printf("\n");
    return 0;
}