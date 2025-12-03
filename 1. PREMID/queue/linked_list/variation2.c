
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct Queue {
    Node* front;
    Node* rear;
} Queue;

// Function Prototypes
Queue* initialize();
bool isFull(Queue* q);
bool isEmpty(Queue* q);
void enqueue(Queue* q, int value);
int dequeue(Queue* q);
int front(Queue* q);
void display(Queue* q);

int main () {

    Queue* q = initialize();
    int num, choice;
    do{
        printf("\nMenu:\n[1]: enqueue\n[2]: dequeue\n[3]: rear\n[4]: Display\n[0]: Exit\n");
        printf("Enter Choice: ");
        scanf("%d", &choice);

        switch (choice){
            case 1:
                printf("Enter a number: ");
                scanf("%d", &num);
                enqueue(q, num);
                break;
            case 2:
                num = dequeue(q);
                if(num != -1){
                    printf("%d dequeued\n", num);
                }
                break;
            case 3:
                if(!isEmpty(q)){
                    printf("front element is %d\n", rear(q));
                } else {
                    printf("Queue is empty.\n");
                }
                break;
            case 4:
                display(q);
                break;
            case 0:
                printf("Exiting...");
                free(q);
                exit(0);
            default:
                printf("Invalid Choice!\n");
        }
    } while(choice != 0);

    return 0;
}

// Functions
Queue* initialize(){
    /*
    Allocate memory for the queue structure
    Initialize both front and rear pointers to NULL
    Return the pointer to the new queue
    */

    Queue* newQueue = malloc(sizeof(Queue));
    newQueue->front = NULL;
    newQueue->rear = NULL;
    return newQueue;
}

bool isFull(Queue* q){
    // Return false linked list is never full
    return false;
}

bool isEmpty(Queue* q){
    // Return false if rear is NULL
    return (q->rear == NULL);
}

void enqueue(Queue* q, int value){
    /*
    Allocate memory for a new node
    Set the data of the new node and set its next pointer to NULL
    Check if the queue is currently empty
    If the queue is empty, the new node is both the front and the rear
    If the queue is not empty, link the current front to the new node
    Then, update the front pointer to the new node
    */
   
    Node* newNode = malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = NULL;

    if(isEmpty(q)){
        q->front = newNode;
        q->rear = newNode;
    } else {
        q->front->next = newNode;
        q->front = newNode;
    }
}

int dequeue(Queue* q){
    /*
    Check if the queue is empty before attempting to dequeue
    Store a temporary pointer to the rear node
    Store the data of the rear node
    Move the rear pointer to the next node
    If the queue becomes empty after this operation, update the front pointer to NULL
    Free the memory of the old rear node
    Return the stored value
    */

    if(isEmpty(q)){
        printf("Queue is empty.\n");
        return -1;
    }

    Node* temp = q->rear;
    int value = temp->data;
    q->rear = temp->next;
    if(isEmpty(q)){
        q->front = NULL;
    }
    free(temp);
    return value;
}

int rear(Queue* q){
    /*
    Check if the queue is empty
    Otherwise, return the data of the rear node
    */

    if(isEmpty(q)){
        printf("Queue is empty.\n");
        return -1;
    }
    return q->rear->data;
}

void display(Queue* q){
    /*
    Check if the queue is empty
    Create a temporary pointer to traverse the queue
    Loop through the list until the end (NULL) is reached
    */

    if(isEmpty(q)){
        printf("Queue is empty.\n");
        return;
    }
    Node* temp = q->rear;
    printf("rear -> ");
    for(int i = 0; temp != NULL; i++){
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}