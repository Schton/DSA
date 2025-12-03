#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 10

typedef int Set[MAX];

Set* initSet();
void displayBits(Set set);
void displayElems(Set set);
void insertBit(Set *set, int pos);
void deleteBit(Set *set, int pos);
bool isMember(Set set, int data);
bool isSubset(Set A, Set B);
Set* Union(Set A, Set B);
Set* Intersection(Set A, Set B);
Set* Difference(Set A, Set B);

int main() {
    Set *A, *B, *C;
    A = initSet();
    B = initSet();

    insertBit(A, 10);
    insertBit(A, 8);
    insertBit(A, 6);
    insertBit(A, 4);
    insertBit(A, 2);
    insertBit(A, 0);

    insertBit(B, 9);
    insertBit(B, 7);
    insertBit(B, 4);
    insertBit(B, 2);
    insertBit(B, 1);

    printf("Set A\n");
    printf("Bits: ");
    displayBits(*A);
    printf("Elements: ");
    displayElems(*A);

    printf("\nSet B\n");
    printf("Bits: ");
    displayBits(*B);
    printf("Elements: ");
    displayElems(*B);

    C = initSet();
    printf("\nUnion of A, B\n");
    C = Union(*A, *B);
    printf("Bits: ");
    displayBits(*C);
    printf("Elements: ");
    displayElems(*C);
    printf("\nIntersection of A, B\n");
    C = Intersection(*A, *B);
    printf("Bits: ");
    displayBits(*C);
    printf("Elements: ");
    displayElems(*C);    
    printf("\nDifference of A, B\n");
    C = Difference(*A, *B);
    printf("Bits: ");
    displayBits(*C);
    printf("Elements: ");
    displayElems(*C);

    return 0;
}

Set* initSet() {
    Set *newSet = malloc(sizeof(Set));
    for (int i = 0; i < MAX; i++) {
        (*newSet)[i] = 0;
    }
    return newSet;
}

void insertBit(Set *set, int pos) {
    if (pos >= 0 && pos < MAX)
        (*set)[pos] = 1;
}

void deleteBit(Set *set, int pos) {
    if (pos >= 0 && pos < MAX)
        (*set)[pos] = 0;
}

bool isMember(Set set, int data) {
    if (data >= 0 && data < MAX)
        return set[data] == 1;
    return false;
}

bool isSubset(Set A, Set B) {
    for (int i = 0; i < MAX; i++) {
        if (A[i] == 1 && B[i] == 0)
            return false;
    }
    return true;
}

void displayBits(Set set) {
    for (int i = 0; i < MAX; i++) {
        printf("%d ", set[i]);
    }
    printf("\n");
}

void displayElems(Set set) {
    for (int i = 0; i < MAX; i++) {
        if (set[i] == 1) {
            printf("%d ", i);
        }
    }
    printf("\n");
}

Set* Union(Set A, Set B) {
    Set *result = malloc(sizeof(Set));
    for (int i = 0; i < MAX; i++) {
        (*result)[i] = A[i] || B[i];
    }
    return result;
}

Set* Intersection(Set A, Set B) {
    Set *result = malloc(sizeof(Set));
    for (int i = 0; i < MAX; i++) {
        (*result)[i] = A[i] && B[i];
    }
    return result;
}

Set* Difference(Set A, Set B) {
    Set *result = malloc(sizeof(Set));
    for (int i = 0; i < MAX; i++) {
        (*result)[i] = A[i] && !B[i];
    }
    return result;
}