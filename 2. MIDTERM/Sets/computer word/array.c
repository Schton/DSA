#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Prototypes with parameters
void initialize(unsigned char *set);
void insert(unsigned char *set, int element);
void delete(unsigned char *set, int element);
bool find(unsigned char set, int element);
unsigned char set_union(unsigned char A, unsigned char B);
unsigned char intersection(unsigned char A, unsigned char B);
unsigned char difference(unsigned char A, unsigned char B);
void display(unsigned char set);

int main (){
    unsigned char A, B, C;

    initialize(&A);
    initialize(&B);

    insert(&A, 1);
    insert(&A, 6);

    insert(&B, 3);
    insert(&B, 6);
    insert(&B, 7);

    printf("Set A = ");
    display(A);
    printf("Set B = ");
    display(B);

    printf("Find: ");
    bool found = find(A, 6);
    if(found){
        printf("Element is found\n");
    } else {
        printf("Element is not found\n");
    }

    printf("Union A,B is Set C = ");
    C = set_union(A, B);
    display(C);

    printf("Intersection A, B is Set C = ");
    C = intersection(A, B);
    display(C);

    printf("Difference A, B is Set C = ");
    C = difference(A, B);
    display(C);

    return 0;
}

//Set the entire byte/integer to 0
void initialize(unsigned char *set){
    *set = 0;
}

/*
Safety check: ensure element index is within the bit range
Create a bitmask for the element's position
Perform Bitwise OR assignment
*/
void insert(unsigned char *set, int element){
    if(element < 0 || element > 7){
        printf("Error: element %d out of range (0-7)\n", element);
        return;
    }
    unsigned char mask = 1 << element;
    *set |= mask;
}

/*
Safety check: ensure element index is within the bit range
Create a mask for the element's position
Invert the mask (this creates a mask with a 0 at the target bit and 1s everywhere else)
Perform Bitwise AND assignment
*/
void delete(unsigned char *set, int element){
    if(element < 0 || element > 7){
        printf("Error: element %d out of range (0-7)\n", element);
        return;
    }
    unsigned char mask = 1 << element;
    *set &= ~mask;
}

/*
Create a mask for the element's position
Use Bitwise AND between the set and the mask
*/
bool find(unsigned char set, int element){
    if(element < 0 || element > 7) return false;
    unsigned char mask = 1 << element;
    return (set & mask) != 0;
}

// BITWISE OR [ | ]
unsigned char set_union(unsigned char A, unsigned char B){
    return A | B;
}

// BITWISE AND [ & ]
unsigned char intersection(unsigned char A, unsigned char B){
    return A & B;
}

// BITWISE A AND NOT B [ & (~) ]
unsigned char difference(unsigned char A, unsigned char B){
    return A & (~B);
}

/*
Iterate through all possible elements (0 to 7)
Check if the bit corresponding to element i is set
If present, print the element, separated by commas
*/
void display(unsigned char set){
    
    // Display as unsigned integer value
    printf("%u ", set);

    //Display Set Elements
    printf("{");
    bool first = true;
    for(int i = 0; i < 8; i++){
        if(set & (1 << i)){
            if(!first) printf(", ");
            printf("%d", i);
            first = false;
        }
    }
    printf("} ");

   // Display binary bits (positions)
    printf("(");
    for(int i = 7; i >= 0; i--){
        printf("%d", (set >> i) & 1);
    }
    printf(")\n");
}
