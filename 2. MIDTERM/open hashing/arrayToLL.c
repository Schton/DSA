
// Array to Linked List Implementation

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Hash Table Size
#define MAX_SIZE 10

typedef struct Node{
    int data;
    struct Node* next;
} Node, *NodePTR;

typedef NodePTR Dictionary[MAX_SIZE];

void initDictionary(Dictionary Dict);
int hash(int value);
NodePTR createNode(int data);
void insertDictionary(Dictionary Dict, int data);
void deleteData(Dictionary Dict, int data);
bool search(Dictionary Dict, int data);
void display(Dictionary Dict); 

int main (){

    Dictionary Dict;
    initDictionary(Dict);

    insertDictionary(Dict, 10);
    insertDictionary(Dict, 20);
    insertDictionary(Dict, 13);
    insertDictionary(Dict, 15);
    insertDictionary(Dict, 25);
    insertDictionary(Dict, 39);
    insertDictionary(Dict, 5);
    insertDictionary(Dict, 2);
    
    printf("Before Delete:\n");
    display(Dict);

    int find = 25;
    if(search(Dict, find)){
        printf("\n%d found in dictionary at index %d.\n", find, hash(find));
    } else {
        printf("\n%d not found in dictionary.\n", find);
    }

    deleteData(Dict, 25);
    printf("\nAfter Delete:\n");
    display(Dict);

    return 0;
}

void initDictionary(Dictionary Dict){
    for(int i = 0; i < MAX_SIZE; i++){
        Dict[i] = NULL;
    }
}

int hash(int value){
    return value % MAX_SIZE;
}

NodePTR createNode(int data){
    Node* newNode = malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void insertDictionary(Dictionary Dict, int data){
    int index = hash(data);
    Node* newNode = createNode(data);

    if(Dict[index] == NULL){
        Dict[index] = newNode;
    } else {
        NodePTR current = Dict[index];
        while(current->next != NULL){
            current = current->next;
        }
        current->next = newNode;
    }
}

void deleteData(Dictionary Dict, int data){
    int index = hash(data);
    Node* current = Dict[index];
    Node* prev = NULL;

    if(current == NULL){
        printf("Value %d is not found\n", data);
        return;
    }

    while(current != NULL && current->data != data){
        prev = current;
        current = current->next;
    }

    if(prev == NULL){
        Dict[index] = current->next;
    } else {
        prev->next = current->next;
    }

    printf("%d Data deleted successfully\n", data);
}

bool search(Dictionary Dict, int data){
    int index = hash(data);
    Node* current = Dict[index];

    while(current != NULL){
        if(current->data == data){
            return true;
        }
        current = current->next;
    }
    return false;
}

void display(Dictionary Dict){
    printf("Hash Table:\n");
    for(int i = 0; i < MAX_SIZE; i++){
        printf("[%d] = ", i);
        if(Dict[i] == NULL){
            printf("Empty.\n");
        } else {
            Node* current = Dict[i];
            while(current != NULL){
                printf("%d -> ", current->data);
                current = current->next;
            }
            printf("NULL\n");
        }
    }
}