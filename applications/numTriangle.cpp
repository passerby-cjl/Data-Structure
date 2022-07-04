//
// Created by Passerby on 2022/5/23.
//
#include "iostream"
using namespace std;
const int SIZE = 1e3+5;
int f[SIZE];
void numTriangle(){
    int n,a;
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        for(int j=i;j>=1;j--){
            scanf("%d",&a);
            f[j]=max(f[j-1], f[j])+a;
        }
    }
    int result=0;
    for(int i=1;i<=n;i++){
        result=max(result,f[i]);
    }
    printf("%d", result);
}