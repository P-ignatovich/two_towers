#include <stdio.h>
#include <string.h>
#include <time.h>
#include "queue_qnode.h"

void init(int *blocks, queue_t *queue, int n);
void step(int *blocks, int maxSum, int n, int *inStorage, qnode_t node, queue_t *queue, qnode_t *storage);
void forkNode(int *blocks, qnode_t node, int blockIndex, queue_t *queue);
int ifUsed(int blockIndex, qnode_t node);
void putInStorage(qnode_t node, qnode_t *storage, int *inStorage);
void printStorage(qnode_t *storage, int inStorage, int *blocks);
int findResult(qnode_t *storage, int k);
