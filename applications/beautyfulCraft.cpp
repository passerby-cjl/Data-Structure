//
// Created by Passerby on 2022/5/29.
//
#include "iostream"
#include <algorithm>
using namespace std;
const int SIZE = 1e5+5;
int stack[SIZE];
int h[SIZE];
int t[SIZE];
int L[SIZE];
int R[SIZE];
void beautifulCraft(){
    int n;
    scanf("%d", &n);
    for(int i=1;i<=n;i++) scanf("%d", h+i);
    for(int i=1;i<=n;i++){

    }
    int top=0;
    for(int i=n;i>0;i--){
        while(top&&h[stack[top]]<=h[i]) top--;
        R[i]=R[stack[top]]+1;
        stack[++top]=i;
    }
    top=0;
    R[0]=-1;
    for(int i=n;i>0;i--){
        while(top&&h[stack[top]]<=h[i]) top--;
        R[i]=R[stack[top]]+1;
        stack[++top]=i;
    }
    int result=0;
    for(int i=1;i<=n;i++){
        if(L[i]>R[i]*2||R[i]>L[i]*2) result++;
    }
    printf("%d", result);
}
int main(){
    beautifulCraft();
}