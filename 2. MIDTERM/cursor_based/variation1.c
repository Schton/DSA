#include <stdio.h>
#include <stdlib.h>

#define MAX 4

typedef struct {
    int elem;
    int next;
} Cell, HeapSpace[MAX];

typedef struct {
    HeapSpace H;
    int avail;
} VHeap;

typedef int List;

void initialize(VHeap *V);
int allocSpace(VHeap* V);
void deallocSpace(VHeap* V, int index);
void insertFirst(int* L, VHeap* V, int elem);
void insertLast(int* L, VHeap* V, int elem);
void insertSorted(int* L, VHeap* V, int elem);
void delete(int* L, VHeap* V, int elem);
void deleteAllOccurrence(int* L, VHeap* V, int elem);
void display(int L, VHeap V);

int main() {
    VHeap V;

    initialize(&V); 

    // for (int i = 0; i < MAX; i++) {
    //     printf("%d\t", V.H[i].next);
    // }

    return 0;
}

void initialize(VHeap *V) {
    int i;

    for (i = 0; i < MAX; i++) {
        V->H[i].next = i + 1;
    }
    V->H[i - 1].next = -1;
    V->avail = 0; 

    V->H[0].elem = 10;
    V->H[1].elem = 20;
}

int allocSpace(VHeap* V){

    // Check if there is an available cell in the virtual heap
    // Get the index of the first available cell
    // Update avail to the next available cell
    // Return the index of the allocated cell

    int availCell = -1, i;

    if(V->avail != -1){
        for (i = 0; i < MAX && V->H[i].next != -1; i++){}
    }



    return availCell;
}