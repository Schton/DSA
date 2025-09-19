#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 10

typedef struct{
    int items[MAX];
    int count;
}List;

typedef struct{
    List list;
    int front;
    int rear;
}Queue;

Queue* initialize();
bool isFull(Queue* q);
bool isEmpty(Queue* q);
void enqueue(Queue* q, int value);
int dequeue(Queue* q);
int front(Queue* q);
void display(Queue* q);

int main(){

    Queue *Q = initialize();

    printf("----Queue Menu----\n");
    printf("1. Queue an item\n2. Dequeue an item\n3. Check front item\n4. Display all items\n5. Exit\n\n");

    int choice;
    do{
        printf("Select choice: ");
        scanf("%d", &choice);
        
        switch(choice){
            case 1:
                int x;
                printf("Input a number: ");
                scanf("%d", &x);
                enqueue(Q, x);
                break;

            case 2:
                int deqRes = dequeue(Q);
                if(deqRes != false){
                    printf("Item %d was successfully dequeued.\n\n", deqRes);
                } else{
                    printf("Dequeue unsuccessful.\n\n");
                }
                break;

            case 3:
                int checkRes = front(Q);
                if(checkRes != false){
                    printf("Checked at %d.\n\n", checkRes);
                }else{
                    printf("Check unsuccessful.\n\n");
                }
                break;

            case 4:
                display(Q);
                break;

            case 5:
                printf("Exiting...");
                free(Q);
                exit(0);
                break;

            default:
                printf("Invalid input!\n");
                break;
        }
    }while(choice != 0);

    return 0;
}

Queue* initialize(){
    // Allocate memory for a Queue structure
    // Initialize the queue's list count to 0
    // Initialize the front and rear pointers to -1 to indicate an empty queue
    // Return the pointer to the queue

    Queue *temp = malloc(sizeof(Queue));
    temp->list.count = 0;
    temp->front = -1;
    temp->rear = -1;

    return temp;

}
bool isFull(Queue* q){
    // count == MAX
    bool ret = false;
    if(q->list.count == MAX) ret = true;
    return ret;
}
bool isEmpty(Queue* q){
    // count == 0
    bool ret = false;
    if(q->list.count == 0) ret = true;
    return ret;
}
void enqueue(Queue* q, int value){
    // Check if the queue is full
    // If the queue is empty, set both front and rear to 0
    // Otherwise, update the rear pointer circularly (rear = (rear + 1) % MAX)
    // Add the new value to the list at the rear position
    // Increment the count
    if(!isFull(q)){
        if(isEmpty(q)){
            q->front = 0;
            q->rear = 0;
        }
        q->rear++;
        q->list.items[q->rear] = value;
        q->list.count++;
    }

}
int dequeue(Queue* q){
    // Check if the queue is empty
    // Store the value found at the front of the queue before it is removed
    // If this is the last element in the queue, reset the queue to its initial empty state
    // If not, update the front pointer circularly (front = (front + 1) % MAX)
    // Decrement the count
    // Return the removed value
    int val = -1;
    if(!isEmpty(q)){
        val = q->list.items[q->front];
        
    }
    return val;
}
int front(Queue* q){
    // Check if the queue is empty
    // Return the value at the front of the queue

}
void display(Queue* q){
    // Check if the queue is empty
    // Loop through the queue from front to rear and print each element

}