#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
  FILE *fpBF, *fpDyn, *fpCheck;
  int n, size = 6, *blocks, result1, result2;
  
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
  if((fpCheck = fopen("./check", "w")) == NULL)
  {
    printf("error occured while opening check file");
    exit(1);
  }

  while(!feof(fpBF))
  {
    fscanf(fpBF, "#%d", &n);
    for(size_t i = 0; i < size; i++)
    {
      fscanf(fpBF, "%d ", blocks + i);
    }
    fscanf(fpBF, "%d", &result1);

    fscanf(fpDyn, "#%d", &n);
    for(size_t i = 0; i < size; i++)
    {
      fscanf(fpDyn, "%d ", blocks + i);
    }
    fscanf(fpDyn, "%d", &result2);

    if (result1 != result2)
    {
      fprintf(fpCheck, "#%d\n", n);
      for(size_t i = 0; i < size; i++)
      {
        fprintf(fpCheck, "%d ", blocks[i]);
      }
      fprintf(fpCheck, "\nBF result = %d\ndyn result = %d\n", result1, result2);
    }
  }
}