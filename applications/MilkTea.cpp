//
// Created by Passerby on 2022/3/30.
//
#include "iostream"
using namespace std;
const int SIZE = 1e5+1;
const int LAYOUR = 17;
int f[SIZE][LAYOUR];
int origin[SIZE][3];
int lastappear[2*SIZE];
int prevappear[2*SIZE];
int deep[SIZE];
int minuscups[SIZE];
void getForefathers(int self, int father){
    deep[self] = deep[f[self][0]]+1;
    for(int i=1;(1<<i) < deep[self]; i++) {
        f[self][i] = f[f[self][i - 1]][i - 1];
    }
    for(int index=lastappear[self];index;index = prevappear[index]) {
        int temp,dis;
        if(index%2) {
            temp=origin[(index-1)/2][1];
        }else{
            temp=origin[(index-2)/2][0];
        }
        if (temp == father) continue;
        f[temp][0] = self;
        getForefathers(temp, self);
    }
}
int addup(int &maximum, int self, int father){
    int result=minuscups[self];
    for(int index=lastappear[self];index;index = prevappear[index]) {
        int temp;
        if(index%2)
            temp=origin[(index-1)/2][1];
        else
            temp=origin[(index-2)/2][0];
        if (temp == father) continue;
        result+= addup(maximum, temp, self);
    }
    maximum = max(result, maximum);
    return result;
}
void MilkTea(){
    int n,K;
    cin>>n>>K;
    int _2px[LAYOUR];
    _2px[0] = 1;
    for(int i=1;i<LAYOUR;i++) _2px[i]=_2px[i-1]<<1;
    int a,b,c;
    for(int i=0;i<n-1;i++){
        scanf("%d%d%d" ,&a,&b,&c);
        prevappear[2*i+1] = lastappear[a];
        prevappear[2*i+2] = lastappear[b];
        lastappear[a] = 2*i+1;
        lastappear[b] = 2*i+2;
        origin[i][0]=a;
        origin[i][1]=b;
    }
    f[1][0] = 0;
    getForefathers(1, 0);
    for(int s=0;s<K;s++){
        int x,y;
        scanf("%d%d", &x,&y);
        minuscups[x] ++;
        minuscups[y] ++;
        if(deep[x]>deep[y]) {
            int temp = x;
            x = y;
            y = temp;
        }
        int temp = deep[y]-deep[x];
        for(int i=LAYOUR-1;i>=0;i--){
            if(temp/_2px[i]){
                y = f[y][i];
                temp -= _2px[i];
            }
        }
        if(x!=y){
            for(int i=LAYOUR-1;i>=0;i--){
                if(f[x][i]!=f[y][i]){
                    x=f[x][i];
                    y=f[y][i];
                }
            }
            x=f[x][0];
        }
        minuscups[x] --;
        minuscups[f[x][0]] --;
    }
    int maximun=0;
    addup(maximun, 1, 0);
    cout<<maximun;
}