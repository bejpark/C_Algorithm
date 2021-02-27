//
//  main.c
//  exercise
//
//  Created by BeJ Park on 2020/05/05.
//  Copyright © 2020 BeJ Park. All rights reserved.
//
//2020-1 서강대컴공과제
#include <stdio.h>
#include <math.h>

double fixDemical(double n){//실수 n을 소수점 세자리까지 나타내게 하는 함수
    int m = (int)(1000*n);//1000을 곱한 후 정수형변환(소수점 네자리까지 정수로 올라오고 나머지는 버려짐)
    double k = m;//실수형으로 재변환
    k = k/1000;//다시 1000을 나눠줌으로 소수점 세자리까지만 남은 k로 return
    return k;
}

double solveDistance(double a, double b, double c, double x, double y){ //직선과 원과의 거리 d를 구하는 함수
    double distance;
    distance = (a*x+b*y+c)/sqrt(pow(a,2)+pow(b,2));
    distance = fixDemical(distance);
    return distance;
}
double solveDisctiminant(double a, double b, double c){ //근의 개수를 구하는 판별식 b^2-4ac을 구하는 함수
    double discriminant;
    discriminant = b*b - 4.0*a*c;
    discriminant = fixDemical(discriminant);
    return discriminant;
}


int main() {
    double a, b, cx, cy;
    double r;
    double d, dis;//d:직선과 점 사이 거리, dis:판별식 b^2-4ac
    double x1, x2, y1, y2;// 근들의 좌표
    printf("직선의 함수식을 입력하기 바랍니다.\n");
    printf("y = ax + b\n");
    printf("기울기 a = ");
    scanf("%lf", &a);
    printf("교차점 b = ");
    scanf("%lf", &b);//y=ax+b -> ax-y+b=0 이므로 Discriminant의 a=a, b=-1, c=b
    
    printf("원의 함수식을 입력하기 바랍니다.\n");
    printf("(x - cx)^2 + (y - cy)^2 = r^2\n");
    printf("cx = ");
    scanf("%lf", &cx);
    printf("cy = ");
    scanf("%lf", &cy);
    printf("반지름 r = ");
    scanf("%lf", &r);
    
    
    d = solveDistance(a, -1, b, cx, cy);//y=ax+b -> ax-y+b=0 이므로 solveDistance의 a=a, b=-1, c=b
    dis = solveDisctiminant(a*a+1, 2*a*(b-cy)-2*cx, cx*cx+pow(b-cy,2)-r*r);//직선과 원의 방정식을 연립한 후 정리했을 때의 계수들
    x1 = (-(2*a*(b-cy)-2*cx)-sqrt(dis))/(2*(a*a+1));//근의 공식을 사용함
    x2 = (-(2*a*(b-cy)-2*cx)+sqrt(dis))/(2*(a*a+1));
    y1 = a*x1 + b;
    y2 = a*x2 + b;
    if(d<fixDemical(r)){//r도 소수점 3자리까지 표현해서 비교
        printf("두 함수에는 두 개의 교차점이 있습니다.\n");
        printf("(%0.3f, %0.3f), (%0.3f, %0.3f)\n", x1, y1, x2, y2);
    }
    else if (d==fixDemical(r)){
        printf("직선 라인은 원에 접합니다.\n");
        printf("(%0.3f, %0.3f)\n", x2, y2);
        printf("%lf",dis);
    }
    else//d>r
    {
        printf("두 함수의 교차점이 없습니다.\n");
    }
    
    
    
    return 0;
}

