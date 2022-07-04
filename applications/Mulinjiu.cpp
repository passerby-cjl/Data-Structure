//
// Created by Passerby on 2022/4/3.
//
#include "iostream"
using namespace std;
const int SIZE = 1e5+5;
void getForeFathers(int self, int father, int f[SIZE][20], int lastappear[SIZE], int prevappear[2*SIZE], int *deep, int origin[SIZE][2]){
    deep[self] = deep[father]+1;
    for(int i=1;(1<<i)<deep[self]; i++)
        f[self][i] = f[f[self][i-1]][i-1];
    for(int i=lastappear[self]; i; i=prevappear[i]){
        int temp = origin[(i-1)/2][(i%2)];
        if(temp==father) continue;
        f[temp][0] = self;
        getForeFathers(temp, self, f, lastappear, prevappear, deep, origin);
    }
}
int LCA(int x, int y, int *deep, int f[SIZE][20]){
    if(deep[x]>deep[y]){
        int temp=x;
        x=y;
        y=temp;
    }
    for(int i=19;i>=0;i--){
        if(deep[y]-(1<<i)>=deep[x])
            y=f[y][i];
    }
    if(x==y) return x;
    for(int i=19;i>=0;i--){
        if(f[y][i]!=f[x][i]){
            x=f[x][i];
            y=f[y][i];
        }
    }
    return f[x][0];
}
void Mulinjiu(){
    int T;
    scanf("%d", &T);
    for(int i=0;i<T;i++){
        int m,n;
        int f[SIZE][20]={0};
        int lastappear[SIZE]={0};
        int prevappear[2*SIZE];
        int deep[SIZE];
        int origin[SIZE][2];
        deep[0] = 0;
        scanf("%d%d", &n,&m);
        for(int j=0;j<n-1;j++){
            int x,y;
            scanf("%d%d", &x,&y);
            prevappear[2*j+1] = lastappear[x];
            prevappear[2*j+2] = lastappear[y];
            lastappear[x] = 2*j+1;
            lastappear[y] = 2*j+2;
            origin[j][0] = x;
            origin[j][1] = y;
        }
        getForeFathers(1, 0, f, lastappear, prevappear, deep, origin);
        for(int j=0;j<m;j++){
            int x1,y1,x2,y2;
            scanf("%d%d%d%d", &x1,&y1,&x2,&y2);
            int a= LCA(x1, y1, deep, f);
            int b= LCA(x2, y2, deep, f);
            if(deep[b]>deep[a]){
                swap(a,b);
                swap(x1,x2);
                swap(y1,y2);
            }
            if(LCA(a,x2,deep,f)==a|| LCA(a,y2,deep,f)==a)
                cout<<"YES\n";
            else cout<<"NO\n";
        }
    }
}