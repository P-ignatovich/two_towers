#include <stdio.h>
#include <string.h>
#include <time.h>
#include "queue_qnode.h"

void init(int *blocks, queue_t *queue, int n);
void step(int *blocks, int maxSum, int n, int *inStorage, qnode_t node, queue_t *queue, qnode_t *storage);
void forkNode(int *blocks, qnode_t node, int blockIndex, queue_t *queue);
void deleteNode(qnode_t node);
int ifUsed(int blockIndex, qnode_t node);
void putInStorage(qnode_t node, qnode_t *storage, int *inStorage);
void printStorage(qnode_t *storage, int inStorage, int *blocks);
int findResult(qnode_t *storage, int k);

int main(int argc, char **argv)
{
  FILE *fpIn, *fpOut;
  int n, size, inStorage, maxSum;
	int *blocks;
  time_t start, end;
  struct tm *local;  

  if((fpIn = fopen("./testCases", "r")) == NULL) 
  {
    printf("error occured while opening testCase file\n");
    exit(1);
  }
  if((fpOut = fopen("./out", "w+")) == NULL)
  {
    printf("error occured while creating out file\n");
    exit(1);
  }
  fscanf(fpIn, "%d\n", &n);
  printf("%d testcases\n", n);
  fscanf(fpIn, "%d\n", &size);
  printf("%d elements each\n", size);

  qnode_t *storage = calloc(1000000, sizeof(qnode_t));
  queue_t *queue = createQueue(1000000);
  blocks = malloc(size * sizeof(int));
  
  
  for(size_t i = 0; i < n; i++)
  {
    inStorage = 0;
    maxSum = 0;
    for(size_t j = 0; j < size; j++)
    {
      fscanf(fpIn, "%d ", blocks + j);
    }
    fprintf(fpOut, "Testcase # %ld\n", i + 1);
    for(size_t j = 0; j < size; j++)
    {
      fprintf(fpOut, "%d ", blocks[j]);
    }
    fprintf(fpOut, "\n");

    for(size_t j = 0; j < size; j++) 
    {
      maxSum = maxSum + blocks[j];
    }
    maxSum = maxSum / 2;

    init(blocks, queue, size);
    while(!isEmpty(queue))
    {
      step(blocks, maxSum, size, &inStorage, dequeue(queue), queue, storage);
    }
    time(&start);
    local = localtime(&start);
    printf("%d:%d:%d - calculation started for %d nodes\n", local->tm_hour, local->tm_min, local->tm_sec, inStorage);
    fprintf(fpOut, "maximal height of tower = %d\n", findResult(storage, inStorage));
    time(&end);
    local = localtime(&end);
    printf("%d nodes calculated for %ld seconds\n", inStorage, end - start);
  }
  fclose(fpIn);
  fclose(fpOut);
}


void init(int *blocks, queue_t *queue, int n) 
{
	for(size_t i = 0; i < n; i++) 
  {
		qnode_t temp;
		temp.size = 1;
		temp.indexes = calloc(1, sizeof(int));
		*temp.indexes = i;
		temp.sum = blocks[i];
		enqueue(temp, queue);
	};
} //init

void step(int *blocks, int maxSum, int n, int *inStorage, qnode_t node, queue_t *queue, qnode_t *storage)
{
  putInStorage(node, storage, inStorage);
  for(size_t i = 0; i < n; i++)
  {
    if(node.sum + blocks[i] <= maxSum) 
    {
      if(!ifUsed(i, node)) 
      {
        forkNode(blocks, node, i, queue);
      }
    }
  }  
} //step

void deleteNode(qnode_t node) {
	free(node.indexes);
} //deleteNode

int ifUsed(int blockIndex, qnode_t node) 
{
  for(size_t i = 0; i < node.size; i++)
  {
    if(node.indexes[i] == blockIndex) 
    {
      return 1;
    }   
  }
  return 0;
} //ifUsed

void forkNode(int *blocks, qnode_t node, int blockIndex, queue_t *queue)
{
  qnode_t temp;
  temp.size = node.size + 1;
  temp.sum = node.sum + blocks[blockIndex];
  temp.indexes = calloc(temp.size, sizeof(int));
  memcpy(temp.indexes, node.indexes, node.size * sizeof(int));
  temp.indexes[temp.size - 1] = blockIndex;
  enqueue(temp, queue);  
  
  // for(int i = 0; i < temp.size; i++) 
  // {
	// 	printf("%5d", blocks[temp.indexes[i]]);
	// };
	// printf("\n");
} //forkNode

void putInStorage(qnode_t node, qnode_t *storage, int *inStorage)
{
  storage[(*inStorage)++] = node;
} //putInStorage

void printStorage(qnode_t *storage, int inStorage, int *blocks)
{
  printf("towers in storage:\n");
	for(size_t i = 0; i < inStorage; i++) 
  {
		for(size_t j = 0; j < storage[i].size; j++) 
    {
			printf("%d ", storage[i].indexes[j]);
		};
		printf("\n");
  }
} //printStorage

int findResult (qnode_t *storage, int k)
{
	int maxSum = 0;
	for(int i = k - 2; i >= 0; i--) 
  {
		if(storage[i].sum > maxSum) 
    {
			for(int j = k-1; j > i; j--) 
      {
				if(storage[i].sum == storage[j].sum) 
        {
					int if_compatible = 1;
					int size_i = storage[i].size;
					int size_j = storage[j].size;
					for(int m = 0; m < size_i; m++) 
          {
						if(!if_compatible) 
            {
							break;
						};						
						for(int n = 0; n < size_j; n++) 
            {
							if(storage[i].indexes[m] == storage[j].indexes[n]) 
              {
								if_compatible = 0;
								break;
							};
						};
					};
					if(if_compatible) 
          {
						maxSum = storage[i].sum;
						break;
					};
				};
			};
		};
	};

	return maxSum;
} //findResult
