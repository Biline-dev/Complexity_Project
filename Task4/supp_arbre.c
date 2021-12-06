#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

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
void fillTree(Node *tee, char text[20]){
    int data;
    FILE *fp;
    char s[10];
    fp = fopen(s, "r");
    for(int i=0; i<10000; i++){
        fgets(text, 20, fp);
        //printf("this is it : %s", s);
        data = atoi(s);
        insert(tee, data);
    }
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
    Node* tee = createTree();
    Node* teePire = createTree();
    fillTree(tee, "rand.txt");
    fillTree(teePire, "ascend.txt");
    int x = rand();
    
    //
    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);

    deleteNode(teePire, x); printf("\nDeleted\n");
    
    clock_gettime(CLOCK_REALTIME, &end);
    double time_spent = (end.tv_sec - start.tv_sec) +
                        (end.tv_nsec - start.tv_nsec) / BILLION;
    printf("The elapsed time is %lf seconds for the worst case.", time_spent);


    clock_gettime(CLOCK_REALTIME, &start);
    deleteNode(tee, x);
    printf("\nDeleted\n");
    clock_gettime(CLOCK_REALTIME, &end);
    double time_spent = (end.tv_sec - start.tv_sec) +
                        (end.tv_nsec - start.tv_nsec) / BILLION;
        printf("The elapsed time is %lf seconds for the random set (regular case)", time_spent);



    return 0;
}
