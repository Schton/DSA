#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 10

typedef struct Node {
    char name[50];
    int age;
    char course[10];
    int idNum;
    struct Node* next;
} Student, *StudPTR;

typedef StudPTR Dictionary[MAX];

//Dictionary Functions
void initDictionary(Dictionary dict);
Student* createStudent(Student student);
int hash(Student stud);
int getSumLetters(Student stud);
void insertDict(Dictionary dict, Student stud);
void deleteDict(Dictionary dict, Student stud);
bool isMember(Dictionary dict, Student stud);
void display(Dictionary dict);
void destroyDict(Dictionary *Dict); // Free

int main() {
    Dictionary dict;
    initDictionary(dict);

    Student s1 = { .name = "Alice", .age = 20, .course = "BSCS", .idNum = 1001 };
    Student s2 = { .name = "Bob", .age = 21, .course = "BSIT", .idNum = 1002 };
    Student s3 = { .name = "Charlie", .age = 22, .course = "BSCS", .idNum = 1003 };
    Student s4 = { .name = "Dave", .age = 23, .course = "BSIS", .idNum = 1004 };

    insertDict(dict, s1);
    insertDict(dict, s2);
    insertDict(dict, s3);
    insertDict(dict, s4);

    printf("\n--- Initial Dictionary ---\n");
    display(dict);

    printf("\nDeleting Bob...\n");
    deleteDict(dict, s2);

    printf("\n--- After Deletion ---\n");
    display(dict);

    printf("\nIs Charlie in the dictionary? %s\n",
           isMember(dict, s3) ? "Yes" : "No");
    destroyDict(&dict);
    printf("\nAll memory freed.\n");

    return 0;
}

void initDictionary(Dictionary dict){
    for(int i = 0; i < MAX; i++){
        dict[i] = 0;
    }
}

Student* createStudent(Student stud){
    Student* newStudent = malloc(sizeof(Student));
    strcpy(newStudent->name, stud.name);
    newStudent->age = stud.age;
    strcpy(newStudent->course, stud.course);
    newStudent->idNum = stud.idNum;
    newStudent->next = NULL;
    return newStudent;
}

int getSumLetters(Student stud){
    int length = strlen(stud.name);
    int sum = 0;
    for(int i = 0; i < length; i++){
        sum += stud.name[i];
    }
    return sum;
}

int hash(Student stud){
    return (getSumLetters(stud)) % MAX;
}

void insertDict(Dictionary dict, Student stud){
    int index = hash(stud);
    Student* newStudent = createStudent(stud);

    if(dict[index] == NULL){
        dict[index] = newStudent;
    } else {
        Student* current = dict[index];
        while(current->next != NULL){
            current = current->next;
        }
        current->next = newStudent;
    }
}

void deleteDict(Dictionary dict, Student stud){
    int index = hash(stud);
    Student* current = dict[index], *prev = NULL;

    while(current != NULL && current->idNum != stud.idNum){
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Student not found.\n");
        return;
    }

    if (prev == NULL) {
        dict[index] = current->next;
    } else {
        prev->next = current->next;
    }
    free(current);
    printf("Student cleared.\n");

}

bool isMember(Dictionary dict, Student stud) {
    int index = hash(stud);
    Student* current = dict[index];

    while (current != NULL) {
        if(current->idNum == stud.idNum) {
            return true;
        }
        current = current->next;
    }
    return false;
}

void destroyDict(Dictionary *Dict){
    for(int i = 0; i < MAX; i++){
        Student* current = (*Dict)[i];
        while(current != NULL){
            Student* next = current->next;
            free(current);
            current = next;
        }
        (*Dict)[i] = NULL;
    }
}

void display(Dictionary dict){
    for(int i = 0; i < MAX; i++){
        printf("[%d]: ", i);
        if(dict[i] == NULL){
            printf("Empty.\n");
        } else {
            Student* current = dict[i];
            while(current != NULL){
            printf("(%s, %d, %s, %d) -> ", 
            current->name, current->age, current->course, current->idNum);
            current = current->next;
            }
            printf(" NULL\n");
        }
    }
}