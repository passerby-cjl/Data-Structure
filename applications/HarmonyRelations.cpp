//
// Created by Passerby on 2022/4/30.
//
#include "iostream"
using namespace std;
const int SIZE = 3e4;
int f[SIZE];
int h[SIZE];
int e[SIZE];
int leader[SIZE];
int find(int x){
    if(f[x]==x) return x;
    return f[x] = find(f[x]);
}
void Union(int x, int y){
    int fx = find(x),fy = find(y);
    if(fx==fy) return;
    if(h[fx]<h[fy]) f[fx] = fy;
    else if(h[fy]<h[fx]) f[fy] = fx;
    else{
        f[fy] = fx;
        h[fx]++;
    }
}
void sort(int begin, int end){
    int len = end-begin;
    if(len<=1) return;
    int i=begin, j=end-1;
    int pivot = leader[begin + (len+1) / 2 - 1];
    while(i<=j){
        while(leader[i]<pivot) i++;
        while(pivot<leader[j]) j--;
        if(i<=j){
            swap(leader[i], leader[j]);
            i++,j--;
        }
    }
    if(j-begin>0) sort(begin, i);
    if(end-i>1) sort(i, end);
}
void HarmonyRelations(){
    int n,m,p,q, result=0;
    char opt;
    scanf("%d%d\n", &n, &m);
    for(int i=1;i<=n;i++) f[i] = i;
    for(int i=0;i<m;i++){
        cin>>opt;
        scanf("%d%d", &p, &q);
        if(opt=='F') {
            Union(p,q);
        }
        else{
            if(e[p]) {
                Union(e[p], q);
            }
            if(e[q]) {
                Union(e[q], p);
            }
            e[p] = q;
            e[q] = p;
        }
    }
    int group=0 ;
    for(int i=1;i<=n;i++) {
        leader[i] = find(i);
    }
    sort(1, n+1);
    for(int i=1;i<=n;i++){
        if(leader[i]!=group){
            result++;
            group = leader[i];
        }
    }
    printf("%d", result);
}