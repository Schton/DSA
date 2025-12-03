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

//Function Prototypes
void initialize(VHeap *V);
int allocSpace(VHeap* V);
void deallocSpace(VHeap* V, int index);
void insertFirst(int* L, VHeap* V, int elem);
void insertLast(int* L, VHeap* V, int elem);
void insertSorted(int* L, VHeap* V, int elem);
void delete(int* L, VHeap* V, int elem);
void deleteAllOccurrence(int* L, VHeap* V, int elem);
void display(int L, VHeap V);

int main (){

    VHeap* V;
    initialize(&V);

    return 0;
}

// Functions
void initialize(VHeap *V){
    /*
    Set avail to the beginning of list
    Traverse the list and update each cell’s next to create a chain
    Set last cell’s next to -1
    */

    int i;
    V->avail = 0;
    for(i = V->avail; i < MAX - 1; i++){
        V->H[i].next = i + 1;
    }
    V->H[i].next = -1;
}

int allocSpace(VHeap* V){
    /*
    Check if there is an available cell in the virtual heap
    Get the index of the first available cell
    Update avail to the next available cell
    Return the index of the allocated cell
    */

    int ret = V->avail;
    if(ret != -1){
        V->avail = V->H[ret].next;
    }
    return ret;
}

void deallocSpace(VHeap* V, int index){
    /*
    Set the next of the deallocated cell to the current avail index
    Update avail to point to the newly deallocated cell
    */

    if(index >= 0 && index < MAX){
        V->H[index].next = V->avail;
        V->avail = index;
    }
}

void insertFirst(int* L, VHeap* V, int elem){
    /*
    Allocate a new cell
    Check if allocation was successful
    Set the element of the new cell
    Set the next of the new cell to the current list head
    Update the list head to point to the new cell
    */

    int newCell = allocSpace(V);
    if(newCell != -1){
        V->H[newCell].elem = elem;
        V->H[newCell].next = *L;
    }
    *L = newCell;
}

void insertLast(int* L, VHeap* V, int elem){
    /*
    Allocate a new cell
    Check if allocation was successful
    Set the element of the new cell
    Set the 'next' of the new cell to -1
    Use a pointer to traverse to the last cell
    Update next of last cell to new cell
    */
    
    int newCell = allocSpace(V);
    if(newCell != -1){
        V->H[newCell].elem = elem;
        V->H[newCell].next = -1;
        int *trav = L;
        while(*trav != -1){
            trav = &V->H[*trav].next;
        }
        *trav = newCell;
    }
}

void insertSorted(int* L, VHeap* V, int elem){
    /*
    Allocate a new cell
    Check if allocation was successful
    Set the element of the new cell
    Use a pointer to traverse the list
    Stop when the next element is greater than or equal to the new element
    Update the new cell’s next to point to the current cell
    Update the previous cell’s next to point to the new cell
    */

    int newCell = allocSpace(V);
    if(newCell != -1){
        V->H[newCell].elem = elem;
        int *trav = L;
        while(*trav != -1 && V->H[*trav].elem < elem){
            trav = &V->H[*trav].next;
        }
        V->H[newCell].next = *trav;
        *trav = newCell;
    }
}

void delete(int* L, VHeap* V, int elem){
    /*
    Use a pointer to traverse the list
    Stop when the element is found or the end of the list is reached
    If found, store the index of the current cell
    Update the previous cell’s next to skip the current cell
    Deallocate the current cell to return it to the free list
    */

    int *trav, temp;
    trav = L;

    while(*trav != -1 && V->H[*trav].elem != elem){
        trav = V->H[*trav].next;
    }
    if(*trav != -1){
        temp = *trav;
        *trav = V->H[temp].next;
        deallocSpace(V, temp);
    }
}

void deleteAllOccurrence(int* L, VHeap* V, int elem){
    /*
    Use a pointer to traverse the list
    For each cell, check if the element matches the target value
    If it matches:
        - Save the index of the current cell
        - Update the previous cell’s next to skip the current cell
        - Deallocate the current cell to return it to the free list
    Otherwise, move to the next cell
    Repeat until the end of the list is reached
    */

    int *trav = L, temp;
    
    while(*trav != -1){
        if(V->H[*trav].elem = elem){
            temp = *trav;
            *trav = V->H[temp].next;
            deallocSpace(V, temp);
        } else {
            trav = &V->H[*trav].next;
        }
    }
}

void display(int L, VHeap V){
    /*
    Print all cell values in correct order starting from List head until next is -1
    */
   
    for(int i = L; i != -1; V.H[i].next){
        printf("%d ", V.H[i].elem);
    }
    printf("\n");
}