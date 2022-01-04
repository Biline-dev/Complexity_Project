#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

// todo fix the random in dpll the atom to be tried TRUE or FALSE should be the same
// in my case its random


const int CLAUSE_CHANGE  =1;
const int TRUE =1;
const int FALSE =-1;
const int UNDEFINED =0;
const int ATOM_CHANGE =0;
const int PURE =0;
const int NOT_PURE =-1;


//handle purity undo changes for each clause undone
typedef struct clause_pointer{
  int clause_id;
  struct clause_pointer * next_clause;
}clause_pointer;

typedef struct purity{
  int purity_value;
  clause_pointer * positive_clauses;
  clause_pointer * negative_clauses;
}purity;

typedef struct change{
  int type_of_change;
  int atom;
  int clause_id;
  struct change * next_change;
}change;

typedef struct model{
  int * atoms_table;
  int number_of_atoms;
  int number_of_undefined_atoms;
}model;

typedef struct literal{
  int atom;
  int value;
}literal;

typedef struct clause{
  int clause_id;
  literal * table_literals;
  int number_of_literals;
  int number_of_undefined_literals;
  int value;
}clause;

typedef struct formula{
  clause * table_clauses;
  int number_of_clauses;
  int number_of_undefined_clauses;
  int value;
  int max_atom_name; // the biggest atom name
}formula;


int total_number_of_branches = 0;


void print_clauses_value(formula F)
{
  for(int index = 0;index < F.number_of_clauses; index ++)
  {
    printf("clause %d: %d",F.table_clauses[index].clause_id,F.table_clauses[index].value);
    printf("\n");
  }
}


void print_formula(formula F)
{
  for(int index = 0;index < F.number_of_clauses; index ++)
  {
    printf("clause %d: ",F.table_clauses[index].clause_id);
    for(int jindex = 0; jindex < F.table_clauses[index].number_of_literals; jindex++){
      printf("%d,",F.table_clauses[index].table_literals[jindex].atom);
    }
    printf("\n");
  }
}

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

void output_model(model M)
{
  FILE *output = fopen("model.txt","w");
  fprintf(output, "%d\n",M.number_of_atoms );
  for(int index = 1; index < M.number_of_atoms+1; index++)
  {
    fprintf(output, "%d\n", M.atoms_table[index]);
  }
  fclose(output);
}

formula read_formula(char * s)
{
  formula F;
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
   F.number_of_clauses = str_to_num(buff);
   F.table_clauses = malloc(sizeof(clause)*F.number_of_clauses);
   F.number_of_undefined_clauses = F.number_of_clauses;
   F.value = UNDEFINED;
   F.max_atom_name = 0;
  // printf("number of clauses = %d\n",F.number_of_clauses);
   for(int index = 0; index < F.number_of_clauses && fgets(buff, 255, (FILE*)fp); index++)
   {
     F.table_clauses[index].number_of_literals = str_to_num(buff);
     F.table_clauses[index].table_literals = malloc(sizeof(literal) * F.table_clauses[index].number_of_literals);
     F.table_clauses[index].number_of_undefined_literals = F.table_clauses[index].number_of_literals;
     F.table_clauses[index].value = UNDEFINED;
     F.table_clauses[index].clause_id = index;

     for(int jindex = 0; jindex < F.table_clauses[index].number_of_literals && fgets(buff, 255, (FILE*)fp) ; jindex++)
     {
       F.table_clauses[index].table_literals[jindex].atom = str_to_num(buff);
       F.table_clauses[index].table_literals[jindex].value = UNDEFINED;

       //finding the boundaries for your atoms
       if(F.table_clauses[index].table_literals[jindex].atom > F.max_atom_name)
       {
         F.max_atom_name = F.table_clauses[index].table_literals[jindex].atom;
       }
     }
   }
  }
   return F;
}

// purity init_purity(formula F,int size)
// {
//   purity * purity_table = malloc(sizeof(purity)*(size+1));
//   for(int index = 0;index < size+1;index++)
//   {
//     purity_table[index].purity_value = PURE;
//     purity_table[index].positive_clauses = NULL;
//     purity_table[index].negative_clauses = NULL;
//   }
//   for(int index =0; index < F->number_of_clauses; index++)
//   {
//     for(int jindex = 0; ((jindex < F->table_clauses[index].number_of_literals)); jindex++)// only if the clause if UNDEFINED
//     {
//       clause_pointer * p_clause = malloc(sizeof(clause_pointer));
//       p_clause->clause_id = index;
//       if(F->table_clauses[index].table_literals[jindex].atom > 0)
//       {
//         p_clause->next_clause = purity_table[abs(F->table_clauses[index].table_literals[jindex].atom)].positive_clauses;
//         purity_table[abs(F->table_clauses[index].table_literals[jindex].atom)].positive_clauses = p_clause->next_clause;
//       }
//     }
//   }
// }

model init_model(int size)
{
  model M;
  M.atoms_table = malloc(sizeof(int)*size+1);
  M.number_of_atoms = size;
  M.number_of_undefined_atoms = size;
  for(int index = 0; index < size+1; index++)
  {
    M.atoms_table[index] = 0;
  }
  return M;
}

