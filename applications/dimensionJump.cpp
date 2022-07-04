//
// Created by Passerby on 2022/4/17.
//
#include "iostream"
using namespace std;
const int SIZE = 3000;
int farm_o[SIZE][SIZE];
int farm_e[SIZE][SIZE];
int m, n;
inline int read() {                 // read in a int and return
    char ch = getchar();
    int x = 0, f = 1;
    while(ch < '0' || ch > '9')
    {
        if(ch == '-') f = -1;
        ch = getchar();
    }
    while('0' <= ch && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
void add(int x, int y, int d){
    if((x+y)%2){
        int tempx = (x+y)/2;
        int tempy = m/2+(y-x+1)/2;
        for(int i=tempx;i<=(m+n-1)/2;i+=i&-i)
            for(int j=tempy;j<=m/2+n/2;j+=j&-j)
                farm_o[i][j]+=d;
    }else{
        int tempx = (x+y)/2;
        int tempy = (m+1)/2+(y-x)/2;
        for(int i=tempx;i<=(m+n)/2;i+=i&-i)
            for(int j=tempy;j<=(m+1)/2+(n-1)/2;j+=j&-j)
                farm_e[i][j]+=d;
    }
}
int ask(int x, int y){
    int value = 0;
    if((x+y)%2) {
        int tempx = (x + y) / 2;
        int tempy = m / 2 + (y - x + 1) / 2;
        for(int i=tempx;i>0;i-=i&-i)
            for(int j=tempy;j>0;j-=j&-j)
                value+=farm_o[i][j];
        return value;
    }else {
        int tempx = (x + y) / 2;
        int tempy = (m + 1) / 2 + (y - x) / 2;
        for(int i=tempx;i>0;i-=i&-i)
            for(int j=tempy;j>0;j-=j&-j)
                value += farm_e[i][j];
        return value;
    }
}
void dimensionJump(){
    m=read(), n=read();
    for(int j=1;j<=n;j++)
        for(int i=1;i<=m;i++)
            add(i, j, read());
    int opt, x, y, d;
    while(cin>>opt){
        x=read(),y=read(),d=read();
        if(opt==1)
            add(x, y, d);
        if(opt==2){
            int tot1 = ask(x, y+d);
            int left1 = ask(x-d-1, y-1);
            int top1 = ask(x+d+1, y-1);
            int leftop1 = ask(x, y-d-2);
            int tot2 = ask(x, y+d-1);
            int left2 = ask(x-d, y-1);
            int top2 = ask(x+d, y-1);
            int leftop2 = ask(x, y-d-1);
            int result = tot1+tot2-left1-left2-top1-top2+leftop1+leftop2;
            printf("%d\n", result);
        }
    }
}