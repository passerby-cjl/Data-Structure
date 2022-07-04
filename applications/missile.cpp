//
// Created by Passerby on 2022/5/23.
//
#include "iostream"
using namespace std;
const int SIZE=2000;
int a[SIZE];
int dp[SIZE];
bool head[SIZE];
void missle(){
    int n;
    scanf("%d", &n);
    for(int i=1;i<=n;i++) {
        scanf("%d", a+i);
        dp[i]=1;
    }
    int result2=0;
    for(int i=n;i>0;i--){
        int M=0;
        for(int j=i+1;j<=n;j++){
            if(a[j]>a[i]) continue;
            M=max(M,dp[j]);
        }
        dp[i]=M+1;
        int temp=0,tempj;
        for(int j=i+1;j<=n;j++){
            if(head[j]&&a[j]<=a[i]&&a[j]>=temp){
                temp=a[j];
                tempj=j;
            }
        }
        if(temp) head[tempj] = false;
        else result2++;
        head[i] = true;
    }
    int result=0;
    for(int i=1;i<=n;i++){
        result=max(result, dp[i]);
    }
    printf("%d\n%d", result,result2);
}