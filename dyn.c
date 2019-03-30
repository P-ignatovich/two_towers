#include <stdio.h>
#include <stdlib.h>

int solve(int *blocks, int n);
void checkSolution ();

int main(int argc, char **argv)
{
  FILE *fpIn, *fpOut;
  int n, size;

  if((fpIn = fopen("./testCases", "r")) == NULL)                
  {
    printf("error occured while opening testCase file\n");
    exit(1);
  }
  if((fpOut = fopen("./dynOut", "w+")) == NULL)
  {
    printf("error occured while creating output file\n");
    exit(1);
  }
  fscanf(fpIn, "%d\n", &n);
  printf("%d testcases\n", n);
  fscanf(fpIn, "%d\n", &size);
  printf("%d elements each\n", size);
  
  int *blocks = malloc(size * sizeof(int));
  
  for(size_t i = 0; i < n; i++)
  {
    for(size_t j = 0; j < size; j++)
    {
      fscanf(fpIn, "%d ", blocks + j);
    }
    fprintf(fpOut, "#%ld\n", i + 1);
    for(size_t j = 0; j < size; j++)
    {
      fprintf(fpOut, "%d ", blocks[j]);
    }
    fprintf(fpOut, "\n");

    fprintf(fpOut, "%d\n", solve(blocks, size));
  }
  fclose(fpIn);
  fclose(fpOut);
}

int solve(int *blocks, int n)
{
  int maxSum = 0;
  int hMax;                                                         //height of new higher tower
  int delta;                                                        //delta for new set of towers

  for(size_t i = 0; i < n; i++)                                     //calculating maximal possible height of towers
  {
    maxSum = maxSum + blocks[i];
  }
  maxSum = maxSum / 2;

  int A[n][maxSum + 1];                                             //initializing array

  for(size_t i = 0; i < n; i++)
  {
    for(size_t j = 0; j <=maxSum; j++)
    {
      A[i][j] = -1;
    }
  }
  A[0][0] = 0;
  A[0][blocks[0]] = blocks[0];                                      //

  for(size_t i = 1; i < n; i++)                                     //initialising cycle of calculation
  {
    for(size_t j = 0; j <= maxSum; j++)                             //copying previous row to current
    {
      A[i][j] = A[i - 1][j];
    }                                                               //

    for(size_t j = 0; j < maxSum; j++)
    {
      if(A[i-1][j] != -1)                                           //checking if tower with current delta exists
      {
        if(A[i-1][j] + blocks[i] <= maxSum)                         //adding current block to bigger tower
        {
          hMax = A[i-1][j] + blocks[i];                             //clculating hMax and delta for current set
          delta = blocks[i] + j;
          if(A[i][delta] < hMax)                                    //checking if new set for delta will be better than existing one
          {
            A[i][delta] = hMax;
          }
        }                                                           //
        if(A[i-1][j] - j + blocks[i] <= maxSum)                     //adding current block to lesser tower
        {
          if(blocks[i] <= j)                                        //checking if addition will cause lesser tower to become bigger
          {                                                         //if lesser tower is still lesser
            hMax = A[i - 1][j];
            delta = j - blocks[i];
          }else                                                     //if lesser tower became bigger
          {
            hMax = A[i - 1][j] - j + blocks[i];                     //clculating hMax and delta for current set
            delta = blocks[i] - j;
          }
          if(A[i][delta] < hMax)                                    //checking if new set for delta will be better than existing one
          {
            A[i][delta] = hMax;
          }
        }
      }
    }
  }
  return A[n-1][0];
} //solve

void checkSolution ()
{
  FILE *fpBF, *fpDyn, *fpCheck;

  if((fpBF = fopen("./BFout", "r")) == NULL)                
  {
    printf("error occured while opening bruteforce solution file\n");
    exit(1);
  }
  if((fpDyn = fopen("./dynOut", "r")) == NULL)
  {
    printf("error occured while creating out file\n");
    exit(1);
  }
  if((fpCheck = fopen("./check", "w+")) == NULL)
  {
    printf("error occured while opening check file");
    exit(1);
  }


} //checkSolution