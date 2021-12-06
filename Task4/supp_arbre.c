#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include<string.h>


#define BILLION 1000000000.0

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

typedef struct Node Node;
 
/* newNode() allocates a new node
with the given data and NULL left
and right pointers. */
Node* newNode(int data)
{
    // Allocate memory for new node
    Node* lol = (Node*)malloc(sizeof(Node));
 
    // Assign data to this node
    lol->data = data;
 
    // Initialize left and
    // right children as NULL
    lol->left = NULL;
    lol->right = NULL;
    return (lol);
}
Node* createTree(){
    Node *tee = (Node*) malloc(sizeof(Node));
    tee->data = 0;
    tee->right = tee->left = NULL;
    return tee;
}
int isEmpty(Node *node){
    if (node == NULL)
        return 1;
    else return 0;
}
int leaf(Node* node){
    return !(node->left || node->right);
}


Node* insert(Node *tee, int x){
    if(!tee)
        return newNode(x);
    else
        if(x<tee->data)
            tee->left = insert(tee->left, x);
        else    
            tee->right = insert(tee->right, x);
}
void fillTree(Node *tee, char txt[20], int size){
    int data;
    FILE *fp;
    char s[10];
    int i;
    fp = fopen(txt, "r");
    for(i=0; i<size; i++){
        fgets(s, 20, fp);
        //printf("this is it : %s", s);
        data = atoi(s);
        insert(tee, data);
    }
    fclose(fp);
}

void printTree(Node *tee){
    if(!isEmpty(tee)){
        printTree(tee->left);
        printf("%d\n", tee->data);
        printTree(tee->right);
    }
}

Node *search(Node *tee, Node *dad, int x){
    if(!tee)
        return NULL;
    if(x==tee->data)
        return dad;
    else 
        if(x<tee->data)
            return search(tee->left, tee, x);
        else
            return search(tee->right, tee, x);
}

Node *minValue(Node *tee){
    Node *temp = tee;
    while(temp->left != NULL)
        temp = temp->left;
    return temp;
}

Node *deleteNode(Node *tee, int x){
    if(tee==NULL)
        return NULL;

    if (x < tee->data)
        tee->left = deleteNode(tee->left, x);
    else if (x > tee->data)
        tee->right = deleteNode(tee->right, x);

    else{
        if(tee->left==NULL && tee->right==NULL){
            free (tee);
            return NULL;
        }
        else if(tee->left==NULL){
            Node *temp = tee->right;
            free(tee);
            return temp;
        }else if (tee->right == NULL) {
            Node* temp = tee->left;
            free(tee);
            return temp;
        }
        Node *temp = minValue(tee->right);

        tee->data = temp->data;
        tee->right = deleteNode(tee->right, temp->data);
    }
    return tee;
}
//struct timespec start, end;
int main()
{
    FILE *f1, *f2, *f3;
    char s[20];
    double time_spent;
    char step[6];
    struct timespec start, end;
    f1=fopen("resultPire.txt", "r+");
    f2=fopen("result.txt", "r+");
    f3=fopen("resultMeuilleur.txt", "r+");
    fseek(f1, 0, SEEK_END);
    fseek(f2, 0, SEEK_END);
    fseek(f3, 0, SEEK_END);
    
    Node* tee = createTree();
    Node* teePire = createTree();
    fillTree(tee, "rand.txt", 10000);
    fillTree(teePire, "ascend.txt", 10000);
    for(int i=1; i<10000; i=i+5){

    
    
    
    
    //---------------------------------------//
    clock_gettime(CLOCK_REALTIME, &start);
    
    deleteNode(teePire, 10000); 
    //printf("\nDeleted\n");

    clock_gettime(CLOCK_REALTIME, &end);
    time_spent = (end.tv_sec - start.tv_sec) +
                        (end.tv_nsec - start.tv_nsec) / BILLION;
    sprintf(s, "%.10lf", time_spent);
    sprintf(step, "%d", i);
    strcat(step, " ");
    strcat(step, s);
    fputs(step, f1);
    fputs("\n",f1);
    //printf("The elapsed time is %.10lf seconds for the worst case.", time_spent);
    //-------------------------------------------//

    clock_gettime(CLOCK_REALTIME, &start);
    
    deleteNode(tee, 10000);
    //printf("\nDeleted\n");
    
    clock_gettime(CLOCK_REALTIME, &end);
    time_spent = (end.tv_sec - start.tv_sec) +
                        (end.tv_nsec - start.tv_nsec) / BILLION;
    sprintf(s, "%.10lf", time_spent);
    sprintf(step, "%d", i);
    strcat(step, " ");
    strcat(step, s);
    fputs(step, f2);
    fputs("\n",f2);
       //printf("The elapsed time is %.10lf seconds for the random set (regular case)", time_spent);
     //-------------------------------------------//
    tee->left = newNode(-1);

    //printTree(tee);
    clock_gettime(CLOCK_REALTIME, &start);
    
    deleteNode(tee, -1);
    
    //printf("\nDeleted\n");
    
    clock_gettime(CLOCK_REALTIME, &end);
    time_spent = (end.tv_sec - start.tv_sec) +
                        (end.tv_nsec - start.tv_nsec) / BILLION;
    sprintf(s, "%.10lf", time_spent);
    sprintf(step, "%d", i);
    strcat(step, " ");
    strcat(step, s);
    fputs(step, f3);
    fputs("\n",f3);
        //printf("The elapsed time is %.10lf seconds for the best set (best case)", time_spent);

    }
    
    //printf("\nlol : %d\n", tee->left->data);



   


     fclose(f1);
     fclose(f2);
     fclose(f3);



    return 0;
}
