//
// Created by Passerby on 2022/4/30.
//
#include <cstring>
#include "iostream"
using namespace std;
const int SIZE = 5e6+11;
int f[SIZE];
int e0[SIZE][2];
inline int read() {
    char ch = getchar();
    int x = 0, fu = 1;
    while(ch < '0' || ch > '9')
    {
        if(ch == '-') fu = -1;
        ch = getchar();
    }
    while('0' <= ch && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * fu;
}
int Hash(int x, int *hsh){
    int result = x%SIZE;
    while(hsh[result]&&hsh[result]!=x) {
        result++;
        result%=SIZE;
    }
    hsh[result] = x;
    return result;
}
int find(int x){
    if(f[x]==x) return x;
    return f[x] = find(f[x]);
}
void Union(int x, int y, int *h){
    int fx = find(x), fy = find(y);
    if(fx==fy) return;
    if(h[fx]<h[fy]) f[fx] = fy;
    else if(h[fy]<h[fx]) f[fy] = fx;
    else{
        f[fx] = fy;
        h[fy]++;
    }
}

void AutoDebugger(){
    int t, n, p, q, e;
    t=read();
    for(int i=0;i<t;i++){
        int k=0;
        int h[SIZE]={0};
        int hsh[SIZE]={0};
        n=read();
        for(int j=0;j<SIZE;j++) f[j] = j;
        for(int j=0;j<n;j++){
            p=read();q=read();e=read();
            if(e) Union(Hash(p, hsh), Hash(q, hsh), h);
            else {
                e0[k][0] = Hash(p, hsh), e0[k][1] = Hash(q, hsh);
                k++;
            }
        }
        int j=0;
        for(;j<k;j++){
            if(find(e0[j][0])==find(e0[j][1])){
                printf("NO\n");
                break;
            }
        }
        if(j==k) printf("YES\n");
    }
}