#include "queue_qnode.h"

queue_t *createQueue (int capacity)                                    //initializing queue
{
  queue_t *queue = (queue_t*) calloc(1, sizeof(queue_t));              //allocating memory for structure that stores information on queue
  queue->array = (qnode_t*) calloc(capacity, sizeof(qnode_t));         //allocating memory for array for storing information
  queue->front = 0;                                                    //initializing index of front alement as 0
  queue->rear = -1;                                                    //initializing index of rear element as capacity - 1 to get 0 on first enqueue
  queue->size = 0;                                                     //size is for number of elements, currently contained in queue
  queue->capacity = capacity;                                          //capaity
  return queue;
}

void enqueue (qnode_t val, queue_t *queue)
{
  if (isFull(queue)) 
  {
    printf("unable to enqueue element: queue is full\n");
    return;
  }
  if (queue->rear < queue->capacity - 1)
  {
    queue->rear++;
  } else queue->rear = 0;
  queue->array[queue->rear] = val;
  queue->size++; 
} //enqueue

qnode_t dequeue (queue_t *queue)
{
  if (isEmpty(queue)) 
  {
    qnode_t a;
    printf("unable to dequeue element: queue is empty\n");
    return a ;
  }
  if (queue->front < queue->capacity -1) 
  {
    queue->size--;
    return queue->array[queue->front++];
  } else 
  {
    int frontCopy = queue->front;
    queue ->front = 0;
    queue->size--;
    return queue->array[frontCopy];  
  }
} //dequeue

int isFull (queue_t *queue)
{
  if (queue->size == queue->capacity) 
  {
    return 1;
  } else return 0;
} //isFull

int isEmpty (queue_t *queue)
{
  if (queue->size == 0) 
  {
    return 1;
  } else return 0;
} //isEmpty

int deleteQueue (queue_t *queue)
{
  free(queue->array);
  free(queue);
  return 0;
} //deleteQueue