#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
 
#define MAX_P 5
#define MAX_S 5
#define TOTAL_SIZE (MAX_P + MAX_S)
#define EMPTY 0
#define NIL -1 // Next In Line

typedef struct {
    int elem;
    int next;
    bool occupied;
} Entry;

typedef struct {
    Entry table[TOTAL_SIZE];
    int avail;
} Dictionary;

void initDictionary(Dictionary *Dict);
int hash(int value);
void insertDictionary(Dictionary *Dict, int data);
void deleteData(Dictionary *Dict, int data);
bool search(Dictionary Dict, int data); // isMember
void display(Dictionary Dict); 


int main (){

    Dictionary Dict;
    initDictionary(&Dict);

    insertDictionary(&Dict, 50);
    insertDictionary(&Dict, 67);
    insertDictionary(&Dict, 34);
    insertDictionary(&Dict, 22);
    insertDictionary(&Dict, 21);
    insertDictionary(&Dict, 23);
    insertDictionary(&Dict, 33);
    insertDictionary(&Dict, 50);
    insertDictionary(&Dict, 30);
    insertDictionary(&Dict, 29);
    insertDictionary(&Dict, 31);

    bool found = search(Dict, 34);
    if(found){
        printf("Data Exists\n");
    } else {
        printf("Data does not Exist\n");
    }

    display(Dict);
    return 0;
}

void initDictionary(Dictionary *Dict){
    //Primary
    for(int i = 0; i < MAX_P; i++){
        Dict->table[i].occupied = false;
        Dict->table[i].elem = EMPTY;
        Dict->table[i].next = NIL;
    }

    //Secondary
    for(int i = MAX_P; i < TOTAL_SIZE; i++){
        Dict->table[i].occupied = false;
        Dict->table[i].elem = EMPTY;
        Dict->table[i].next = i + 1;
    }

    Dict->table[TOTAL_SIZE - 1].occupied = false;
    Dict->table[TOTAL_SIZE - 1].next = NIL;

    Dict->avail = MAX_P;
}

int hash(int value){
    return value % MAX_P;
}

void insertDictionary(Dictionary *Dict, int data){
    int index = hash(data);

    if(!Dict->table[index].occupied){
        Dict->table[index].elem = data;
        Dict->table[index].occupied = true;
        Dict->table[index].next = NIL;
        printf("Inserted %d at primary [%d].\n", data, index);
        return;
    }

    int temp = index;
    while(Dict->table[temp].next != NIL){
        temp = Dict->table[temp].next;
    }
    if(Dict->avail == NIL){
        printf("No available space.\n");
        return;
    }

    int newIndex = Dict->avail;
    Dict->avail = Dict->table[newIndex].next;

    Dict->table[newIndex].elem = data;
    Dict->table[newIndex].occupied = true;
    Dict->table[newIndex].next = NIL;
    Dict->table[temp].next = newIndex;

    printf("Collision! Inserted %d at secondary [%d], linked from [%d].\n", data, newIndex, temp);
}

void deleteData(Dictionary *Dict, int data){
    int index = hash(data);
    int prev = NIL;

    while(index != NIL && Dict->table[index].elem != data){
        prev = index;
        index = Dict->table[index].next;
    }

    if(index == NIL){
        printf("%d not found.\n", data);
        return;
    }

    printf("Deleting %d from [%d].\n", data, index);
    Dict->table[index].occupied = false;
    Dict->table[index].elem = EMPTY;

    if(index >= MAX_P){
        Dict->table[index].next = Dict->avail;
        Dict->avail = index;
    }

    if(prev != NIL){
        Dict->table[prev].next = Dict->table[index].next;
    }
}

bool search(Dictionary Dict, int data){
    int index = hash(data);

    while(index != NIL){
        if(Dict.table[index].occupied && Dict.table[index].elem == data){
            return true;
        }
        index = Dict.table[index].next;
    }
    return false;
}

void display(Dictionary Dict){
    printf("\n%-8s %-8s %-8s %-8s\n", "Index", "Elem", "Next", "Occupied");
    printf("----Primary----\n");
    for(int i = 0; i < MAX_P; i++){
        printf("[%2d]    %-8d %-8d %-8s\n",
               i,
               Dict.table[i].elem,
               Dict.table[i].next,
               Dict.table[i].occupied ? "true" : "false");
    }

    printf("\n----Secondary----\n");
    for(int i = MAX_P; i < TOTAL_SIZE; i++){
            printf("[%2d]    %-8d %-8d %-8s\n",
               i,
               Dict.table[i].elem,
               Dict.table[i].next,
               Dict.table[i].occupied ? "true" : "false");
    }
        printf("\nAvail = %d\n", Dict.avail);
}