void print_model(model M)
{
  printf("model: ");
  for(int index = 1; index < M.number_of_atoms+1; index++)
  {
    printf("%d = %d, ",index,M.atoms_table[index]);
  }
  printf("\n");
}


int check_clause_value(clause C)
{
  int clause_is = FALSE;
  for(int index = 0; index < C.number_of_literals; index++)
  {
    if(C.table_literals[index].value == 1)
    {
      clause_is = TRUE;
      return clause_is;
    }
    else if(C.table_literals[index].value == 0)
    {
      clause_is = UNDEFINED;
    }
  }
  return clause_is;
}

int check_formula_value(formula F)
{
  int formula_is = TRUE;
  for(int index = 0; index < F.number_of_clauses; index++)
  {
    //if one clause is FALSE the whole formula is FALSE
    if(F.table_clauses[index].value == -1)
    {
      formula_is = FALSE;
      return formula_is;
    }
    //if one clause is undefined means the formula cant be TRUE but might be FALSE
    else if(F.table_clauses[index].value == 0)
    {
      formula_is = UNDEFINED;
    }
  }
  return formula_is;
}

// generate a random atom that is UNDEFINED and returns it if there are none UNDEFINED atoms it returns -1
int random_atom(model M)
{

  if(M.number_of_undefined_atoms == 0)
  {
    // printf("no more atoms\n");
    // print_model(M);
    return -1;
  }

  srand((unsigned)clock());
  int ran = (random()%M.number_of_atoms)+1;
  int index = 0;
  while(M.atoms_table[ran] != 0)
  {
    index++;
    if(index > (M.number_of_atoms)*2)
    {
      printf("stuck in infinte loop when generating a random atom\n");
      exit(1);
    }
    if(ran+1 > M.number_of_atoms)
    {
      ran = 0;
    }
    ran++;
  }
  return ran;
}

int random_value()
{
  srand((unsigned)clock());
  int ran = (random()%8);
  if(ran < 4)
  {
    return -1;
  }
  else{
    return 1;
  }
}

void push_change(int type_of_change,int name,int value, change **changes)
{
  change * new_change = malloc(sizeof(change));
  new_change->type_of_change = type_of_change;
  if(type_of_change == ATOM_CHANGE)
  {
    // printf("atom change %d = %d\n",name,value);
    new_change->atom = name;
  }
  else{
    // printf("clause change %d = %d\n",name,value);
    new_change->clause_id = name;
  }

  new_change->next_change = (*changes);
  (*changes) = new_change;
}

void undo_atom_change(formula * F,model * M,int atom)
{
  for(int index =0; index < F->number_of_clauses; index++)
  {
      //for each literal in each clause
    for(int jindex = 0; jindex < F->table_clauses[index].number_of_literals; jindex++)
    {
      if((abs(F->table_clauses[index].table_literals[jindex].atom) == atom) &&
    (F->table_clauses[index].table_literals[jindex].value != UNDEFINED))
      {
        F->table_clauses[index].number_of_undefined_literals++;
        //sanity check
        if((F->table_clauses[index].number_of_undefined_literals > F->table_clauses[index].number_of_literals))
        {
          printf("number of undefined literals %d is bigger than number of literals %d\n",F->table_clauses[index].number_of_undefined_literals,F->table_clauses[index].number_of_literals);
          exit(1);
        }
        F->table_clauses[index].table_literals[jindex].value = UNDEFINED;
      }
    }
  }
  M->atoms_table[atom] = UNDEFINED;
  M->number_of_undefined_atoms++;
  // printf("plus: %d\n",M->number_of_undefined_atoms);
}

void undo_clause_change(formula * F, int clause_id)
{
  F->table_clauses[clause_id].value = UNDEFINED;
}

void pop_changes(formula * F,change * changes,model *M)
{
  while(changes != NULL)
  {
    if(changes->type_of_change == ATOM_CHANGE)
    {
      // printf("undo atom %d\n",changes->atom);
      undo_atom_change(F,M,changes->atom);
    }
    else{
      // printf("undo clause %d\n",changes->clause_id);
      undo_clause_change(F,changes->clause_id);
    }
    changes = changes->next_change;
  }
}

void assign_atom_value(formula* F,change ** changes,model *M,int atom,int atom_value)
{
  //for each clause in the formula
  for(int index =0; index < F->number_of_clauses; index++)
  {
    int atom_found = FALSE;
    //for each literal in each clause
    for(int jindex = 0; ((jindex < F->table_clauses[index].number_of_literals) && (F->table_clauses[index].value == UNDEFINED)); jindex++)// only if the clause if UNDEFINED
    {
      //if we find the atom we need to assign a value to
      if(abs(F->table_clauses[index].table_literals[jindex].atom) == atom)
      {
        // and we assign a value to this literal
        int assigned_value = UNDEFINED;
        if( (F->table_clauses[index].table_literals[jindex].atom * atom_value) > 0)
        {
          assigned_value = TRUE;
        }
        else{
          assigned_value = FALSE;
        }
        atom_found = TRUE;
        F->table_clauses[index].table_literals[jindex].value = assigned_value;
        F->table_clauses[index].number_of_undefined_literals--;
        //sanity check
        if(F->table_clauses[index].number_of_undefined_literals < 0)
        {
          printf("number of undefined literals is bigger than number of literals\n");
          exit(1);
        }

      }
    }
    //if the atom was found, we verify if the clauses value changed
    if(atom_found == TRUE)
    {
      int clause_value = check_clause_value(F->table_clauses[index]);
      push_change(CLAUSE_CHANGE,index,clause_value,changes);
      if(clause_value == TRUE)
      {
        F->table_clauses[index].value = TRUE;
      }
      else if(clause_value == FALSE)
      {
        F->table_clauses[index].value = FALSE;
        return; // the one clause if FALSE we return;
      }
    }
  }
}

