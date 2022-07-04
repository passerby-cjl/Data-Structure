//
// Created by Passerby on 2022/4/25.
//
#include "iostream"
using namespace std;
const int SIZE = 2e5+5;
int f1[SIZE];
int f2[SIZE];
int num1[SIZE];
int num2[SIZE];
int h[SIZE];
int find(int x, int*f){
    if(x==f[x]) return x;
    return f[x] = find(f[x], f);
}
void Union(int x, int y, int *f, int *num){
    int fx = find(x, f),fy = find(y, f);
    if(fx==fy) return;
    if(h[fx]<h[fy]) {
        f[fx] = fy;
        num[fy] += num[fx];
    }
    else if(h[fy]<h[fx]) {
        f[fy] = fx;
        num[fx] += num[fy];
    }
    else{
        f[fx] = fy;
        num[fy] += num[fx];
        h[fy]++;
    }
}
void goodRelation(){
    int n, m, p, q;
    scanf("%d%d%d%d", &n, &m, &p, &q);
    int x, y;
    for(int i=1;i<=n;i++) {
        f1[i] = i;
        num1[i] = 1;
    }
    for(int i=1;i<=m;i++) {
        f2[i] = i;
        num2[i] = 1;
    }
    for(int i=0;i<p;i++){
        scanf("%d%d", &x, &y);
        Union(x, y, f1, num1);
    }
    for(int i=0;i<q;i++){
        scanf("%d%d", &x, &y);
        Union(-x, -y, f2, num2);
    }
    printf("%d", min(num1[find(1, f1)], num2[find(1, f2)]));
}