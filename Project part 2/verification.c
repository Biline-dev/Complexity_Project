#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>



typedef struct model{
  int * table;
  int size;
  int not_defined_atoms;
}model;

typedef struct literal{
  int name;
  struct literal * next;
}literal;

typedef struct clause{
  literal * literals;
  int number_of_literals;
  struct clause * next;
}clause;

typedef struct formula{
  clause * clauses;
  int number_of_clauses;
}formula;


int str_to_num(char * string)
{
  int number = 0;
  int negative = 1;
  int init_i = 0;
  if(string[0] == '-')
  {
    negative = -1;
    init_i = 1;
  }
  for(int i = init_i; string[i] != '\0' && string[i] != '\n' ;i++)
  {
    number = number * 10 + string[i]-'0';
  }
  return number*negative;
}

//load the model from the files
model input_model(char *s){
  model M;
  FILE *fp;
  char buff[12];
  fp = fopen(s, "r");
  if(!fp)
  {
   printf("file doesnt exist or rights missing\n");
   exit(-2);
  }
  if(fgets(buff, 255, (FILE*)fp))
  {
    M.size = str_to_num(buff);
    M.table = malloc(sizeof(int)*M.size+1);
    int index = 1;
    while(index < M.size+1 && fgets(buff, 255, (FILE*)fp))
    {
      M.table[index] = str_to_num(buff);
      index+=1;
    }
  }
  return M;
}

//load the formula from the file
formula read_formula(char * s)
{
  formula F;
  clause * p_clause;
  literal * l;
  FILE *fp;
 char buff[12];
 fp = fopen(s, "r");
 if(!fp)
 {
   printf("file doesnt exist or rights missing\n");
   exit(-2);
 }
  int index = 0;
 if(fgets(buff, 255, (FILE*)fp))
 {
   F.number_of_clauses = str_to_num(buff);
   F.clauses = NULL;
   while(index < F.number_of_clauses && fgets(buff, 255, (FILE*)fp))
   {
     p_clause = malloc(sizeof(clause));
     p_clause->literals = NULL;
     p_clause->number_of_literals = str_to_num(buff);
     p_clause->next = F.clauses;
     F.clauses = p_clause;
     int jindex = 0;
     while(jindex < p_clause->number_of_literals && fgets(buff, 255, (FILE*)fp))
     {
       l = malloc(sizeof(literal));
       l->name = str_to_num(buff);
       l->next = p_clause->literals;
       p_clause->literals = l;
       jindex++;
     }
     index++;
    }
  }
   return F;
}

void print_clause(clause * p_clause)
{
  clause * pointer = p_clause;
  literal * l = pointer->literals;
  printf("clause is: ");
  while(l != NULL)
  {
    printf("%d,",l->name);

    l = l->next;
  }
  printf("\n");
  return;
}

// remove a close close from the formula
void remove_clause(formula* F, clause* p_clause)
{
  clause * pointer = F->clauses;
  if(pointer == p_clause)
  {
    pointer = pointer->next;
    F->clauses = pointer;
    return ;
  }
  while(pointer->next != NULL)
  {
    if(pointer->next == p_clause)
    {
      pointer->next = p_clause->next;
      return;
    }
    pointer = pointer->next;
  }
}

//Set an atom value in a formula
int set_atom(formula* F,int a, int value)
{
  clause * p_clause = F->clauses;
  literal * l;
  while(p_clause != NULL)
  {
    l = p_clause->literals;
    while(l != NULL)
    {
      if(abs(l->name) == a)
      {
        if((l->name * value) > 0)
        {
          (F->number_of_clauses)--;
          remove_clause(F,p_clause);
          break;
        }else{
          if(p_clause->number_of_literals == 1)
          {
            return -1;
          }
        }
        (p_clause->number_of_literals)--;
      }
      l = l->next;
    }
    p_clause = p_clause->next;
  }
  return 1;
}

//verification algorithme
int verification(formula* F,model M)
{
  int state =1;
  for(int index = 1;index <= M.size && state ==1; index++)
  {
    if(M.table[index] != 0)
    {
      state = set_atom(F,index,M.table[index]);
    }
  }
  if(state == -1 || F->number_of_clauses > 0)
  {
    printf("this model doesnt satisfy the formula\n");
  }else{
    printf("this model satisfies the formuala\n");
  }
}


void print_formula(formula F)
{
  literal * l;
  clause * p_clause ;
  printf("\n\n");
  p_clause = F.clauses;
  printf("number of clauses in the formula = %d\n",F.number_of_clauses);
  while(p_clause != NULL)
  {
    l = p_clause->literals;
    printf("%d clauses are: ",p_clause->number_of_literals);
    while(l != NULL)
    {
      printf("%d,",l->name);
      l = l->next;
    }
    p_clause = p_clause->next;
    printf("\n");
  }
}

void print_model(model M)
{
  printf("model is : \n");
  for(int index = 1;index < M.size+1;index++)
  {
    printf("%d = %d\n",index,M.table[index]);
  }
}

void main()
{
  model M = input_model("model.txt");
  FILE * output = fopen("output.txt","a");

  formula F = read_formula("formula.txt");
  int total_claues = F.number_of_clauses;

  double total_time = 0;
  clock_t begin;
  clock_t end;
  double time_spent;

  begin = clock();
  verification(&F,M);
  end = clock();
  time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  total_time+= time_spent;
  fprintf(output, "%d",total_claues );
  fprintf(output, ",%f\n", total_time );

  return;
}
