#include <stdio.h>

#define SIZE 10

//build max heap
//swap root and last element
//reduce iteration limit
//perform heapify
//repeat 
void heapSort(int a[], int tempSize){

    int ndx,tempSwap;

    tempSwap = a[0];
    a[0] = a[tempSize-1];
    a[tempSize-1] = tempSwap;

    tempSize--;
    ndx = tempSize;

    while(2 * ndx + 1 <= SIZE || 2 * ndx <= SIZE){
        // if(a[ndx] < a[2 * ndx + 1] || a[ndx] < a[2 * ndx + 1]){
        //     if(a[2 * ndx + 1] < a[2 * ndx]){
        //         tempSwap = a[ndx];
        //         a[ndx] = a[2 * ndx];
        //         a[2 * ndx] = tempSwap;
        //     }
        //     else{
        //         tempSwap = a[ndx];
        //         a[ndx] = a[2 * ndx + 1];
        //         a[2 * ndx + 1] = tempSwap;
        //     }
        // }
        ndx--;
    }

    //find first parent node, starting from last index
    if(tempSize != 0) heapSort(a, tempSize);

    return;
    
}
int main(){

    int a[SIZE] = {313,32,100,24,19,67,8,17,16,10};

    heapSort(a, SIZE);

    return 0;
}