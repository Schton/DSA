#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node{
    int data;
    struct Node* next;
} Node;

typedef struct Stack{
    Node *top;
}Stack;

Stack* initialize();
bool isFull(Stack* s);
bool isEmpty(Stack* s);
void push(Stack* s, int value);
int pop(Stack* s);
int peek(Stack* s);
void display(Stack* s);

int main(){

    Stack *s = initialize();
    printf("----Stack Menu----\n");
    printf("1. Push an item\n2. Pop an item\n3. Peek an item\n4. Display all items\n5. Exit\n\n");

    int choice;
    do{
        printf("Select choice: ");
        scanf("%d", &choice);
        
        switch(choice){
            case 1:
                int x;
                printf("Input a number: ");
                scanf("%d", &x);
                printf("\n");
                push(s, x);
                break;

            case 2:
                int popRes = pop(s);
                if(popRes != false){
                    printf("Item %d was successfully popped.\n\n", popRes);
                } else{
                    printf("Pop unsuccessful.\n\n");
                }
                break;

            case 3:
                int checkRes = peek(s);
                if(checkRes != false){
                    printf("Peeked at %d.\n\n", checkRes);
                }else{
                    printf("Peek unsuccessful.\n\n");
                }
                break;

            case 4:
                display(s);
                break;

            case 5:
                printf("Exiting...");
                free(s);
                exit(0);
                break;

            default:
                printf("Invalid input!\n");
                break;
        }
    }while(choice != 0);


    return 0;
}

Stack* initialize(){
    // Allocate memory for the stack structure
    // Initialize the stack's top pointer to NULL
    // Return the pointer to the stack
    Stack *temp = malloc(sizeof(Stack));
    temp->top = NULL;
    return temp;
}
bool isFull(Stack* s){
    // Return false (linked list can never be full)
    return false;
}
bool isEmpty(Stack* s){
    // The stack is empty if its top pointer is NULL
    bool ret = false;
    if(s->top == NULL) ret = true;
    return ret;
}
void push(Stack* s, int value){
    // Allocate memory for a new node
    // Set the data of the new node
    // Link the new node to the current top of the stack
    // Update the stack's top pointer to point to the new node

    //create new node
    Node *temp = malloc(sizeof(Node));
    temp->data = value;
    temp->next = NULL;

    //let new node link point to whatever top is pointing
    temp->next = s->top;

    //point top the new node
    s->top = temp;
    if(s->top->data == value) printf("%d was pushed successfully.\n", value);
}
int pop(Stack* s){
    // Check if the stack is empty before attempting to pop
    // Get a temporary pointer to the top node
    // Store the data of the top node
    // Move the top pointer to the next node
    // Free the memory of the old top node using temp
    // Return the stored value
    Node *tempTop = s->top;
    int storedVal = -1;
    if(!isEmpty(s)){
        storedVal = s->top->data;
        s->top = s->top->next;
        free(tempTop);
    }
    return storedVal;
}
int peek(Stack* s){
    // Check if the stack is empty
    // Return the data of the top node
    int ret = -1;
    if(!isEmpty(s)){
        ret = s->top->data;
    }
    return ret;
}
void display(Stack* s){
    // Check if the stack is empty
    // Create a temporary pointer to traverse the list
    // Traverse the linked list and print each element's data
    if(!isEmpty(s)){
        Node *trav = s->top;
        while(trav != NULL){
            printf("%d\t", trav->data);
            trav = trav->next;
        }
        printf("\n\n");
    }
}

