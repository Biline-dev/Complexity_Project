# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#define BILLION 1000000000.0

//déclarer la structure de la liste chainnée 
//déclarer la structure d'un seul élément 
typedef struct Element Element;
struct Element
{
    int nombre;
    Element *suivant;
};

//déclarer la structure d'une liste d'éléments  
typedef struct Liste Liste;
struct Liste
{
    Element *tete;
};


//partie fonctions
//la fonction remplir qui sert à remplir la liste
Liste *remplir(int liste_taille)
{

    Liste *liste = malloc(sizeof(*liste));
    Element *element = malloc(sizeof(*element));
    Element *prd=malloc(sizeof(*element));
    
    //si une erreur produit lors de la création de la liste
    if (liste == NULL || element == NULL)
    {
        exit(EXIT_FAILURE);
    }
    //créer et insérer le premier élément
    element->nombre = 1;
    element->suivant = NULL;
    liste->tete = element;
    prd=liste->tete;
    //insérer le reste des éléments
    int i;
    for(i=2;i<=liste_taille;i++){
    Element *nouveau = malloc(sizeof(*nouveau));
    //si une erreur produit lors de la création d'un élément
    if (nouveau == NULL)
    {
        exit(EXIT_FAILURE);
    }
    
    nouveau->nombre = i;
    nouveau->suivant=prd->suivant;
    prd->suivant=nouveau;
    prd=nouveau;
    }

    return liste;
}

//Afficher la liste chaînée
void afficherListe(Liste *liste)
{
    if (liste == NULL)
    {
        exit(EXIT_FAILURE);
    }
//utiliser un pointeur actuel pour ne pas perdre la tete de la liste et l'utiliser prochainement
    Element *actuel = liste->tete;
    while (actuel != NULL)
    {
        printf("%d -> ", actuel->nombre);
        actuel = actuel->suivant;
    }
    printf("NULL\n");
}

//suppression d'un élément dans une liste triée
Liste *supprimer(int val,Liste *liste){
Element *actuel = liste->tete;
Element *prd=NULL;
Element *temp;

//vérifier si la liste n'est pas vide
if (liste == NULL)
    {
        exit(EXIT_FAILURE);
    }

/* parcourir la liste triée at avancer tant qu'on est pas encore arrivé à la fin de la liste 
et tant que la valeur actuelle est inférieure à la valeur qu'on veut supprimer */
while(actuel!=NULL && actuel->nombre<val){
prd=actuel;
actuel=actuel->suivant;
}

//vérifier si l'élément existe dans la liste 
if( actuel!= NULL && actuel->nombre == val){
//si l'élément à supprimer se trouve en tete de liste, on supprime la tete
if(prd==NULL){
temp=actuel;
liste->tete=liste->tete->suivant;
}
//sinon si l'élément à supprimer est différent du premier élément, on utilise l'élément précédent
else{
temp=prd->suivant;
prd->suivant=temp->suivant;

}
free(temp);
}
return liste;
}


//le programme principal 
int main(){

struct timespec start,end;
int k;
int valeurs_a_supprimer;
int liste_tailles[6]={10,1000,10000,50000,100000,1000000};
//tester sur des listes de différentes tailles
for(k=0;k<6;k++){
   //donner la taille de la liste en paramètre pour la remplir
   Liste *l;
 
   //pire Cas 
    l=remplir(liste_tailles[k]);
    //dans le pire cas , on supprime la dernière valeur du tableau
    valeurs_a_supprimer=liste_tailles[k];
    clock_gettime(CLOCK_REALTIME, &start);
    supprimer(valeurs_a_supprimer,l);
    clock_gettime(CLOCK_REALTIME,&end);
      double time_spent=(end.tv_sec-start.tv_sec)*BILLION+(end.tv_nsec-start.tv_nsec);
      printf("premier pire cas avec la taille %d du tableau = %f nanoSec\n",liste_tailles[k],time_spent);
   //moyen cas
     l=remplir(liste_tailles[k]);
     //dans le moyen cas, on supprime la valeur du milieu
     valeurs_a_supprimer=liste_tailles[k]/2;
     clock_gettime(CLOCK_REALTIME, &start);
    supprimer(valeurs_a_supprimer,l);
    clock_gettime(CLOCK_REALTIME,&end);
      time_spent=(end.tv_sec-start.tv_sec)*BILLION+(end.tv_nsec-start.tv_nsec);
      printf("moyen cas avec la taille %d du tableau = %f nanoSec\n",liste_tailles[k],time_spent);


   //Meilleur Cas 
    l=remplir(liste_tailles[k]);
    //dans le meilleur cas, on supprime la première valeur du tableau qui est égale à 1
     valeurs_a_supprimer=0;
     clock_gettime(CLOCK_REALTIME, &start);
    supprimer(valeurs_a_supprimer,l);
    clock_gettime(CLOCK_REALTIME,&end);
      time_spent=(end.tv_sec-start.tv_sec)*BILLION+(end.tv_nsec-start.tv_nsec);
      printf("meilleur  cas avec la taille %d du tableau = %f nanoSec\n",liste_tailles[k],time_spent);
}
return 0;
}
