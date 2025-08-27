#include <stdio.h>
#include <stdlib.h>

#define MAX 10

typedef struct{
    int elem[MAX];
    int count;
}Etype, *EPtr;

void initialize(EPtr);
void insertPos(EPtr, int, int);
void deletePos(EPtr, int);
int locate(EPtr, int);
int retrieve(EPtr, int);
void insertSorted(EPtr, int);
void display(EPtr);
void makeNULL(EPtr);

int main(){

    EPtr L;
    int find;

    initialize(L);

    insertPos(L,10,0);
    insertPos(L,20,1);
    insertPos(L,30,2);
    insertPos(L,40,3);
    insertPos(L,50,6);

    printf("Insert:\n");
    display(L);

    find = locate(L,20);
    printf("%d\n\n", find);

    printf("-----------------------------------------");

    printf("\nLocate:\n");
    printf("%d\n\n", find);

    deletePos(L,1);

    printf("-----------------------------------------");

    printf("\nDelete:\n");
    display(L);

    insertSorted(L,25);

    printf("-----------------------------------------");

    printf("\nInsert Sorted:\n");
    display(L);

    find = locate(L,20);

    printf("-----------------------------------------");

    printf("\nLocate:\n");
    printf("%d\n", find);

    find = locate(L,50);

    printf("-----------------------------------------");

    printf("\nLocate:\n");
    printf("%d\n", find);

    makeNULL(L);
    
    return 0;
}

void initialize(EPtr L){

    for(int i = 0; i < MAX; i++){
        L->elem[i] = -1;
    }
    L->count = 0;
}

void insertPos(EPtr L, int data, int position){
    if(L->count < MAX){
        if(L->elem[position] == -1){
            L->elem[position] = data;
            L->count++;
        }else if(L->elem[position] != -1){
            int i;
            //shift elems to right
            for(i = L->count; i > position; i--){
                L->elem[i] = L->elem[i-1];
            }
        
            //insert to position
            L->elem[position] = data;
            L->count++;
        }
    }
}

int locate(EPtr L, int data){
    int i;
    for(i = 0; i < MAX && L->elem[i] != data; i++){}

    return (i < MAX) ? i : -1;
}

void deletePos(EPtr L, int position){
    if(position <= (L->count - 1)){
        if(L->elem[position] != -1){
            for(int i = position; i < L->count; i++){
                L->elem[i] =  L->elem[i+1];
            }
            L->count--;
        }
    }
}

int retrieve(EPtr L, int position){
    int i = 0;
    if(position <= (L->count - 1)) i=1;
    return (i > 0) ? L->elem[position] : -1;
}

void insertSorted(EPtr L, int data){
    if(L->count < MAX){
        int position, i;
        //find position
        for(position = 0; position < L->count && L->elem[position] > data; position++){}

        //shift elems to right
        for(i = L->count; i > position; i--){
            L->elem[i+1] = L->elem[i];
        }

        //insert to position
        L->elem[position+1] = data;
        L->count++;
    }
}

void display(EPtr L){
    for(int i = 0; i < MAX; i++){
        printf("%d\t", L->elem[i]);
    }
    printf("\n\n");
}

void makeNULL(EPtr L){
    free(L);
}
