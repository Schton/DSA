#include <stdio.h>
#include <stdlib.h>

#define LENGTH 10

typedef struct{
    int id;
}studtype;

typedef struct{
    studtype *elemPtr;
    int count;
    int max;
}List;

void initialize(List*);
void insertPos(List*, int, int);
void deletePos(List*, int);
int locate(List, int);
int retrieve(List, int);
void insertSorted(List*, int);
void display(List);
void resize(List*);
void makeNULL(List*);

int main(){

    List L;
    int find;

    initialize(&L);

    insertPos(&L,1111,0);
    insertPos(&L,2222,1);
    insertPos(&L,5555,2);
    insertPos(&L,6666,3);
    insertPos(&L,7777,6);

    printf("Insert:\n");
    display(L);

    printf("-----------------------------------------");


    deletePos(&L,1);
    printf("\nDelete:\n");
    display(L);

    printf("-----------------------------------------");

    insertSorted(&L,3333);
    printf("\nInsert Sorted:\n");
    display(L);

    printf("-----------------------------------------");
    find = locate(L,5555);
    printf("\nLocate:\n");
    printf("%d\n", find);

    printf("-----------------------------------------");
    find = locate(L,4444);
    printf("\nLocate:\n");
    printf("%d\n", find);

    printf("-----------------------------------------");
    printf("\nRetrieve:\n");    
    int ret = retrieve(L, 6);
    printf("%d\n", ret);

    makeNULL(&L);
    return 0;
}

void initialize(List *L) {
    L->elemPtr = (studtype *)malloc(sizeof(studtype) * LENGTH);
    L->count = 0;
    L->max = LENGTH;
}

void resize(List *L) {
    L->max *= 2;
    L->elemPtr = (studtype *)realloc(L->elemPtr, sizeof(studtype) * L->max);
}

void insertPos(List *L, int data, int position) {
    if (position < 0 || position > L->count) {
        printf("Invalid position!\n");
        return;
    }
    if (L->count == L->max) {
        resize(L);
    }

    for (int i = L->count; i > position; i--) {
        L->elemPtr[i] = L->elemPtr[i - 1];
    }

    L->elemPtr[position].id = data;
    L->count++;
}

void deletePos(List *L, int position) {
    if (position < 0 || position >= L->count) {
        printf("Invalid position!\n");
        return;
    }

    for (int i = position; i < L->count - 1; i++) {
        L->elemPtr[i] = L->elemPtr[i + 1];
    }

    L->count--;
}

int locate(List L, int data) {
    for (int i = 0; i < L.count; i++) {
        if (L.elemPtr[i].id == data) {
            return i;
        }
    }
    return -1;
}

int retrieve(List L, int position) {
    if (position < 0 || position >= L.max) {
        printf("Invalid position!\n");
        return -1;
    }
    return L.elemPtr[position].id;
}

void insertSorted(List *L, int data) {
    if(L->count < L->max){
        int position, i;
        //find position
        for(position = 0; position < L->count && L->elemPtr[position].id > data; position++){}

        //shift elems to right
        for(i = L->count; i > position; i--){
            L->elemPtr[i+1] = L->elemPtr[i];
        }

        //insert to position
        L->elemPtr[position+1].id = data;
        L->count++;
    }
}

void display(List L) {
    for (int i = 0; i < L.max; i++) {
        printf("%d ", L.elemPtr[i].id);
    }
    printf("\n");
}

void makeNULL(List *L) {
    free(L->elemPtr);
    L->elemPtr = NULL;
    L->count = 0;
    L->max = 0;
}

