#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv)
{
  FILE *fp;

  if(argc != 4)
  {
    printf("enter quantity of test cases needed, size of each and maximal size of each block as launch arguments\n");
    printf("example: ./test_gen 4 5 6\n");
    exit(1);
  }
  
  int n = atoi(argv[1]);
  int size = atoi(argv[2]);
  int max_block = atoi(argv[3]);

  srand(time(0));
  if((fp = fopen("./testCases", "w+")) == NULL) 
  {
    printf("error occured while creating output file\n");
    exit(1);
  }
  fprintf(fp, "%d\n", n);
  fprintf(fp, "%d\n", size);
  for(size_t i = 0; i < n; i++)
  {
    for(size_t j = 0; j < size; j++)
    {
      fprintf(fp,"%d ", rand() % max_block + 1);
    }
    fprintf(fp, "\n");
  }
  printf("generated %d test cases %d elements each, max element size = %d\n", n, size, max_block);
  fclose(fp);    
}
