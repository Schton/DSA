#include <stdio.h>
#include <stdbool.h>

#define MAX 10

typedef struct{
    char elem[MAX];
    int count;
}charList;

bool findElem(charList, char); // Answer to #1

void main(){

    // Answer to #2 and #5
    charList L = {{'U','S','C'},3};;
    bool result;

    if(L.count > 1){
        result = findElem(L,'S');

        if(result){
            printf("The list is not empty and element X is in the list.");
        } else{
            printf("The list is not empty and element X is not in the list.");
        }
    } else{
        printf("The list is empty.");
    }
    
}

// Answer to #4
bool findElem(charList L, char x){

    int i;
    for(i = 0; i < L.count && L.elem[i] != x; i++){}

    return (i < L.count) ? true : false; 
}

// #3, draw an execution stack
