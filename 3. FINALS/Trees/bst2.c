#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node* leftChild;
    struct Node* rightChild;
} Node, *BST;

void insert(BST* T, int value){
    BST* trav = T;
    
    while(*trav != NULL && (*trav)->data != value){
            if((*trav)->data > value){
                trav = &(*trav)->leftChild;  
            } else {
                trav = &(*trav)->rightChild;
            }
        }
    
    if(*trav == NULL){
        *trav = (BST)calloc(1, sizeof(Node));
        (*trav)->data = value;
    }
}

void deleteLeaf(BST* T, int value){
    BST* trav = T;
    
    while(trav != NULL && (*trav)->data != value){
        if((*trav)->data > value){
            trav = &(*trav)->leftChild;  
        } else {
            trav = &(*trav)->rightChild;
        }
    }
    
    if(*trav == NULL) return;
    
    if((*trav)->leftChild == NULL && (*trav)->rightChild == NULL){
        free(*trav);
        *trav = NULL;
    }
}


void display(BST T){
    if(T != NULL){
        printf("Node: %d ", T->data);
        
        if (T->leftChild)
            printf("Left = %d, ", T->leftChild->data);
        else
            printf("Left = 0, ");

        if (T->rightChild)
            printf("Right = %d\n", T->rightChild->data);
        else
            printf("Right = 0\n");
            
        display(T->leftChild);
        display(T->rightChild);
    }
}

int main() {
    BST T = NULL;

    insert(&T, 50);
    insert(&T, 20);
    insert(&T, 80);
    insert(&T, 10);
    insert(&T, 30);
    deleteLeaf(&T, 30);
    
    display(T);
}