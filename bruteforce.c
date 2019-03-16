#include <stdio.h>
#include <stdlib.h>
#include "queue_qnode.h"
#define MAX_N 6

int ifUsed (int block_number, qnode_t *tower);
void init (int *blocks, queue_t *queue, int n);
void forkNode (qnode_t *tower, int block, queue_t *queue);
void step (int *blocks, int *blocks_sum, int n, int *k, qnode_t *tower, qnode_t **storage, queue_t *queue);
int findresult (qnode_t **storage, int k);


int main (int argc, char **argv)
{
	int n = 6, k = 0, blocks_sum;
	int blocks[6] = {1, 3, 2, 4, 6, 7};
	
	for (int i = 0; i < n; i++) {
		blocks_sum = blocks_sum + blocks[i];
	}

	qnode_t **storage = calloc(10000, sizeof(unsigned long));
	queue_t *queue = createQueue(10000);

	init(blocks, queue, n);

	while (!isEmpty(queue)) {
		step(blocks, &blocks_sum, n, &k, dequeue(queue), storage, queue);
	};
	
	printf("towers in storage:\n");
	for (int i = 0; i < k; i++) {
		for (int j = 0; j < storage[i]->size; j++) {
			printf("%d ", storage[i]->indexes[j]);
		};
		printf("\n");
	}
	printf("maximal height of equal towers = %d\n", findresult(storage, k));



	// printf("queue initialized!\n");

	// for(int i = 0; i < n; i++)
	// {
	// 	printf("%d ", queue->array[i]->indexes[0]);
	// }int findresult (qnode_t **storage, int k)
	// printf("\n");
	

	// while (!isEmpty(queue)) {
	// 	printf("in cycle of dequeue\n");
	// 	printf("queue front = %d; rear = %d; size = %d\n", queue->front, queue->rear, queue->size);
	// 	// int temp = dequeue(queue)->indexes[0];
	// 	qnode_t *temp = dequeue(queue);
	// 	int block_val = temp->indexes[0];
	// 	printf("dequeued valie = %d\n", block_val);

	// }
	
	
	return 0;	
}

void step (int *blocks, int *blocks_sum, int n, int *k, qnode_t *tower, qnode_t **storage, queue_t *queue)
{
	storage[(*k)++] = tower;
	if (tower->sum >= *blocks_sum/2) {
		return ;
	}
	for (int i = 0; i < n; i++) {
		if (!ifUsed(blocks[i], tower)) {
			forkNode(tower, blocks[i], queue);
		};
		
	};
}

int ifUsed (int block, qnode_t *tower)									//takes as arguments block and pointer to node 
{																													//returns 1 if block is not used in tower
	for (int i = 0; i < tower->size; i++) {
		if (tower->indexes[i] == block) return 1;
	};
	return 0;
}

void forkNode (qnode_t *tower, int block, queue_t *queue) {		//creates next node in graph and puts in into queue
	qnode_t *temp = calloc(1, sizeof(qnode_t));
	temp->size = tower->size + 1;
	temp->sum = tower->sum + block;
	temp->indexes = calloc(temp->size, sizeof(int));
	temp->indexes = tower->indexes;
	temp->indexes[temp->size-1] = block;
	enqueue(temp, queue);

	for (int i = 0; i < temp->size; i++) {
			printf("%d ", temp->indexes[i]);
	};
	printf("\n");

}

void init (int *blocks, queue_t *queue, int n) 
{
	for (int i = 0; i < n; i++) {
		qnode_t *temp = calloc(1, sizeof(qnode_t));
		temp->size = 1;
		temp->indexes = calloc(1, sizeof(int));
		*temp->indexes = blocks[i];
		temp->sum = blocks[i];
		enqueue(temp, queue);

		// debugging code
		// for(int j = 0; j < i; j++)
		// {
		// 	printf("%d ", queue->array[j]->indexes[0]);
		// }
		// printf("\n");
		// printf("value %d enqueued\n", temp->indexes[0]);
		// printf("queue front = %d; rear = %d; size = %d\n", queue->front, queue->rear, queue->size);
	};
}

int findresult (qnode_t **storage, int k)
{
	int max_sum = 0;
	for (int i = 0; i < k - 1; i++) {
		if (storage[i]->sum > max_sum) {
			for (int j = i + 1; j < k; j++) {
				if (storage[i]->sum == storage[j]->sum) {
					int if_compatible = 1;
					int size_i = storage[i]->size;
					int size_j = storage[j]->size;
					for (int m = 0; m < size_i; m++) {
						if (!if_compatible) {
							break;
						};						
						for (int n = 0; n < size_j; n++) {
							if (storage[i]->indexes[m] == storage[j]->indexes[n]) {
								if_compatible = 0;
								break;
							};
						};
					};
					if (if_compatible) {
						max_sum = storage[i]->sum;
						break;
					};
				};
			};
		};
	};
	return max_sum;
}