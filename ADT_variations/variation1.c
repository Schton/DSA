#include <stdio.h>

#define MAX 10

typedef struct{
    int elem[MAX];
    int count;
}List;

List initialize(List);
List insertPos(List, int, int);
List deletePos(List, int);
int locate (List , int);
List insertSorted (List, int);
void display(List);

void main(){

    List L;
    int find;
    L = initialize(L);

    L = insertPos(L,10,0);
    L = insertPos(L,20,1);
    L = insertPos(L,30,2);
    L = insertPos(L,40,3);
    L = insertPos(L,50,6);

    printf("Insert:\n");
    display(L);

    find = locate(L,20);

    printf("-----------------------------------------");

    printf("\nLocate:\n");
    printf("%d\n\n", find);

    L = deletePos(L,1);

    printf("-----------------------------------------");

    printf("\nDelete:\n");
    display(L);

    L = insertSorted(L,25);

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

}

List initialize(List L){
    for(int i = 0; i < MAX; i++){
        L.elem[i] = -1;
    }
    L.count = 0;

    return L;
}
List insertPos(List L, int data, int position){
    if(L.elem[position] == -1){
        L.elem[position] = data;
        L.count++;
    }
    return L;
}
List deletePos(List L, int position){
    if(L.elem[position] != -1){
        for(int i = position; i < L.count; i++){
        L.elem[i] =  L.elem[i+1];
    }
    L.count--;
    }
    return L;
}

int locate(List L, int data){
    int i;
    for(i = 0; i < MAX && L.elem[i] != data; i++){}

    return (i < MAX) ? i : -1;
}

List insertSorted(List L, int data){
    int position, i;
    //find position
    for(position = 0; position < L.count && L.elem[position] > data; position++){}

    //shift elems to right
    for(i = L.count; i > position; i--){
        L.elem[i+1] = L.elem[i];
    }

    //insert to position
    L.elem[position+1] = data;
    L.count++;

    return L;

}

void display(List L){

    for(int i = 0; i < MAX; i++){
        printf("%d\t", L.elem[i]);
    }
    printf("\n\n");

}

