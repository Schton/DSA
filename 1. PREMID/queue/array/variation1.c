#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 10

typedef struct {
    int items[MAX];
    int count;
} List;

typedef struct {
    List list;
    int front;
    int rear;
} Queue;

//Function Prototypes
Queue* initialize();
bool isFull(Queue* q);
bool isEmpty(Queue* q);
void enqueue(Queue* q, int value);
int dequeue(Queue* q);
int front(Queue* q);
void display(Queue* q);

int main (){

    Queue *q = initialize();
    int num, choice;
    do{
        printf("\nMenu:\n[1]: enqueue\n[2]: dequeue\n[3]: front\n[4]: Display\n[0]: Exit\n");
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
                    printf("front element is %d\n", front(q));
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
    Allocate memory for a Queue structure
    Initialize the queue's list count to 0
    Initialize the front and rear pointers to -1 to indicate an empty queue
    Return the pointer to the queue
    */

    Queue* newQueue = malloc(sizeof(Queue));
    newQueue->list.count = 0;
    newQueue->front = -1;
    newQueue->rear = -1;
    return newQueue;
}

bool isFull(Queue* q){
    // Queue is full if count == MAX
    return (q->list.count == MAX);
}

bool isEmpty(Queue* q){
    // Queue is empty if count == 0
    return(q->list.count == 0);
}

void enqueue(Queue* q, int value){
    /*
    Check if the queue is full
    If the queue is empty, set both front and rear to 0
    Otherwise, update the rear pointer circularly (rear = (rear + 1) % MAX)
    Add the new value to the list at the rear position
    Increment the count
    */

    if(isFull(q)){
        printf("Queue is full.\n");
        return;
    }

    if(isEmpty(q)){
        q->front = 0;
        q->rear = 0;
    } else {
        q->rear = (q->rear + 1) % MAX;
    }
    q->list.items[q->rear] = value;
    q->list.count++;
}

int dequeue(Queue* q){
    /*
    Check if the queue is empty
    Store the value found at the front of the queue before it is removed
    If this is the last element in the queue, reset the queue to its initial empty state
    If not, update the front pointer circularly (front = (front + 1) % MAX)
    Decrement the count
    Return the removed value
    */

    if(isEmpty(q)){
        printf("Queue is empty.\n");
        return -1;
    }

    int value = q->list.items[q->front];
    if(q->list.count == 1){
        q->front = -1;
        q->rear = -1;
        q->list.count = 0;
    } else {
        q->front = (q->front + 1) % MAX;
        q->list.count--;
    }
    return value;
}

int front(Queue* q){
    /*
    Check if the queue is empty
    Return the value at the front of the queue
    */

    if(isEmpty(q)){
        printf("Queue is empty.\n");
        return -1;
    }
    return q->list.items[q->front];
}

void display(Queue* q){
    /*
    Check if the queue is empty
    Loop through the queue from front to rear and print each element
    */

    if(isEmpty(q)){
        printf("Queue is empty.\n");
        return;
    }
    int i;
    printf("items: [");
    for(i = 0; i < q->list.count; i++){
        int index = (q->front + i) % MAX;
        printf("%d", q->list.items[index]);
        if(i < q->list.count - 1){
            printf(", ");
        }
    }
        
    printf("]\n");
    printf("count: %d\n", q->list.count);
    printf("front: %d\n", q->front);
    printf("rear: %d\n", q->rear);
}