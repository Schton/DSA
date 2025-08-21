#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct node{
    char elem;
    struct node *link;
}*charList;

bool findElem(charList, char); // Answer to #1
void populate(charList*, char); 

void main(){
    // Answer to #2 and #5
    charList head = NULL;

    populate(&head,'U');
    populate(&head,'S');
    populate(&head,'C');

    char x;

    if(!head) printf("The list is empty.");
    else{
        printf("Enter a letter: ");
        scanf("%c", &x);

        bool result = findElem(head,x);

        if(result) printf("The list is not empty and element X is in the list.");
        else printf("The list is not empty and element X is not in the list.");
    }
    
}

void populate(charList* L, char x){

    charList temp = malloc(sizeof(struct node));
    temp->elem = x;
    temp->link = NULL;

    if(*L == NULL) *L = temp;
    else{
        charList* trav = L;

        while((*trav)->link != NULL) {
            trav = &(*trav)->link;
        }
        (*trav)->link = temp;
    }
}

// Answer to #4
bool findElem(charList L, char x){

    charList trav;
    for(trav = L; trav != NULL && trav->elem != x; trav = trav->link){}

    return (trav) ? true : false;
}

// #3, draw an execution stack