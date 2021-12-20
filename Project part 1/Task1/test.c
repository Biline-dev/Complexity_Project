#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define BILLION 1000000000.0

int* Somme(int* T1, int* T2, int size_T1, int size_T2) {

    // Check if the size of the arrays is 0
    if(size_T2<=0 && size_T1<=0) {
        return NULL;
    }
    // If one of the arrays is empty, return the other one
    if (size_T1==0 && size_T2>0) {
        int* T3 = (int*)malloc(size_T2*sizeof(int));
        for (int i=0; i<size_T2; i++) {
            T3[i] = T2[i];
        }
        return T3;
    }
    if (size_T1>0 && size_T2==0) {
        int* T3 = (int*)malloc(size_T1*sizeof(int));
        for (int i=0; i<size_T1; i++) {
            T3[i] = T1[i];
        }
        return T3;
    }
    // If both arrays are not empty
    if(size_T1==size_T2) {
        int* T3 = (int*)malloc(size_T1*sizeof(int));
        for(int i=0; i<size_T1; i++) {
            T3[i] = T1[i] + T2[i];
        }
        return T3;
    }
    else {
        if (size_T1>size_T2) {
            int* T3 = (int*)malloc(size_T1*sizeof(int));
            for(int i=0; i<size_T2; i++) {
            T3[i] = T1[i] + T2[i];
        }
            for(int i=size_T2; i<size_T1; i++) {
            T3[i] = T1[i];
            }
            return T3;
        }
        else{
            int* T3 = (int*)malloc(size_T2*sizeof(int));
            for(int i=0; i<size_T1; i++) {
            T3[i] = T1[i] + T2[i];
           }
            for(int i=size_T1; i<size_T2; i++) {
            T3[i] = T2[i];
            }
            return T3;
        }      
    }

}


int main() {
    // Test 
    struct timespec start, end;
    int size_T1;
    int size_T2;
    int nombreMystere = 0, nombreEntre = 0;
    const int MAX1 = 100000, MAX2=50, MIN1 = 1, MIN2=0;

    // Generate random numbers
    srand(time(NULL));
    size_T1 = (rand() % (MAX1 - MIN1 + 1)) + MIN1;
    printf("size_T1 = %d\n", size_T1);
    size_T2 = (rand() % (MAX1 - MIN1 + 1)) + MIN1;
    printf("size_T2 = %d\n", size_T2);
    int* T1 = (int*)malloc(size_T1*sizeof(int));
    int* T2 = (int*)malloc(size_T2*sizeof(int));

    //remplissage des tableaux
    for(int i=0; i<size_T1; i++) {
        T1[i] = (rand() % (MAX2 - MIN2 + 1)) + MIN2;
    }
    for(int i=0; i<size_T2; i++) {
        T2[i] = (rand() % (MAX2 - MIN2 + 1)) + MIN2;
    }

    //affichage des tableaux
   /* printf("Tableau 1 : \n{");
    for(int i=0; i<size_T1; i++) {
        printf("%d, ", T1[i]);
    }
    printf("}\n");
    printf("Tableau 2 : \n{");
    for(int i=0; i<size_T2; i++) {
        printf("%d, ", T2[i]);
    }
    printf("}\n");*/
    // Calcul du temps
    // Testing
    clock_gettime(CLOCK_REALTIME, &start);
    int* T3 = Somme(T1,  T2, size_T1, 0);
    clock_gettime(CLOCK_REALTIME, &end);
    double time_spent = (end.tv_sec - start.tv_sec) * BILLION +
    (end.tv_nsec - start.tv_nsec);
    printf("Le temps d'execution en nanoseconde est %f nanoSec", time_spent);
/*
    printf("The result is:\n");
    if (T3==NULL) {
       printf("NULL\n");
    }
    else{
        if(size_T1>=size_T2) {
            for(int i=0; i<size_T1; i++) {
            printf("%d\n", T3[i]);
        }
        }else{
            for(int i=0; i<size_T2; i++) {
            printf("%d\n", T3[i]);
            }
        }
    }*/

    free(T1);
    free(T2);
    free(T3);

   return 0;
}
