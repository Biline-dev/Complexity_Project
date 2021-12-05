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

int findLeaf(int * table,int size)
{
  int index = 0;
  int l_child = index*2+1;
  int r_child = index*2+2;

  while(l_child < size)
  {
    if((r_child < size) && (table[r_child] > table[l_child]))
    {
      index = r_child;
    }
    else
    {
      index = l_child;
    }
    l_child = index*2+1;
    r_child = index*2+2;
  }

  return index;
}

int compareup(int *table, int size, int index)
{
  while(table[index] < table[size])
  {
    index = (index-1)/2;
  }
  return index;
}

void shiftup(int * table, int index)
{
  if(index < 3)
  {
    table[0] = table[index];
    return;
  }
  else{
    int parent = (index-1)/2;
    shiftup(table,parent);
    table[parent] = table[index];
    return;
  }
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

void Tri_par_Tas_avec_buttomup_recursive(int * table,int size)
{
  int leaf_index;
  int tmp;
  for(int index = (size/2)-1 ; index >= 0 ; index--)
  {
    tamiser(table,index,size);
  }
  for(int new_size = size-1; new_size > 1 ; new_size--)
  {
      tmp = table[0];
      leaf_index = findLeaf(table,new_size);
      leaf_index = compareup(table,new_size,leaf_index);
      shiftup(table,leaf_index);
      table[leaf_index] = table[new_size];
      table[new_size] = tmp;
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
    table[i] = random()%(size*10);
  }
  Tri_par_Tas_avec_buttomup_recursive(table,size);
  for(int i = 0; i < size ; i++)
  {
    printf("table[%d] = %d\n",i,table[i]);
  }

  return 1;
}