void print_number_of_unsatisfied_clauses(formula F)
{
  int counter = 0;
  int example_of_a_clause = -1;
  for(int index = 0; index < F.number_of_clauses; index++)
  {
    if((F.table_clauses[index].value == UNDEFINED) || (F.table_clauses[index].value == FALSE))
    {
      counter++;
      example_of_a_clause = index;
    }
  }
  printf("number of FALSE or UNDEFINED clauses: %d, example clause %d\n",counter,example_of_a_clause);
}

// return NON absolute literal name of a unit clause
int check_for_unit_clause(formula F,model M)
{
  for(int index = 0; index < F.number_of_clauses; index++)
  {
    if(F.table_clauses[index].value == UNDEFINED && F.table_clauses[index].number_of_undefined_literals == 1)
    {
      for(int jindex = 0; jindex < F.table_clauses[index].number_of_literals; jindex++)
      {
        if(F.table_clauses[index].table_literals[jindex].value == UNDEFINED && M.atoms_table[abs(F.table_clauses[index].table_literals[jindex].atom)] == UNDEFINED )
        {
          // printf("clause %d value %d, literal %d value %d\n",index,F.table_clauses[index].value,F.table_clauses[index].table_literals[jindex].atom,F.table_clauses[index].table_literals[jindex].value);
          return F.table_clauses[index].table_literals[jindex].atom;
        }
      }
    }
  }
  return 0;
}

int dpll(formula * F,model * M,int atom,int value)
{

  change * changes = NULL;
  int formula_value;
  // printf("atom %d = %d\n",atom,value);
  M->number_of_undefined_atoms--;
  if(M->atoms_table[atom] == 0)
  {
    M->atoms_table[atom] = value;
    push_change(ATOM_CHANGE,atom,value,&changes);
  }
  else{
    printf("trying to assign an already assigned atom\n");
    exit(1);
  }
  assign_atom_value(F,&changes,M,atom,value);
  int unit_clause = check_for_unit_clause(*F,*M); // can be negative carefull
  while(unit_clause != 0)
  {
    if(unit_clause < 0)
    {
      value = -1;
    }
    else{
      value = 1;
    }

    M->number_of_undefined_atoms--;
    if(M->atoms_table[abs(unit_clause)] == 0)
    {
      M->atoms_table[abs(unit_clause)] = value;
      push_change(ATOM_CHANGE,abs(unit_clause),value,&changes);
    }
    else{
      print_model(*M);
      printf("unit clause section: trying to assign an already assigned atom.\n");
      exit(1);
    }
    assign_atom_value(F,&changes,M,abs(unit_clause),value);
    unit_clause = check_for_unit_clause(*F,*M);
    // printf("in model: %d = %d\n",abs(unit_clause),M->atoms_table[abs(unit_clause)]);
  }

  formula_value = check_formula_value(*F);
  if(formula_value == TRUE)
  {
    return TRUE;
  }
  else if(formula_value == FALSE)
  {
    output_model(*M);
    pop_changes(F,changes,M);
    return FALSE;
  }

  int randomed_atom = random_atom(*M);
  if(randomed_atom == -1)
  {
    pop_changes(F,changes,M);
    return FALSE;
  }

  if((dpll(F,M,randomed_atom,-1) == TRUE) || (dpll(F,M,randomed_atom,1) == TRUE))
  {
    return TRUE;
  }else
  {
    pop_changes(F,changes,M);
    return FALSE;
  }
}

void main()
{
  formula F = read_formula("formula.txt");
  model M = init_model(F.max_atom_name);
  // print_formula(F);



  int randomed_atom = random_atom(M);
  double total_time = 0;
  clock_t begin;
  clock_t end;
  double time_spent;

  begin = clock();
  if(((dpll(&F,&M,randomed_atom,-1) == TRUE) || (dpll(&F,&M,randomed_atom,1) == TRUE)))
  {
    printf("the formula has %d clauses and is satisfiable",F.number_of_clauses);
    output_model(M);
  }
  else{
    printf("the formula has %d clauses and is NOT satisfiable",F.number_of_clauses);
  }
  end = clock();
  time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  total_time+= time_spent;
  printf(", execution time = %f\n",time_spent);

  // print_model(M);
  // print_clauses_value(F);

}
