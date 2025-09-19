#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 10

typedef struct{
    int items[MAX];
    int front;
    int rear;
}Queue;

Queue* initialize();
bool isEmpty(Queue* q);
bool isFull(Queue* q);
void enqueue(Queue* q, int value);
int dequeue(Queue* q);
int front(Queue* q);
void display(Queue* q);

int main(){

    Queue *Q = initialize();

    return 0;
}

Queue* initialize(){
    // Allocate memory for the Queue structure
    // Initialize front to 1 and rear to 0



}
bool isEmpty(Queue* q){
    // front == (rear + 1) % MAX

}
bool isFull(Queue* q){
    // front == (rear + 2) % MAX
}
void enqueue(Queue* q, int value){
    // Check if the queue is full
    // Increment the rear pointer circularly (rear = (rear + 1) % MAX)
    // Insert the new element at the new rear position

}
int dequeue(Queue* q){
    // Check if the queue is empty
    // Get the element at the front of the queue
    // Increment the front pointer circularly (front = (front + 1) % MAX)
    // Return the dequeued element

}
int front(Queue* q){
    // Check if the queue is empty
    // Return the element at the current front position

}
void display(Queue* q){
    // Check if the queue is empty
    // Loop through the queue from front to rear and print each element

}


