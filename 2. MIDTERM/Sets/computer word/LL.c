#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
    int data;
    struct node* next;
} Node;

typedef struct {
    Node *head;
} Set;

// Prototypes
void initialize(Set *set);
Node* createNode(int element);
void insert(Set *set, int element);
void delete(Set *set, int element);
bool find(Set *set, int element);
Set set_union(Set A, Set B);
Set intersection(Set A, Set B);
Set difference(Set A, Set B);
void display(Set set);

int main () {
    Set A, B;
    initialize(&A);
    initialize(&B);

    insert(&A, 10);
    insert(&A, 20);
    insert(&A, 30);

    insert(&B, 10);
    insert(&B, 20);
    insert(&B, 40);

    printf("Set A: ");
    display(A);

    printf("Set B: ");
    display(B);

    Set U = set_union(A, B);
    printf("Union of Sets: ");
    display(U);

    Set I = intersection(A, B);
    printf("Intersection of Sets: ");
    display(I);

    Set D = difference(A, B);
    printf("Difference of Sets: ");
    display(D);

    return 0;
}

void initialize(Set *set){
    set->head = NULL;
}

Node* createNode(int element){
    Node* newNode = malloc(sizeof(Node));
    newNode->data = element;
    newNode->next = NULL;
    return newNode;
}

void insert(Set *set, int element){
    Node* newNode = createNode(element);
    newNode->next = set->head;
    set->head = newNode;
}

void delete(Set *set, int element){
    Node* temp = set->head, *prev = NULL;

    while(temp != NULL && temp->data != element){
        prev = temp;
        temp = temp->next;
    }

    if(temp == NULL) return;

    if(prev == NULL)
        set->head = temp->next;
    else
        prev->next = temp->next;

    free(temp);
}

bool find(Set *set, int element){
    Node* current = set->head;
    while(current != NULL){
        if(current->data == element)
            return true;
        current = current->next;
    }
    return false;
}

Set set_union(Set A, Set B){
    Set result;
    initialize(&result);

    Node *temp = A.head;
    while(temp != NULL){
        insert(&result, temp->data);
        temp = temp->next;
    }

    temp = B.head;
    while(temp != NULL){
        if(!find(&result, temp->data))
            insert(&result, temp->data);
        temp = temp->next;
    }

    return result;
}

Set intersection(Set A, Set B){
    Set result;
    initialize(&result);

    Node* temp = A.head;
    while(temp != NULL){
        if(find(&B, temp->data))
            insert(&result, temp->data);
        temp = temp->next;
    }

    return result;
}

Set difference(Set A, Set B){
    Set result;
    initialize(&result);

    Node* temp = A.head;
    while(temp != NULL){
        if(!find(&B, temp->data))
            insert(&result, temp->data);
        temp = temp->next;
    }

    return result;
}

void display(Set set){