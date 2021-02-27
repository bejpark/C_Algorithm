//
//  main.c
//  algorithm
//
//  Created by BeJ Park on 2020/04/14.
//  Copyright © 2020 BeJ Park. All rights reserved.
//

#include <stdio.h>
#include <string.h>

int main() {
    while(1)//repeat
    {    char pdstr[100];
        printf("Type In Your Word : ");
        scanf("%s",pdstr);
        int len = strlen(pdstr);//length of the word
        int goal = 1;//starts at 1, if it is not Palindrome turn to 0
        for(int i=0;i<(len/2);i++){
            if(pdstr[i]!=pdstr[len-i-1])//word not same -> goal=0
                goal = 0;
        }
        if(goal == 1)
            printf("%s is Palindrome\n",pdstr);
        else//goal==0
            printf("%s is not Palindrome\n",pdstr);
    }
}
