#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 10

typedef struct{
    int items[MAX];
    int top;
}Stack;

Stack* initialize();
bool isFull(Stack* s);
bool isEmpty(Stack* s);
void push(Stack* s, int value);
int pop(Stack* s);
int peek(Stack* s);
int top(Stack *s);
void display(Stack* s);

int main(){

    Stack *s = initialize();

    printf("----Stack Menu----\n");
    printf("1. Push an item\n2. Pop an item\n3. Check an item\n4. Check top\n5. Display all items\n6. Exit\n\n");

    int choice;
    do{
        printf("Select choice: ");
        scanf("%d", &choice);
        
        switch(choice){
            case 1:
                int x;
                printf("Input a number: ");
                scanf("%d", &x);
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
                int topRes = top(s);
                printf("Top is %d\n\n", topRes);
                break;

            case 5:
                display(s);
                break;

            case 6:
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
    // Allocate memory for a Stack structure
    // Initialize the top of the stack to -1 to indicate it's empty
    // Return the pointer to the stack

    Stack *temp = malloc(sizeof(Stack));
    temp->top = -1;

    return temp;
}
bool isFull(Stack* s){
    // top == MAX - 1
    bool ret = false;
    if(s->top == MAX - 1) ret = true;

    return ret;
}
bool isEmpty(Stack* s){
    // top == -1
    bool ret = false;
    if(s->top == -1) ret = true;

    return ret;
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
void display(Stack* s){
    // Check if the stack is empty (top == -1)
    // Iterate from the top of the stack down to the bottom (index 0)
    // Print each element
    if(isEmpty(s)){
        printf("The stack is empty.\n\n");
    } else{
        printf("----Items----\n");
        for(int i = 0; i <= s->top; i++){
            printf("%d\t", s->items[i]);
        }
        printf("\n-------------\n");
    }
}
