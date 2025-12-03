#include <stdio.h>
#include <stdlib.h>

// ==== NODE STRUCTURE ====
typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node, *NodePTR;

// Treat the Tree as a pointer to NodePTR
typedef NodePTR Tree;

// ==== FUNCTION PROTOTYPES ====
void initializeTree(Tree* T);
NodePTR createNode(int data);
void insertTree(Tree* T, int data);
NodePTR deleteNode(NodePTR root, int data);
void deleteTree(Tree T);
NodePTR search(Tree T, int data);
void Preorder(Tree T);
void Inorder(Tree T);
void Postorder(Tree T);
// void BFS(Tree T);

int main (){
    Tree T;
    initializeTree(&T);

    insertTree(&T, 50);
    insertTree(&T, 30);
    insertTree(&T, 20);
    insertTree(&T, 40);
    insertTree(&T, 70);
    insertTree(&T, 60);
    insertTree(&T, 80);

    printf("===== Pre-Order =====\n");
    printf("Pre-Order: ");
    Preorder(T);
    printf("\n");

    printf("===== In-Order =====\n");
    printf("In-Order: ");
    Inorder(T);
    printf("\n");

    printf("===== Post-Order =====\n");
    printf("Post-Order: ");
    Postorder(T);
    printf("\n");

    T = deleteNode(T, 20);
    printf("After deleting 20, Inorder: ");
    Inorder(T);
    printf("\n");

    deleteTree(T);

    return 0;    
}

void initializeTree(Tree* T){
    (*T) = NULL;
}

NodePTR createNode(int data){
    NodePTR newNode = malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void insertTree(Tree* T, int data){
    if(*T == NULL){
        *T = createNode(data);
        return;
    }
    if(data < (*T)->data)
        insertTree(&(*T)->left, data);
    else if (data > (*T)->data)
        insertTree(&(*T)->right, data);
}

NodePTR deleteNode(NodePTR root, int data){
    if(root == NULL){
        return root;
    }

    if(data < root->data){
        root->left = deleteNode(root->left, data);
    } else if (data > root->data ){
        root->right = deleteNode(root->right, data);
    } else {
        // No left child
        if(root->left == NULL){
            NodePTR temp = root->right;
            free(root);
            return temp;
        // No right child
        } else if (root->right == NULL) {
            NodePTR temp = root->left;
            free(root);
            return temp;
        }
        // Two children
            NodePTR successor = root->right;
            while(successor->left != NULL) successor = successor->left;
            root->data = successor->data;
            root->right =  deleteNode(root->right, successor->data);
    }
    return root;
}

void deleteTree(Tree T){
    if (T != NULL) {
        deleteTree(T->left);
        deleteTree(T->right);
        free(T);
    }
}

NodePTR search(Tree T, int data){
    if(T == NULL || T->data == data){
        return T;
    }
    if(data < T->data)
        return search(T->left, data);
    else
        return search(T->right, data);
}

void Preorder(Tree T){
    if(T == NULL) return;
    printf("%d ", T->data);
    Preorder(T->left);
    Preorder(T->right);
}

void Inorder(Tree T){
    if(T == NULL) return;
    Inorder(T->left);
    printf("%d ", T->data);
    Inorder(T->right);
}

void Postorder(Tree T){
    if(T == NULL) return;
    Postorder(T->left);
    Postorder(T->right);
    printf("%d ", T->data);
}