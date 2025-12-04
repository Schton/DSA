#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#define SIZE 7


typedef struct node{
    int data;
    struct node *lc;
    struct node *rc;
}Node, *NodePtr;


typedef struct{
    int items[SIZE];
    int top;
}Stack;


typedef NodePtr BST;


void initialize(BST *T);
void inorder(BST T);
void display(BST T);
void push(Stack* s, int value);
int pop(Stack* s);
void initializeTree(BST *T);
void insertTree(BST *T, int data);
bool isFull(Stack* s);
bool isEmpty(Stack* s);
int peek(Stack* s);
int top(Stack *s);
NodePtr createNode(int data);


int main(){


    BST T;


    initializeTree(&T);


    insertTree(&T, 50);
    insertTree(&T, 30);
    insertTree(&T, 20);
    insertTree(&T, 40);
    insertTree(&T, 70);
    insertTree(&T, 60);
    insertTree(&T, 80);


    inorder(T);


    return 0;
}


void initializeTree(BST *T){
    (*T) = NULL;
}


NodePtr createNode(int data){
    NodePtr newNode = malloc(sizeof(Node));
    newNode->data = data;
    newNode->lc = NULL;
    newNode->rc = NULL;
    return newNode;
}


void insertTree(BST *T, int data){
    if(*T == NULL){
        *T = createNode(data);
        return;
    }
    if(data < (*T)->data)
        insertTree(&(*T)->lc, data);
    else if (data > (*T)->data)
        insertTree(&(*T)->rc, data);
}


bool isFull(Stack* s){
    // top == MAX - 1
    bool ret = false;
    if(s->top == SIZE - 1) ret = true;


    return ret;
}
bool isEmpty(Stack* s){
    // top == -1
    bool ret = false;
    if(s->top == -1) ret = true;


    return ret;
}


int peek(Stack* s){
    // Check if the stack is empty (top == -1)
    // Return the value at the top of the stack
    int ret = false;
    if(!isEmpty(s)){
        ret = s->items[s->top];
    }
    return ret;
}
int top(Stack *s){
    // Return the value of top
    return s->top;
}


void inorder(BST T){
    Stack *res;
    Stack *stack;
    NodePtr cur = T;


    while(cur || stack->top != 0){
        while(cur){
            push(stack, cur->data);
            cur = cur->lc;
        }
        push(res, stack->items[stack->top]);
        pop(stack);
        cur = cur->rc;
    }


}


void push(Stack* s, int value){
    // Check if the stack is full
    // Increment the top
    // Place the new value at the current top position
    if(!isFull(s)){
        s->top++;
        s->items[s->top] = value;
        printf("Item %d was pushed into position %d\n\n", value, s->top);
    } else{
        printf("Push was unsuccessful.\n\n");
    }
}
int pop(Stack* s){
    // Check if the stack is empty
    // Get the value at the current top of the stack
    // Decrement the top
    // Return the retrieved value
    int ret = false;
    if(!isEmpty(s)){
        ret = peek(s);
        s->top--;
    }
    return ret;
}


void display(BST T){


}

