#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>



void swap(int tab[], int i, int j)
{
  int tmp = tab[i];
  tab[i] = tab[j];
  tab[j] = tmp;
}

void tamiser_iterative(int *table, int index,int size)
{
  int l_child = index*2+1;
  int r_child = index*2+2;
  int max = index;
  while((l_child < size))
  {
    // printf("left_child %d = %d right child %d = %d\n",l_child,table[l_child],r_child,table[r_child]);
    if(table[max] < table[l_child])
    {
      max = l_child;
    }
    if((r_child < size) && (table[max] < table[r_child]))
    {
      max = r_child;
    }
    if(max == index)
    {
      return;
    }
    // printf("max = %d table[max] = %d\n",max,table[max]);
    swap(table,max,index);
    index = max;
    l_child = index*2+1;
    r_child = index*2+2;
  }
}

void tri_par_Tas_iterative(int * table,int size)
{
  for(int index = (size/2)-1 ; index >= 0 ; index--)
  {
    tamiser_iterative(table,index,size);
  }
  for(int new_size = size-1; new_size > 1 ; new_size--)
  {
      swap(table,new_size,0);
      tamiser_iterative(table,0,new_size);
  }
  swap(table,0,1);
}

int main()
{
  int * table;
  int size = 20;
  table = malloc(size * sizeof(int));
  srand((unsigned)clock());
  for(int i = 0; i < size ; i++)
  {
    table[i] = random()%200;
  }
  tri_par_Tas_iterative(table,size);
  for(int i = 0; i < size ; i++)
  {
    printf("table[%d] = %d\n",i,table[i]);
  }

  return 1;
}
