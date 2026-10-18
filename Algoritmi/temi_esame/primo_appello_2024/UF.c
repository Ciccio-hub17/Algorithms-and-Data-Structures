#include <stdlib.h>
#include "UF.h"

static int *id, *sz, *stack, sp=0;
static int find(int x);

static void push(int v) {
  stack[sp++] = v;
}
static int pop(void) {
  return stack[--sp];
}
  
void UFinit(int N) {
  int i;
  stack  = malloc(4*N*sizeof(int));
  id  = malloc(N*sizeof(int));
  sz  = malloc(N*sizeof(int));
  for(i=0; i<N; i++) {
    id[i] = i;
    sz[i] = 1;
  }
}

void UFfree() {
  free(stack);
  free(id);
  free(sz);
}


int UFfind(int p, int q) {
  return(find(p) == find(q));
}

static int find(int x) {
  int i = x;
  while (i!= id[i])
    i = id[i];
  return i;
}

void UFunion(int p, int q) {
  int i = find(p), j = find(q);
  if (i == j)
    return;
  if (sz[i] < sz[j]) {
    push(i); push(id[i]);
    id[i] = j;
    push(j); push(sz[j]);
    sz[j] += sz[i];
  }
  else {
    push(j); push(id[j]);
    id[j] = i;
    push(i); push(sz[i]);
    sz[i] += sz[j];
  }
}

void UFbacktrack(void) {
  int i, val;
  val=pop(); i=pop();
  sz[i] = val;
  val=pop(); i=pop();
  id[i] = val;  
}
