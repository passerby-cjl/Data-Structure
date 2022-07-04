//
// Created by Passerby on 2022/5/23.
//
#include "iostream"
using namespace std;
const int SIZE = 205;
int dp[SIZE][SIZE];
int a[SIZE];
void energyNecklace(){
    int n, result=0;
    scanf("%d0", &n);
    for(int i=1;i<=n;i++) {
        scanf("%d", a+i);
        a[n+i]=a[i];
    }
    for(int j=2;j<=n;j++){
        for(int i=1;i+j-1<2*n;i++){
            for(int k=i;k<i+j-1;k++)
                dp[i][i+j-1]=max(dp[i][i+j-1], dp[i][k]+dp[k+1][i+j-1]+a[i]*a[k+1]*a[i+j]);
        }
    }
    for(int i=1;i<=n;i++) result=max(result, dp[i][i+n-1]);
    printf("%d", result);
}