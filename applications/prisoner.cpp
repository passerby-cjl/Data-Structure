//
// Created by Passerby on 2022/4/25.
//
#include "iostream"
using namespace std;
const int SIZE = 1e5+5;
struct RelationNode{
    int a;
    int b;
    int c;
};
RelationNode relas[SIZE];
int f[SIZE];
int h[SIZE];
int ene[SIZE];
void sort(int begin, int end){
    int len = end - begin;
    if (len <= 1) return ;
    int i = begin, j = end - 1;
    int pivot = relas[(begin + (len+1)/2-1)].c;
    while (j - i >= 0){
        while (relas[i].c > pivot) i++;
        while (pivot > relas[j].c) j--;
        if (j - i >= 0){
            swap(relas[i], relas[j]);
            i++, j--;
        }
    }
    if (j - begin > 0) sort(begin, i);
    if (end - i > 1) sort(i, end);
}
int find(int a){
    if(f[a] == a) return a;
    return f[a] = find(f[a]);
}
void Union(int a, int b){
    int fa = find(a), fb = find(b);
    if(fa==fb) return;
    if(h[fa]>h[fb]) f[fb] = fa;
    else if(h[fa]<h[fb]) f[fa] = fb;
    else{
        f[fa] = fb;
        ++h[fb];
    }
    return;
}
bool Query(int x, int y){
    int fx = find(x), fy = find(y);
    return fx==fy;
}
void prisoner(){
    int n,m;
    scanf("%d%d", &n,&m);
    for(int i=0;i<m;i++) scanf("%d%d%d", &(relas[i].a), &(relas[i].b), &(relas[i].c));
    sort(0, m);
    for(int i=0;i<m;i++) f[i] = i;
    int i=0;
    for(;i<m;i++){
        int a=relas[i].a, b=relas[i].b;
        if(Query(a,b)) {
            printf("%d", relas[i].c);
            break;
        }
        if(!ene[a]&&!ene[b]) {
            f[a] = a;
            f[b] = b;
            ene[a] = b;
            ene[b] = a;
            continue;//1:ade2:bcf
        }//a<->b|c<->d|e<->f|c<->a|d<->f|e<->c|a<->d

        if(ene[a]) Union(ene[a], b);
        else ene[a] = b;
        if(ene[b]) Union(a, ene[b]);
        else ene[b] = a;
    }
    if(i==m) printf("%d", 0);
}