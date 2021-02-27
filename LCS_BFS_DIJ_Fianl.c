//
//  main.c
//  FinalProject
//
//  Created by BeJ Park on 2020/06/22.
//  Copyright © 2020 BeJ Park. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char LCS_X[] = "0ABCBDAB";
char LCS_Y[] = "0BDCABA";
int LCS_c[8][7];
int LCS_b[8][7];
int LCS_m,LCS_n;
/*---------------------------------*/
int BFS_d[8];
int BFS_pi[8];
int BFS_color[8];
char BFS_PI[8];
char BFS_vertex[8] = "rstuvwxy";
int BFS_G[8][8]={
    {0, 1, 0, 0, 1, 0, 0, 0},
    {1, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 0, 1, 0, 1, 1, 0},
    {0, 0, 1, 0, 0, 0, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 1, 0, 0, 0, 1, 0},
    {0, 0, 1, 1, 0, 1, 0, 1},
    {0, 0, 0, 1, 0, 0, 1, 0}
};
/*---------------------------------*/
int DIJ_d[5];
int DIJ_pi[5];
int DIJ_G[5][5]={
    {0, 3, 0, 5, 0},
    {0, 0, 6, 2, 0},
    {0, 0, 0, 0, 2},
    {0, 1, 4, 0, 6},
    {3, 0, 7, 0, 0}
};
int DIJ_S[5]={0};
int DIJ_path[5]={100,100,100,100,100};
char DIJ_PATH[5];

/*---------------------------------*/
typedef struct Node{
    int data;
    struct Node *next;
}Node;

typedef struct Queue{
    Node *front;
    Node *rear;
    int num;
}Queue;
Queue Q;
void InitQueue(Queue *queue){
    queue->front = queue->rear = NULL;
    queue->num = 0;
}

int IsEmpty(Queue *queue){
    return queue->num == 0;
}

void Enqueue(Queue *queue, int data){
    Node *n = (Node*)malloc(sizeof(Node));
    n->data = data;
    n->next = NULL;
    
    if(IsEmpty(queue))
        queue->front=n;
    else
        queue->rear->next = n;
    
    queue->rear = n;
    queue->num++;
}

int Dequeue(Queue *queue){
    int x = 0;
    Node *now;
    if(IsEmpty(queue))
        return x;
    
    now = queue->front;
    x = now->data;
    queue->front = now->next;
    queue->num--;
    
    return x;
}
/*---------------------------------*/
void LCS_LENGTH(char x[], char y[]){
    LCS_m = strlen(x)-1;//7
    LCS_n = strlen(y)-1;//6
    for(int i=0;i<=LCS_m;i++)
        LCS_c[i][0] = 0;
    for(int j=0;j<=LCS_n;j++)
        LCS_c[0][j] = 0;
    for(int i=1;i<=LCS_m;i++)
        for(int j=1;j<=LCS_n;j++){
            if(x[i]==y[j]){
                LCS_c[i][j] = LCS_c[i-1][j-1] + 1;
                LCS_b[i][j] = 0;//Left-Up
                
            }
            else if(LCS_c[i-1][j] >= LCS_c[i][j-1]){
                LCS_c[i][j] = LCS_c[i-1][j];
                LCS_b[i][j] = 1;//Up
            }
            else{
                LCS_c[i][j] = LCS_c[i][j-1];
                LCS_b[i][j] = 2;//Left
            }
        }
}

void LCS_PRINT(int b[][7], char x[], int i, int j){
    if(i==0 || j==0)
        return;
    if(b[i][j] == 0){
        LCS_PRINT(b, LCS_X, i-1, j-1);
        printf("%c ", x[i]);
    }
    else if(b[i][j] == 1)
        LCS_PRINT(b, LCS_X, i-1, j);
    else LCS_PRINT(b, LCS_X, i, j-1);
}
/*---------------------------------*/
void BFS(int Graph[][8], int s){
    int u;
    InitQueue(&Q);
    for(int i=0;i<8;i++){
        BFS_color[i] = 0;
        BFS_d[i] = 10000;
        BFS_pi[i] = -1;
    }
    BFS_color[s] = 1;
    BFS_d[s] = 0;
    BFS_pi[s] = -1;
    Enqueue(&Q, s);
    while(!IsEmpty(&Q)){
        u = Dequeue(&Q);
        for(int v=0;v<8;v++){
            if(Graph[u][v]==1){
                if(BFS_color[v]==0){
                    BFS_color[v] = 1;
                    BFS_d[v] = BFS_d[u] + 1;
                    BFS_pi[v] = u;
                    Enqueue(&Q, v);
                }
            }
        }
        BFS_color[u] = 2;
    }
}

