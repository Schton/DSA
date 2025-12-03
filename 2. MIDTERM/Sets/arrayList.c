#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 100

typedef struct {
    int content[MAX];
    int size;
} Set;

void initSet(Set *set);
void insertAtVal(Set *set, int data, int pos);
void deleteAtVal(Set *set, int data, int pos);
bool isMember(Set set, int data);
void minVal(Set set);
void maxVal(Set set);
bool equalVal(Set set, int data);
int findVal(Set set, int data);
Set Union(Set A, Set B);
Set Intersection(Set A, Set B);
Set Difference(Set A, Set B);

int main() {
    Set A, B, C;
    initSet(&A);
    initSet(&B);

    insertAtVal(&A, 10, 0);
    insertAtVal(&A, 20, 1);
    insertAtVal(&A, 30, 2);

    insertAtVal(&B, 20, 0);
    insertAtVal(&B, 40, 1);

    printf("A = ");
    for (int i = 0; i < A.size; i++) printf("%d ", A.content[i]);
    printf("\n");

    printf("B = ");
    for (int i = 0; i < B.size; i++) printf("%d ", B.content[i]);
    printf("\n");

    C = Union(A, B);
    printf("Union = ");
    for (int i = 0; i < C.size; i++) printf("%d ", C.content[i]);
    printf("\n");

    C = Intersection(A, B);
    printf("Intersection = ");
    for (int i = 0; i < C.size; i++) printf("%d ", C.content[i]);
    printf("\n");

    C = Difference(A, B);
    printf("Difference = ");
    for (int i = 0; i < C.size; i++) printf("%d ", C.content[i]);
    printf("\n");

    minVal(A);
    maxVal(A);

    deleteAtVal(&A, 20, 0);
    printf("A after delete = ");
    for (int i = 0; i < A.size; i++) printf("%d ", A.content[i]);
    printf("\n");

    return 0;
}

void initSet(Set *set){
    set->size = 0;
}

void insertAtVal(Set *set, int data, int pos){
    if(pos > set->size || pos < 0){
        printf("Invalid\n");
        return;
    }
    if(set->size >= MAX){
        printf("Set is full.\n");
        return;
    }
    for(int i = set->size; i > pos; i--){
        set->content[i] = set->content[i - 1];
    }
    set->content[pos] = data;
    set->size++;
}

void deleteAtVal(Set *set, int data, int pos){
    if(pos >= set->size || pos < 0){
        printf("Invalid\n");
        return;
    }
    if(set->size <= 0){
        printf("Set is empty.\n");
        return;
    }

    int index = -1;
    for(int i = 0; i < set->size; i++){
        if(set->content[i] == data){
            index = i;
            break;
        }
    }
    for(int i = index; i < set->size - 1; i++){
        set->content[i] = set->content[i + 1];
    }
    set->size--;
}

bool isMember(Set set, int data){
    for(int i = 0; i < set.size; i++){
        if(set.content[i] == data){
            return true;
        }
    }
    return false;
}

void minVal(Set set){
    int min = set.content[0];
    for(int i = 1; i < set.size; i++){
        if(set.content[i] < min){
            min = set.content[i];
        }
    }
    printf("Minimum value: %d\n", min);
}

void maxVal(Set set){
    int max = set.content[0];
    for(int i = 1; i < set.size; i++){
        if(set.content[i] > max){
            max = set.content[i];
        }
    }
    printf("Maximum value: %d\n", max);
}

bool equalVal(Set set, int data){
    for(int i = 0; i < set.size; i++){
        if(set.content[i] == data){
            return true;
        }
    }
    return false;
}

int findVal(Set set, int data){
    for(int i = 0; i < set.size; i++){
        if(set.content[i] == data){
            return i;
        }
    }
    return -1;
}

Set Union(Set A, Set B){
    Set Result;
    initSet(&Result);

    for(int i = 0; i < A.size; i++){
        insertAtVal(&Result, A.content[i], Result.size);
    }

    for(int i = 0; i < B.size; i++){
        if(!isMember(Result, B.content[i])){
            insertAtVal(&Result, B.content[i], Result.size);
        }
    }

    return Result;
}

Set Intersection(Set A, Set B){
    Set Result;
    initSet(&Result);

    for(int i = 0; i < A.size; i++){
        if(isMember(B, A.content[i])){
        insertAtVal(&Result, A.content[i], Result.size);
        }
    }
    return Result;
}

Set Difference(Set A, Set B){
    Set Result;
    initSet(&Result);

    for(int i = 0; i < A.size; i++){
        if(!isMember(B, A.content[i])){
        insertAtVal(&Result, A.content[i], Result.size);
        }
    }
    return Result;
}

