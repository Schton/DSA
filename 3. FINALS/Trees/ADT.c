#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int data;
    struct node* lc;
    struct node* rc;
}Node, *BST;

void insert(BST* T, int x){
    BST* trav = T;
    
    //traverse to place to insert
    while(*trav != NULL && (*trav)->data != x){
        if(x < (*trav)->data) trav = &(*trav)->lc;
        else trav = &(*trav)->rc;
    }
    
    if(*trav != NULL) return;
    
    //insert 
    struct node* temp = malloc(sizeof(Node));
    temp->data = x;
    temp->rc = NULL;
    temp->lc = NULL;
    *trav = temp;
}
// if its a leaf, dealloc
// if its a parent node, if parent is left child of its parent replace with it with its right child. If parent is a right child of its parent replace with it left child.
// if its a root node, either replace it with its right or left most leaf
void deleteNode(BST* T, int x){
    BST* trav = T;
    
    if((*T)->data == x){
        //if no right subtree, replace with leftmost
        if((*trav)->rc == NULL){
            //traverse to left most
            trav = &(*trav)->lc;
            while((*trav)->lc != NULL){
                trav = &(*trav)->rc;
            }
            //replace root with left most
            (*T)->data = (*trav)->data;
            //delete leftmost
            *trav = NULL;
        } 
        else{
          trav = &(*trav)->rc;
            while((*trav)->rc != NULL){
                trav = &(*trav)->lc;
            }
            (*T)->data = (*trav)->data;
            *trav = NULL;
        }
        return;
    }
    
    while(*trav != NULL && (*trav)->data != x){
        if(x < (*trav)->data) trav = &(*trav)->lc;
        else trav = &(*trav)->rc;
    }
    //if leaf
    if((*trav)->rc == NULL && (*trav)->lc == NULL) *trav = NULL;
    //if parent
    else if((*trav)->lc != NULL || (*trav)->rc != NULL){
        if((*trav)->rc == NULL){
            (*trav)->data = (*trav)->lc->data;
            (*trav)->lc = NULL;
        }
        else{
            (*trav)->data = (*trav)->rc->data;
            (*trav)->rc = NULL;
        }
    }
    
}

void inorder(BST B){
    if(B != NULL){
        inorder(B->lc);
        inorder(B->rc);
    }
}

void printTree(Node* root, int space, char* type, int parent) {
    // Base case
    if (root == NULL) return;

    // Increase distance between levels
    int DISTANCE = 10;
    space += DISTANCE;

    // Process RIGHT child first (so it appears at the top)
    // We pass root->data as the 'parent' for the next call
    printTree(root->rc, space, "Right", root->data);

    // Print current node
    printf("\n");
    
    // Loop to print spaces for indentation
    for (int i = DISTANCE; i < space; i++)
        printf(" ");

    // Formatting the output string based on relationship
    if (parent == -1) {
        // This is the Root
        printf("-[%d] (ROOT)\n", root->data);
    } else {
        // This is a child (Left or Right) showing its Parent
        printf("-[%d] (%s of %d)\n", root->data, type, parent);
    }

    // Process LEFT child
    printTree(root->lc, space, "Left", root->data);
}

// Wrapper to simplify the call in main
void printTreeWrapper(Node* root) {
    // Pass -1 to indicate no parent for the root
    printTree(root, 0, "Root", -1);

    printf("____________________________________");
}

int main() {
    // Write C code here
    BST T = NULL;
    
    insert(&T, 10);
    // insert(&T, 20);
    insert(&T, 5);
    insert(&T, 7);
    insert(&T, 3);
    
    // inorder(T);
    printTreeWrapper(T);
    
    deleteNode(&T, 10);
    printf("\n");
    printTreeWrapper(T);
    // inorder(T);

    return 0;
}
