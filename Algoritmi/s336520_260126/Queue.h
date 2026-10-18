#ifndef QUEUE_H
#define QUEUE_H

// Coda di interi (indici dei vertici)
typedef struct queue *Q;

Q Qinit();
int Qempty(Q q);
void Qput(Q q, int id);
int Qget(Q q);
void Qfree(Q q);

#endif