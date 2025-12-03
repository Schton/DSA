
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    int data;
    struct node *next;
} Node;

typedef struct {
    Node *head;
    int count;
} List;

// Variation 1
List initialize();
List empty(List list);
List insertFirst(List list, int data);
List insertLast(List list, int data);
List insertPos(List list, int data, int index);
List deleteFirst(List list);
List deleteLast(List list);
List deletePos(List list, int index);
int retrieve(List list, int index);
int locate(List list, int data);
void display(List list);

int main (){

    List L = initialize();
    L = insertFirst(L, 10);
    

    return 0;
}

List initialize(){
    List *newList;
    newList->head = NULL;
    newList->count = 0;
    return *newList;

}

List empty(List L){

}

List insertFirst(List list, int data){
    Node *newNode = malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = list.head;
    list.head = newNode;
    list.count++;
    return list;

}

List insertLast(List list, int data){
    Node *newNode = malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    if(list.head == NULL){
        list.head = newNode;
        list.count++;
        return list;
    }
    Node* current = list.head;
    while(current != NULL){
        current = current->next;
    }
    current->next = newNode;
    list.count++;

}

List insertPos(List list, int data, int index){
    if(index > list.count){
        return list;
    }
    if(index == 0){
        insertFirst(list, data);
        return list;
    }
    if(index == list.count){
        insertLast(list, data);
        return list;
    }
    Node* newNode = malloc(sizeof(Node));
    newNode->data = data;
    Node* current = list.head;
    for(int i = 0; i < index - 1 && current->next != NULL; i++){
        current = current->next;
    }
    newNode->next = current->next;
    current->next = newNode;
    list.count++;

    return list;

}

List deleteFirst(List list){
    Node* current = list.head;
    list.head = list.head->next;
    free(current);
    list.count--;
    return list;

}

List deleteLast(List list){
    if(list.count == 1){
        free(list.head);
        list.head = NULL;
        list.count--;
        return list;
    }
    Node* current = list.head;
    for(int i = 0; i < list.count - 2; i++){
        current = current->next;
    }
    free(current->next);
    current->next = NULL;
    list.count--;
    return list;

}

List deletePos(List list, int index){
    if(index == 0){
        deleteFirst(list);
        return list;
    }

    Node* current = list.head;
    for(int i = 0; i < index - 1; i++){
        current = current->next;
    }
    Node* temp = current->next;
    current->next = temp->next;
    free(temp);
    list.count++;
    return list;

}

int retrieve(List list, int index){
    if(index >= list.count || index < 0){
        printf("Invalid index");
        return -1;
    }

    Node* current = list.head;
    for(int i = 0; i < index; i++){
        current = current->next;
    }
    return current->data;

}

int locate(List list, int data){
    if(list.head == NULL){
        return -1;
    }
    
    Node* current = list.head;
    int index = 0;
    for(; current->next != NULL; index++){
        if(current->data == data){
            return index;
        }
        current = current->next;
    }
    return -1;

}

void display(List list){
    Node *current = list.head;
    for(int i = 0; i < list.count; i++){
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL");
}