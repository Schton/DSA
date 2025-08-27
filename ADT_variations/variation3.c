#include <stdio.h>
#include <stdlib.h>

#define LENGTH 10

typedef struct{
    int *elemPtr;
    int count;
    int max;
}List;

List initialize(List);
List insertPos(List, int, int);
List deletePos(List, int);
int locate(List, int);
List  insertSorted(List, int);
void display(List);
List resize(List);

int main(){

    List L;
    int find;

    L = initialize(L);

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

List initialize(List L){
    L.elemPtr = (int*)malloc(sizeof(int) * LENGTH);
    L.count = 0;
    L.count = LENGTH;

    for(int i = 0; i < L.max; i++){
        L.elemPtr[i] = -1;
    }

    return L;
}

List insertPos(List L, int data, int position){
   if(L.count >= L.max) L = resize(L);

   if(L.elemPtr[position] == -1){
        L.elemPtr[position] = data;
        L.count++;
    }else if(L.elemPtr[position] != -1){
        int i;
        //shift elems to right
        for(i = L.count; i > position; i--){
            L.elemPtr[i] = L.elemPtr[i-1];
        }
    
        //insert to position
        L.elemPtr[position] = data;
        L.count++;
    }

    return L;
}
List deletePos(List L, int position){
    if(position <= (L.count - 1)){
        if(L.elemPtr[position] != -1){
            for(int i = position; i < L.count; i++){
                L.elemPtr[i] =  L.elemPtr[i+1];
            }
            L.count--;
        }
    }
}
int locate(List L, int data){
    int i;
    for(i = 0; i < L.max && L.elemPtr[i] != data; i++){}

    return (i < L.max) ? i : -1;
}
List  insertSorted(List L, int data){
    if(L.count < L.max){
        int position, i;
        //find position
        for(position = 0; position < L.count && L.elemPtr[position] > data; position++){}

        //shift elems to right
        for(i = L.count; i > position; i--){
            L.elemPtr[i+1] = L.elemPtr[i];
        }

        //insert to position
        L.elemPtr[position+1] = data;
        L.count++;
    }
}
void display(List L){
    for(int i = 0; i < L.max; i++){
        printf("%d\t", L.elemPtr[i]);
    }
    printf("\n\n");
}
List resize(List L){

    L.max *= 2;

    int *newPtr = realloc(L.elemPtr, L.max * sizeof(int));

    L.elemPtr = newPtr;

    for (int i = L.count; i < L.max; i++) {
        L.elemPtr[i] = -1;
    }

    return L;
}