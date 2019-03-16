#include <stdio.h>
#include <stdlib.h>

typedef struct qnode_t                //contains information on each exact combination of blocks (tower)
{
	int *indexes;                       //array containing indexes of blocks, used in tower
	int size;                           //amount of blocks, used in tower
	int sum;                            //sum of blocks, used in tower
} qnode_t;     

typedef struct queue_t                
{
  qnode_t **array;
  int front, rear, size, capacity;    //size is for number of elements currently contained in queue
} queue_t;                            //capacity is for total capacity of queue             


queue_t *createQueue (int capacity);        //takes number of elements as argument
void enqueue (qnode_t *val, queue_t *queue);
qnode_t *dequeue (queue_t *queue);
int isFull (queue_t *queue);            //returns 1 if full 0 if not
int isEmpty (queue_t *queue);           //returns 1 if empty  0 if not/*NEED TO FIX*/
int deletqueue (queue_t *queue);        //returns 0 if deleted properly