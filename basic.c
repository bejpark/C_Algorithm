//
//  main.c
//  ex2
//
//  Created by BeJ Park on 2020/04/15.
//  Copyright © 2020 BeJ Park. All rights reserved.
//
#include <stdio.h>

int main(void)
{
    while(1){
        int start = 1;
        int n;
        int k=0;
        printf("the number : ");
        scanf("%d",&n);
        
        while(1)
        {
            start=start*2;
            if(start>n)
                break;
            k++;
        }
        printf("largest k is %d\n", k);
    }
    return 0;
}

