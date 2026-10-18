#include <stdlib.h>
#include "Queue.h"

typedef struct qnode *link;
struct qnode { int v; link next; };

struct queue { link head; link tail; };

Q Qinit() {
    Q q = malloc(sizeof(*q));
    q->head = q->tail = NULL;
    return q;
}

int Qempty(Q q) {
    return q->head == NULL;
}

void Qput(Q q, int id) {
    link new_node = malloc(sizeof(*new_node));
    new_node->v = id;
    new_node->next = NULL;
    if (q->tail == NULL) {
        q->head = q->tail = new_node;
    } else {
        q->tail->next = new_node;
        q->tail = new_node;
    }
}

int Qget(Q q) {
    if (q->head == NULL) return -1;
    int v = q->head->v;
    link t = q->head;
    q->head = q->head->next;
    if (q->head == NULL) q->tail = NULL;
    free(t);
    return v;
}

void Qfree(Q q) {
    while(!Qempty(q)) Qget(q);
    free(q);
}