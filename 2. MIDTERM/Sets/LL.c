#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
    int data;
    struct node* next;
} Node;

typedef struct {
    Node *head;
    int size;
} Set;

void initSet(Set *set);
Node *createNode(int data);
void insertAtVal(Set *set, int data, int pos);
void deleteAtVal(Set *set, int data);
bool isMember(Set *set, int data);
void minVal(Set set);
void maxVal(Set set);
int findVal(Set set, int data);
void destroySet(Set *set);
void display(Set *set);
Set Union(Set A, Set B);
Set Intersection(Set A, Set B);
Set Difference(Set A, Set B);

int main(){
    Set A, B, C;
    initSet(&A);
    initSet(&B);
    initSet(&C);

    insertAtVal(&A, 10, 0);
    insertAtVal(&A, 20, 1);
    insertAtVal(&A, 30, 2);
    insertAtVal(&A, 40, 3);

    insertAtVal(&B, 20, 0);
    insertAtVal(&B, 30, 1);
    insertAtVal(&B, 40, 2);
    insertAtVal(&B, 50, 3);

    printf("Set A: ");
    display(&A);
    printf("Set B: ");
    display(&B);

    printf("Set Union: ");
    C = Union(A, B);
    display(&C);

    printf("Set Intersection: ");
    C = Intersection(A, B);
    display(&C);

    printf("Set Difference: ");
    C = Difference(A, B);
    display(&C);

    minVal(A);
    maxVal(A);
    findVal(A, 20);
    findVal(A, 99);

    destroySet(&A);
    destroySet(&B);
    destroySet(&C);

    return 0;
}

void initSet(Set *set){
    set->head = NULL;
    set->size = 0;
}

Node *createNode(int data){
    Node* newNode = malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void insertAtVal(Set *set, int data, int pos){
    Node *newNode = createNode(data);
    if(pos == 0 || set->head == NULL){
        newNode->next = set->head;
        set->head = newNode;
    } else {
        Node *trav = set->head;
        int index = 0;
        while(trav->next != NULL && index < pos - 1){
            trav = trav->next;
            index++;
        }
        newNode->next = trav->next;
        trav->next = newNode;
    }
    set->size++;
}

void deleteAtVal(Set *set, int data){
    Node* current = set->head, *prev = NULL;
    while(current != NULL && current->data != data){
        prev = current;
        current = current->next;
    }
    if(current == NULL) return;
    if(prev == NULL){
        set->head = current->next;
    } else {
        prev->next = current->next;
    }
    free(current);
    set->size--;
}

bool isMember(Set *set, int data){
    Node *temp = set->head;
    while(temp != NULL){
        if(temp->data == data){
            return true;
        }
        temp = temp->next;
    }
    return false;
}

void minVal(Set set){
    if(set.head == NULL){
        printf("Set is empty.\n");
        return;
    }
    Node* current = set.head;
    int minVal = current->data;
    while(current != NULL){
        if(current->data < minVal){
            minVal = current->data;
        }
        current = current->next;
    }
    printf("Minimum value: %d\n", minVal);
}

void maxVal(Set set){
    if(set.head == NULL){
        printf("Set is empty.\n");
        return;
    }
    Node* current = set.head;
    int maxVal = current->data;
    while(current != NULL){
        if(current->data > maxVal){
            maxVal = current->data;
        }
        current = current->next;
    }
    printf("Maximum value: %d\n", maxVal);
}

int findVal(Set set, int data){
    Node* current = set.head;
    int pos = 0;
    while(current != NULL){
        if(current->data == data){
            printf("%d found at position %d\n", data, pos);
            return pos;
        }
        pos++;
        current = current->next;
    }
    printf("%d not found in set.\n", data);
    return -1;
}

void destroySet(Set* set){
    Node* current = set->head;
    while(current != NULL){
        Node* next = current->next;
        free(current);
        current = next;
    }
    set->head = NULL;
    set->size = 0;
}

void display(Set *set){
    Node* current = set->head;
    while(current != NULL){
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

Set Union(Set A, Set B){
    Set Result;
    initSet(&Result);
    Node *temp = A.head;
    while(temp != NULL){
        insertAtVal(&Result, temp->data, Result.size);
        temp = temp->next;
    }
    temp = B.head;
    while(temp != NULL){
        if(!isMember(&Result, temp->data)){
            insertAtVal(&Result, temp->data, Result.size);
        }
        temp = temp->next;
    }
    return Result;
}

Set Intersection(Set A, Set B){
    Set Result;
    initSet(&Result);
    Node *temp = A.head;
    while(temp != NULL){
        if(isMember(&B, temp->data)){
            insertAtVal(&Result, temp->data, Result.size);
        }
        temp = temp->next;
    }
    return Result;
}

Set Difference(Set A, Set B){
    Set Result;
    initSet(&Result);
    Node *temp = A.head;
    while(temp != NULL){
        if(!isMember(&B, temp->data)){
            insertAtVal(&Result, temp->data, Result.size);
        }
        temp = temp->next;
    }
    return Result;
}