void INT_TO_CHAR(int INT[],char CHAR[]){
    for(int i=0;i<8;i++){
        switch(INT[i]){
            case 0: CHAR[i] = 'r'; break;
            case 1: CHAR[i] = 's'; break;
            case 2: CHAR[i] = 't'; break;
            case 3: CHAR[i] = 'u'; break;
            case 4: CHAR[i] = 'v'; break;
            case 5: CHAR[i] = 'w'; break;
            case 6: CHAR[i] = 'x'; break;
            case 7: CHAR[i] = 'y'; break;
            case -1: CHAR[i] = 'N'; break;
        }
    }
}
/*---------------------------------*/
void RELAX(int u, int v, int Graph[][5]){
    if((DIJ_d[v] > DIJ_d[u] + Graph[u][v]) && (Graph[u][v]!=0)){
        DIJ_d[v] = DIJ_d[u] + Graph[u][v];
        DIJ_pi[v] = u;
    }
}
void DIJKSTRA(int Graph[][5], int s){

    int u = 0;
    int min;
    for(int i=0;i<5;i++){
        DIJ_d[i] = 10000;
        DIJ_pi[i] = -1;
    }
    
    DIJ_d[s] = 0;
    DIJ_S[u] = 1;
    for(int i=0;i<5;i++){
        min = 1000;
         for(int j=0;j<5;j++){
             if(min > Graph[u][j] && Graph[u][j]!=0){
                 min = Graph[u][j];
                 u = i;
             }
         }
         DIJ_S[u] = 1;
         for(int v=1;v<5;v++)
             if(Graph[u][v]!=0)
                 RELAX(u, v, DIJ_G);
     }
}

void INT_TO_CHAR2(int INT[],char CHAR[]){
    for(int i=0;i<5;i++){
        if(INT[i]!=100){
            switch(INT[i]){
                case 0: CHAR[i] = 's'; break;
                case 1: CHAR[i] = 't'; break;
                case 2: CHAR[i] = 'x'; break;
                case 3: CHAR[i] = 'y'; break;
                case 4: CHAR[i] = 'z'; break;
            }
        }
    }
}

void DIJ_PRINT_PATH(int INT[], char CHAR[], int n, int i){
    while(1){
        INT[i] = DIJ_pi[n];
        n = DIJ_pi[n];
        if(INT[i]==0)
            break;
        i++;
    }
    
    INT_TO_CHAR2(INT, CHAR);
    for(int j=0;j<=i;j++)
        printf("-> %c ",CHAR[j]);
}


/*---------------------------------*/

int main() {
    printf("++++++++++ (P1) LCS ++++++++++\n");
    printf("X= < A,B,C,B,D,A,B >, Y= < B,D,C,A,B,A >\n");
    printf("LCS of X and Y is : ");
    LCS_LENGTH(LCS_X, LCS_Y);
    LCS_PRINT(LCS_b, LCS_X, 7, 6);
    printf("\n\n");
   
    printf("++++++++++ (P2) BFS ++++++++++\n");
    BFS(BFS_G, 1);
    INT_TO_CHAR(BFS_pi, BFS_PI);
    printf("<Vertex>\t<d>\t\t<PI>\n");
    for(int i=0;i<8;i++){
        printf("%c \t\t\t %d \t\t %c \t",BFS_vertex[i], BFS_d[i], BFS_PI[i]);
        printf("\n");
    }
    printf("\n");
    
    printf("++++++++++ (P4) Dijkstra ++++++++++\n");
    DIJKSTRA(DIJ_G, 0);//s:0 t:1 x:2 y:3 z:4
    printf("Shortest Past from the source vertex s to y is : y ");
    DIJ_PRINT_PATH(DIJ_path, DIJ_PATH, 3, 0);
    printf("\nThe Corresponding total cost is %d\n",DIJ_d[3]);
    printf("Shortest Past from the source vertex s to z is : z ");
    DIJ_PRINT_PATH(DIJ_path, DIJ_PATH, 4, 0);
    printf("\nThe Corresponding total cost is %d\n",DIJ_d[4]);
    
    return 0;
}
