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



void tamiser(int *table, int index,int size)
{
  int max = index;
  int l_child = index*2+1;
  int r_child = index*2+2;
  if((l_child < size))
  {
    if(table[max] < table[l_child])
    {
      max = l_child;
    }
    if((r_child < size) && (table[max] < table[r_child]))
    {
      max = r_child;
    }
  }
  if(index != max)
  {
    swap(table,max,index);
    tamiser(table,max,size);
  }
}

void tri_par_Tas_recursive(int * table,int size)
{
  for(int index = (size/2)-1 ; index >= 0 ; index--)
  {
    tamiser(table,index,size);
  }
  for(int new_size = size-1; new_size > 1 ; new_size--)
  {
      swap(table,new_size,0);
      tamiser(table,0,new_size);
  }
  swap(table,0,1);
}

int main()
{
  int * table;
  int size = 20;
  table = malloc(size * sizeof(int));
  for(int i = 0; i < size ; i++)
  {
    table[i] = random()%200;
  }
  tri_par_Tas_recursive(table,size);
  for(int i = 0; i < size ; i++)
  {
    printf("table[%d] = %d\n",i,table[i]);
  }


  return 1;
}
