#include <stdio.h>
#include <stdlib.h>


float* Somme(float* T1, float* T2, int size_T1, int size_T2) {

    // Check if the size of the arrays is 0
    if(size_T2<=0 && size_T1<=0) {
        return NULL;
    }
    // If one of the arrays is empty, return the other one
    if (size_T1==0 && size_T2!=0) {
        float* T3 = (float*)malloc(size_T2*sizeof(int));
        for (int i=0; i<size_T2; i++) {
            T3[i] = T2[i];
        }
        return T3;
    }
    if (size_T1!=0 && size_T2==0) {
        float* T3 = (float*)malloc(size_T1*sizeof(int));
        for (int i=0; i<size_T1; i++) {
            T3[i] = T1[i];
        }
        return T3;
    }
    // If both arrays are not empty
    if(size_T1==size_T2) {
        float* T3 = (float*)malloc(size_T1*sizeof(int));
        for(int i=0; i<size_T1; i++) {
            T3[i] = T1[i] + T2[i];
        }
        return T3;
    }
    else {
        if (size_T1>size_T2) {
            float* T3 = (float*)malloc(size_T1*sizeof(int));
            for(int i=0; i<size_T2; i++) {
            T3[i] = T1[i] + T2[i];
        }
            for(int i=size_T2; i<size_T1; i++) {
            T3[i] = T1[i];
            }
            return T3;
        }
        else{
            float* T3 = (float*)malloc(size_T2*sizeof(int));
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
    int size_T1;
    int size_T2;
    do{
        printf("Give a size to the first array T1:\n");
        scanf("%d", &size_T1);
    }while(size_T1<0);
    do{
        printf("Give a size to the second array T2:\n");
        scanf("%d", &size_T2);
    }while(size_T2<0);

    //Remplissage des tableaux
    float* T1 = (float*)malloc(size_T1*sizeof(int));
    float* T2 = (float*)malloc(size_T2*sizeof(int));

    //Insert in T1
    for(int i=0; i<size_T1; i++) {
        printf("Give a value to T1[%d]:\n", i);
        scanf("%f", &T1[i]);
    }
    //Insert in T2
    for(int i=0; i<size_T2; i++) {
        printf("Give a value to T2[%d]:\n", i);
        scanf("%f", &T2[i]);
    }

    // Testing
    float* T3 = Somme(T1, T2, size_T1, size_T2);
    printf("The result is:\n");
    if (T3==NULL) {
       printf("NULL\n");
    }
    else{
        if(size_T1>=size_T2) {
            for(int i=0; i<size_T1; i++) {
            printf("%f\n", T3[i]);
        }
        }else{
            for(int i=0; i<size_T2; i++) {
            printf("%f\n", T3[i]);
            }
        }
    }
    free(T1);
    free(T2);
    free(T3);

   return 0;
}
