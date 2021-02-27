//
//  main.c
//  Assignment5_20160392
//
//  Created by BeJ Park on 2020/06/10.
//  Copyright © 2020 BeJ Park. All rights reserved.
//

#include <stdio.h>
int arr[100];
int n = 6;
int w[6] = {6, 10, 3, 5, 1, 3};
int v[6] = {60, 20, 12, 80, 30, 60};
int MAX_WEIGHT = 16;
 

int fibonacci(int n){
    if(0<n && n<=2)
        return 1;
    if(arr[n]!=0)
        return arr[n];
    
    arr[n] = fibonacci(n-1)+fibonacci(n-2);
    return arr[n];
}

int matrixChain(int p[], int i, int j){
    if(i==j)
        return 0;
    int k;
    int num;
    int min = 9999999;
    
    for(k=i;k<j;k++){
        num=matrixChain(p, i, k)+matrixChain(p, k+1, j)+p[i-1]*p[k]*p[j];
        if(num<min)
            min=num;
    }
    return min;
}

void matrixMult(){
    int mA[5][3] = {
        {1, 2, 1},
        {1, 2, 1},
        {1, 2, 1},
        {1, 2, 1},
        {1, 2, 1}
    };
    int mB[3][7] = {
        {1, 2, 1, 1, 1, 1, 1},
        {1, 1, 2, 1, 1, 1, 1},
        {1, 1, 1, 2, 1, 1, 1}
    };
    int mC[7][10] = {
        {1, 1, 1, 2, 1, 2, 1, 1, 1, 1},
        {1, 1, 1, 1, 2, 1, 2, 1, 1, 1},
        {1, 1, 1, 1, 1, 2, 1, 2, 1, 1},
        {1, 1, 1, 1, 1, 1, 2, 1, 2, 1}
    };
    int mSum1[5][7]={0};
    int mSum2[5][10]={0};

    int i, j, k;
    int sum;
    for(i=0;i<5;i++)
    {
        for(j=0;j<7;j++){
            sum = 0;
            for(k=0;k<3;k++){
                sum += mA[i][k]*mB[k][j];
            }
            mSum1[i][j] = sum;
        }
    }
    
    for(i=0;i<5;i++)
    {
        for(j=0;j<10;j++){
            sum = 0;
            for(k=0;k<7;k++){
                sum += mSum1[i][k]*mC[k][j];
            }
            mSum2[i][j] = sum;
        }
    }
    
    for(i=0;i<5;i++){
        for(j=0;j<10;j++){
            printf("%d\t",mSum2[i][j]);
        }
        printf("\n");
    }
   
}

void knapsack() {
    printf("<Fractional Knapsack Problem> Max Weight %d\n",MAX_WEIGHT);
    
    float totalVal;
    int i, max;
    int used[6];
    
    int leftW = MAX_WEIGHT;
 
    for (i = 0; i < n; ++i)
        used[i] = 0;
 
    while (leftW > 0) {
        max = -1;//make 'max' new
        for (i = 0; i < n; ++i)
            if ((used[i] == 0) && ((max == -1) || ((float)v[i]/w[i] > (float)v[max]/w[max])))//Max Value per Weight
                max = i;
 
        used[max] = 1;
        leftW -= w[max];
        
        if (leftW >= 0){
            printf("Added item %d (Value : %d, Weight : %d).  %d Weight Left.\n", max + 1, v[max], w[max], leftW);
            totalVal += v[max];
        }
        else {
            printf("Added %.1f%% of item %d (Value : %d, Weight : %d).\n", ((1 + (float)leftW/w[max]) * 100), max + 1, v[max], w[max]);
            totalVal += (1 + (float)leftW/w[max]) * v[max];//fractional knapsack
        }
    }
    printf("Total Value : %.1f$.\n", totalVal);
}
 


int main() {
    //Fibonacci
    printf("<Fibonacci> case n = 5 : %d\n", fibonacci(5));
    printf("<Fibonacci> case n = 10 : %d\n\n", fibonacci(10));
    
    //Matrix-Chain Multiplication
    printf("<Matrix-Chain> Matrix After Multiplication : \n");
    matrixMult();
    int mtx[4]={5,3,7,10};
   printf("<Matrix-Chain> Minimum number of Multiplication : %d\n\n", matrixChain(mtx, 1, 3));
    
    //Fractional Knapsack problem
    knapsack();
    
    return 0;
}
