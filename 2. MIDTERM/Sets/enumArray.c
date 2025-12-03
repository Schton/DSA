#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ARRAY_SIZE 8
// The Set itself is an array of booleans/integers
typedef bool Set[ARRAY_SIZE];

// Prototypes with parameters
void initialize(Set set);
void insert(Set set, int element);
void delete(Set set, int element);
bool find(Set set, int element);
void set_union(Set A, Set B, Set C);
void intersection(Set A, Set B, Set C);
void difference(Set A, Set B, Set C);
void display(Set set);

int main (){
    Set A, B, C;

    initialize(A);
    initialize(B);
    initialize(C);

    insert(A, 0);
    insert(A, 2);
    insert(A, 7);

    insert(B, 2);
    insert(B, 4);
    insert(B, 5);

    printf("Set A = ");
    display(A);
    printf("Set B = ");
    display(B);
    
    printf("Find: ");
    bool found = find(B, 5);
    if(found){
        printf("Element is found\n");
    } else {
        printf("Element is not found\n");
    }

    printf("Union A, B is Set C = ");
    set_union(A, B, C);
    display(C);
    printf("Intersection A, B is Set C = ");
    intersection(A, B, C);
    display(C);
    printf("Difference A, B is Set C = ");
    difference(A, B, C);
    display(C);

    return 0;
}

/*
Iterate through every index from 0 up to ARRAY_SIZE-1
Set the value at each index to false
*/
void initialize(Set set){
    for(int i = 0; i < ARRAY_SIZE; i++){
        set[i] = false;
    }
}

/*
Safety check: ensure element index is within the array range
Use the 'element' value as the array index
Set the value at that index to true
*/
void insert(Set set, int element){
    if(element < 0 || element > 7){
        printf("Error: element %d out of range (0-7)\n", element);
        return;
    }
    set[element] = true;
}

/*
Safety check: ensure element index is within the array range
Use the 'element' value as the array index
Set the value at that index to false
*/
void delete(Set set, int element){
    if(element < 0 || element > 7){
        printf("Error: element %d out of range (0-7)\n", element);
        return;
    }
    set[element] = false;
}

/*
Safety check: ensure element index is within the array range
Access the array index corresponding to the element
The value at that index (true/1 or false/0) directly indicates presence
*/
bool find(Set set, int element){
    if(element < 0 || element > 7) return false;
    return (set[element] == 1) ? true : false;  
}

/*
The resulting set (C) is where the union will be stored
Iterate through every possible element index
The resulting set element is true if it is present in set A OR set B
*/
void set_union(Set A, Set B, Set C){
    for(int i = 0; i < ARRAY_SIZE; i++){
        C[i] = A[i] | B[i];
    }
}

/*
The resulting set (C) is where the intersection will be stored
Iterate through every possible element index
The resulting set element is true if it is present in set A AND set B
*/
void intersection(Set A, Set B, Set C){
    for(int i = 0; i < ARRAY_SIZE; i++){
        C[i] = A[i] & B[i];
    }
}

/*
The resulting set (C) is where the difference will be stored
Iterate through every possible element index
The resulting set element is true ONLY if it is present in A AND NOT in B
*/
void difference(Set A, Set B, Set C){
    for(int i = 0; i < ARRAY_SIZE; i++){
        C[i] = A[i] & (!B[i]);
    }
}

/*
Iterate and list the elements that are TRUE
*/
void display(Set set){

    printf("[");
    for(int i = 0; i < ARRAY_SIZE; i++){
        printf("%d", set[i] ? 1 : 0);
        if(i != ARRAY_SIZE - 1) printf(", ");
    }
    printf("] ");

    printf("{");
    bool first = true;
    for(int i = 0; i < ARRAY_SIZE; i++){
            if(set[i]){
            if(!first) printf(", ");
            printf("%d", i);
            first = false;
        }
    }
    printf("}\n");
}
