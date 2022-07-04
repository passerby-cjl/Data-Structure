//
// Created by Passerby on 2022/3/21.
//
#include "iostream"
using namespace std;
long long getScheme(long long width, long long low, long long high){
    long long a=0,b=0;
    a = width*(width+1)*(width+2)/6;
    b=(low+high+1)*(high-low)/2;
    return a*b;
}
void undestroyedFarm(){
    int n,m;
    long long result=0;
    cin>>n>>m;
    int **farm = new int *[n+1];
    for(int i=0;i<n;i++){
        farm[i] = new int[m+1];
        for(int j=0;j<m;j++){
            char f;
            cin>>f;
            if(!i) farm[i][j] = (f=='.');
            else farm[i][j] = (f=='.') * (farm[i-1][j]+1);
        }
    }
    int **stack = new int*[m+1];
    for(int j=0;j<=m;j++) stack[j] = new int[2];
    for(int i=0;i<n;i++){
        int top = 0;
        stack[top][0] = 0;
        stack[top][1] = 1;
        for(int j=0;j<=m;j++){
            if(j==m) farm[i][j] = 0;
            while(top>0&&farm[i][j]<stack[top][0]){
                if(farm[i][j]>stack[top-1][0]) {
                    result += getScheme(stack[top][1], farm[i][j], stack[top][0]);
                    stack[top][0] = farm[i][j];
                }else if(farm[i][j]==stack[top-1][0]){
                    result += getScheme(stack[top][1], farm[i][j], stack[top][0]);
                    top--;
                    stack[top][1] += stack[top+1][1];
                }else{
                    result += getScheme(stack[top][1], stack[top-1][0], stack[top][0]);
                    top--;
                    stack[top][1] += stack[top+1][1];
                }
            }
            if(farm[i][j] == stack[top][0])
                stack[top][1]++;
            else{
                stack[++top][0] = farm[i][j];
                stack[top][1] = 1;
            }
        }
    }
    cout<<result;
}