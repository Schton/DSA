#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX 10
#define EMPTY -2
#define DELETED -1

typedef struct {
    int itemID;
    char itemName[32];
    int stock;
} Item;

typedef Item Dictionary[MAX];

void initDictionary(Dictionary Dict);
int hash(Item item);
void insertDictionary(Dictionary Dict, Item item);
void deleteData(Dictionary Dict, Item item);
bool search(Dictionary Dict, Item item); // isMember
void display(Dictionary Dict); 

int main (){
    Dictionary dict;
    initDictionary(dict);

    Item items[10] = {
        {101, "Apple", 52},
        {102, "Banana", 32},
        {103, "Orange", 42},
        {104, "Mango", 24},
        {105, "Grapes", 63},
        {106, "Pineapple", 15},
        {107, "Strawberry", 40},
        {108, "Watermelon", 20},
        {109, "Kiwi", 35},
        {110, "Cherry", 55}
    };

    
    for (int i = 0; i < MAX; i++) {
        insertDictionary(dict, items[i]);
    }

    deleteData(dict, items[1]);
    display(dict);

    return 0;
}

void initDictionary(Dictionary Dict){
    for(int i = 0; i < MAX; i++){
        Dict[i].itemID = EMPTY;
        strcpy(Dict[i].itemName, "EMPTY");
        Dict[i].stock = 0;
    }
}

int hash(Item item){
    return item.stock % MAX;
}

void insertDictionary(Dictionary Dict, Item item){
    int index = hash(item);

    for(int i = 0; i < MAX; i++){
        int pos = (index + i) % MAX;

        if(Dict[pos].itemID == EMPTY || Dict[pos].itemID == DELETED){
            Dict[pos].itemID = item.itemID;
            strcpy(Dict[pos].itemName, item.itemName);
            Dict[pos].stock = item.stock;
            printf("Inserted item\n");
            return;
        }
    }
}

void deleteData(Dictionary Dict, Item item){
    int index = hash(item);

    for(int i = 0; i < MAX; i++){
        int start = (index + i) % MAX;

        if(Dict[start].stock == item.stock){
            Dict[start].stock = DELETED;
            printf("Deleted stock %d\n", item.stock);
            return;
        }

        if(Dict[start].stock == EMPTY){
            printf("Empty stock %d\n", item.stock);
            return;
        }
    }
    
}

bool search(Dictionary Dict, Item item){
    int index = hash(item);

    for(int i = 0; i < MAX; i++){
        int start = (index + i) % MAX;

        if(Dict[start].stock == item.stock){
            return true;
        }
    }
    return false;
}

void display(Dictionary Dict){
    printf("\n%-8s | %-10s | %-6s\n", "Index", "ItemName", "Stock");
    printf("---------------------------------\n");
    for (int i = 0; i < MAX; i++) {
        if (Dict[i].itemID == EMPTY) {
            printf("[%2d]     %-10s | %-6s\n", i, "EMPTY", "-");
        } else if (Dict[i].itemID == DELETED) {
            printf("[%2d]     %-10s | %-6s\n", i, "DELETED", "-");
        } else {
            printf("[%2d]     %-10s | %-6d\n", i, Dict[i].itemName, Dict[i].stock);
        }
    }
}
