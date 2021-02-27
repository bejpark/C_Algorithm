//
//  main.c
//  MidTerm
//
//  Created by BeJ Park on 2020/05/05.
//  Copyright © 2020 BeJ Park. All rights reserved.
//

#include <stdio.h>
#include <time.h>
#define ArraySize 10//10 or 100 or 1000

void setArray(int arr[], int n){//create size n array in decreasing order
    for(int i=0;i<n;i++)
        arr[i] = n-i;
}

void bubbleSort(int arr[], int n){
    int i, j, k;
    for(i=0;i<n-1;i++)
        for(j=0;j<n-1;j++)
            if(arr[j]>arr[j+1]){
                k = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = k;
            }
}

void insertionSort(int arr[], int n){
    int i, j, k;
    for(i=1;i<n;i++){
        k = arr[i];
        j = i - 1;
        while(j>=0 && arr[j]>k){
            arr[j+1] = arr[j];
            j = j - 1;
        }
        arr[j+1] = k;
    }
}

void merge(int arr[], int start, int middle, int end){
    int i = start;
    int j = middle+1;
    int k = start;
    int sortarr[ArraySize];

    while(i<=middle && j<=end){
        if(arr[i]<=arr[j]){
            sortarr[k] = arr[i];
            i++;
        }else{
            sortarr[k] = arr[j];
            j++;
        }
        k++;
    }
    while(i<=middle){
        sortarr[k] = arr[i];
        k++;
        i++;
    }
    while(j<=end){
        sortarr[k] = arr[j];
        k++;
        j++;
    }
    for(int n=start;n<=end;n++)
        arr[n]=sortarr[n];
}
void mergeSort(int arr[], int start, int end){
    int m;
    if(start < end){
        m = (start+end)/2;
        mergeSort(arr, start, m);
        mergeSort(arr, m+1, end);
        merge(arr, start, m, end);
    }
}

int quick(int arr[], int start, int end){
    int pivot = arr[start];
    int i = start;
    int temp;
    for(int j=start+1;j<=end;j++){
        if(arr[j]<=pivot){
            i++;
            temp = arr[j];
            arr[j] = arr[i];
            arr[i] = temp;
        }
    }
    temp = arr[start];
    arr[start] = arr[i];
    arr[i] = temp;

    return i;
}
void quickSort(int arr[], int start, int end){
    if(start<end){
        int m = quick(arr, start, end);
        quickSort(arr, start, m-1);
        quickSort(arr, m+1, end);
    }
}

void radix(int arr[], int n, int k) {
    int sortarr[ArraySize];
    int i;
    int count[10] = {0};//use counting sort

    for (i=0;i<n;i++)
        count[(arr[i] / k) % 10]++;
    for (i=1;i<10;i++)
        count[i] += count[i - 1];
    for (i=n-1;i>=0;i--) {
        sortarr[count[(arr[i] / k) % 10] - 1] = arr[i];
        count[(arr[i] / k) % 10]--;
    }
    for (i=0;i<n;i++)
        arr[i] = sortarr[i];
}
void radixSort(int arr[], int n) {
    int max = arr[0];
    for (int i=1;i<n;i++){
        if (arr[i] > max)
            max = arr[i];
    }
    for (int i=1;max/i>0;i*=10)
        radix(arr, n, i);
}

void bucketSort1(int arr[], int n){//case n=10
    int i;
    int j;
    int bucket[5][2] = {0};//create to divide 1~2 3~4 5~6 ... in bucket
    for(i=0;i<n;i++){
        if(bucket[(arr[i]-1)/2][0]==0)//1~10 -> (0~9)/2 change to divide easily
            bucket[(arr[i]-1)/2][0]=arr[i];
        else if(bucket[(arr[i]-1)/2][0]!=0)//if there is not empty at bucket[x][0], fill at bucket[x][1]
            bucket[(arr[i]-1)/2][1]=arr[i];
        
    }
    for(i=0;i<5;i++)
        bubbleSort(bucket[i], 2);//use any stable sort at single bucket
        for(j=0;j<2;j++){
            arr[i*2+j]=bucket[i][j];
        }
}
void bucketSort2(int arr[], int n){//case n=100, similar idea as bucketSort1
    int i;
    int j;
    int k = 0;
    int bucket[10][10] = {0};
    int temp[10] = {0};//temp[i] is for the count number of data at bucket[i][]
    for(i=0;i<n;i++){
        k = (arr[i]-1)/10;
        bucket[(arr[i]-1)/10][temp[k]]=arr[i];//1~100 -> (0~99)/10
        temp[k]++;//there is plus one element at bucket[k][]
    }
    for(int l=0;l<10;l++)
        bubbleSort(bucket[l],10);
    for(i=0;i<10;i++)
        for(j=0;j<10;j++){
            arr[i*10+j]=bucket[i][j];
        }
}
void bucketSort3(int arr[], int n){//case n=1000, same idea as bucketSort2
    int i;
    int j;
    int k = 0;
    int bucket[20][50] = {0};
    int temp[50] = {0};
    for(i=0;i<n;i++){
        k = (arr[i]-1)/50;
        bucket[(arr[i]-1)/50][temp[k]]=arr[i];
        temp[k]++;
    }
    for(int l=0;l<20;l++)
        bubbleSort(bucket[l],50);
    for(i=0;i<20;i++)
        for(j=0;j<50;j++){
            arr[i*50+j]=bucket[i][j];
        }
}


int main() {
    int i;
    int array[ArraySize];
    setArray(array, ArraySize);
    printf("Before Sorting :\n");
       for(i=0;i<ArraySize;i++){
           printf("%4d ", array[i]);
       }
    printf("\n");
    clock_t start = clock();
    //bubbleSort(array,ArraySize); printf("+++++++++++ using BubbleSort (size : %d) +++++++++++\n",ArraySize);
    //insertionSort(array, ArraySize); printf("+++++++++++ using InsertionSort (size : %d) +++++++++++\n",ArraySize);
    //mergeSort(array, 0, ArraySize-1); printf("+++++++++++ using MergeSort (size : %d) +++++++++++\n",ArraySize);
    //quickSort(array, 0, ArraySize-1); printf("+++++++++++ using QuickSort (size : %d) +++++++++++\n",ArraySize);
    //radixSort(array, ArraySize); printf("+++++++++++ using RadixSort (size : %d) +++++++++++\n",ArraySize);
    //bucketSort1(array, ArraySize); printf("+++++++++++ using BucketSort (size : 10) +++++++++++\n");//case n=10
    //bucketSort2(array, ArraySize); printf("+++++++++++ using BucketSort (size : 100) +++++++++++\n");//case n=100
    //bucketSort3(array, ArraySize); printf("+++++++++++ using BucketSort (size : 1000) +++++++++++\n");//case n=1000
    clock_t end = clock();
    printf("After Sorting :\n");
    for(i=0;i<ArraySize;i++){
        printf("%4d ", array[i]);
    }
    printf("\n");
    printf("실행 시간 : %lf\n", (double)(end - start)/CLOCKS_PER_SEC);
    return 0;
}
