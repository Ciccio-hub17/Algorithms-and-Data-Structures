#include<stdio.h>
#include<stdlib.h>

typedef enum{false, true} bool;

typedef int item;
typedef int key;

typedef struct node node_t, *link;

struct node{
    item val;
    link next;
};

link newNode (link next_node, item val_add);
link insInHead (link head, item val_add);
void insInTail (link *h, link *t, item val_add);
item searchKey (key k, link h);
link DeleteHead (link h);
item extractionHead (link *h);
link Delete_key (link h, key k);
link sortListIns (link h, item val);

int main (){

    link head = NULL;
    item val1 = 5;
    key key1 = 1;
    //creo il primo nodo
    head = insInHead (head, val1);
    //mi salvo un puntatore alla coda
    link tail = head;
    
    insInTail (&head, &tail, val1);

    item Val2 = searchKey (key1, head);

    head = DeleteHead (head);

    printf ("\n");
    return 0;
}

link newNode (link next_node, item val_add){
    link x = malloc (sizeof (node_t));
    if (x == NULL){
        return NULL;
    }
    x->val = val_add;
    x->next = next_node;
    return x;
}

link insInHead (link h, item val_add){
    return newNode (val_add, h);
}

void insInTail (link *h, link *t, item val_add){
    if (*h == NULL){
        *h = newNode (NULL, val_add);
        *t = *h;
    }
    else{
        (*t)->next = newNode (NULL, val_add);
        (*t) = (*t)->next;
    }
}

item searchKey (key k, link h){
    link x;
    for (x = h; x->next != NULL; x = x->next){
        //controllo per verificare che la chiave è presente nella lista
        //return val;
    }
    //return itemestvoid ();
}

link DeleteHead (link h){
    link t = h;
    if (h == NULL){
        return NULL;
    }
    h = h->next;
    free (t);
    return h;
}

item extractionHead (link *h){
    link t = *h;
    if (t == NULL){
        //return Itemsetvoid();
    }
    item val = (*h)->val;
    *h = (*h)->next;
    free (t);
    return val;
}

link Delete_key (link h, key k){
    link prev = NULL, current = h;
    if (current == NULL){
        return NULL;
    }
    for (; current != NULL; prev = current, current = current->next){
        /*if (current->key == k)
            if (x == h){
                h = x->next;
            }
            else{
                p->next = x->next;
                free (x);
                break;
            }*/
    }
    return h;
}

link sortListIns (link h, item val){
    link x, p;
    //voglio ordinare per chiave
    item k = 5;
    //if lista vuota oppure se devo inserirlo in testa{
        //return newNode (h, val);
    //}
    for (x = h, p = x; x != NULL /*&& il nodo voglio inserirlo ordinato, quindi continua mentre la chiave del nodo attuale è maggiore del nodo*/; x = x->next, p = x){
        p->next = newNode (x, val);
    }
    return h;
}