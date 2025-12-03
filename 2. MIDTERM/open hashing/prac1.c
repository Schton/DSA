//A Bunch of Confusing Pointer/Asterisk
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// MAX SIZE FOR TABLE
#define MAX 10

typedef struct Node {
    char hex[32];
    char name[32];
    struct Node *next;
} Color, *ColorPtr;

typedef ColorPtr Dictionary[MAX]; // Used for Dictionary

void initDictionary(Dictionary Dict); // Initializing Dictionary
int get_NumOfBits(int x);
int get_SumOfLetters(char *key);
unsigned int hash(Color color);
ColorPtr createNode(Color color); // Creating Node
void insert(Dictionary Dict, Color color); // Insert to Dictionary
void populate(Dictionary Dict);
void display(Dictionary Dict);

int main(void) {

    Dictionary Dict;
    initDictionary(Dict);
    populate(Dict);
    display(Dict);

    return 0;
}

// Set All Indexes to NULL
void initDictionary(Dictionary Dict){
    for(int i = 0; i < MAX; i++){
        Dict[i] = NULL;
    }
}

int get_NumOfBits(int x) {
    unsigned int mask = 1 << (sizeof(int) * 8 - 1);
    int num = 0;

    for (; mask != 0; mask >>= 1) {
        if (x & mask) num++;
    }
    return num;
}

int get_SumOfLetters(char *key) {
    int length = strlen(key);
    int sum = 0;

    for (int i = 0; i < length; i++) {
        sum += key[i];
    }
    return sum;
}

// Hashing to get index
unsigned int hash(Color data) {
    return ((get_NumOfBits(get_SumOfLetters(data.hex)) * get_SumOfLetters(data.name) + 31)) % MAX;
}

// Creating Node
ColorPtr createNode(Color color){
    Color* newNode = malloc(sizeof(Color));
    strcpy(newNode->hex, color.hex);
    strcpy(newNode->name, color.name);
    newNode->next = NULL;
    return newNode;
}

// Inserting to dictionary using insert first
void insert(Dictionary Dict, Color data) {
    int index = hash(data);
    ColorPtr newNode = createNode(data);

    if(Dict[index] == NULL){
        Dict[index] = newNode;
    } else {
        ColorPtr current = Dict[index];
        while(current->next != NULL){
            current = current->next;
        }
        current->next = newNode;
    }
}

void populate(Dictionary Dict) {
    Color colors[13] = {
      {"#FF0000", "Red"}, {"#00FF00", "Green"}, {"#0000FF", "Blue"},
      {"#FFFF00", "Yellow"}, {"#FFA500", "Orange"}, {"#800080", "Purple"},
      {"#00FFFF", "Cyan"}, {"#FFC0CB", "Pink"}, {"#808080", "Gray"},
      {"#000000", "Black"}, {"#FFFFFF", "White"}, {"#A52A2A", "Brown"},
      {"#008000", "Dark Green"}
    };
    int length = sizeof(colors) / sizeof(colors[0]);
    for (int i = 0; i < length; i++) {
        insert(Dict, colors[i]);
    }
}

// Display dictionary using if index of dict is null or not then print the data within the node
void display(Dictionary Dict) {
    printf("Table:\n");
    printf("\t%-4s%7s\n", "nDx", "Head");

    for (int i = 0; i < MAX; i++) {
        printf("\t%2d   ", i);
        if (Dict[i] == NULL) {
            printf("[ EMPTY ]");
        } else {
            printf("[ LINK ]");
            ColorPtr temp = Dict[i];
            while (temp != NULL) {
                printf(" -> [ %-8s %s ]", temp->hex, temp->name);
                temp = temp->next;
            }
        }
        printf(" -> NULL\n");
    }
}