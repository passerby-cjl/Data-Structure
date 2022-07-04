//
// Created by Passerby on 2022/4/30.
//
#include "iostream"
using namespace std;
const int SIZE = 1e5+5;
int Xs[SIZE];
int Ys[SIZE];
int Ls[SIZE];
int f[SIZE];
int h[SIZE];
void sort(int begin, int end){
    int len = end-begin;
    if(len<=1) return;
    int i=begin, j=end-1;
    int pivot = Ls[begin + (len+1) / 2 - 1];
    while(i<=j){
        while(Ls[i]<pivot) i++;
        while(pivot<Ls[j]) j--;
        if(i<=j){
            swap(Xs[i], Xs[j]);
            swap(Ys[i], Ys[j]);
            swap(Ls[i], Ls[j]);
            i++,j--;
        }
    }
    if(j-begin>0) sort(begin, i);
    if(end-i>1) sort(i, end);
}
int find(int x){
    if(x==f[x]) return x;
    return f[x] = find(f[x]);
}
void Union(int x, int y){
    int fx = find(x), fy = find(y);
    if(fx==fy) return;
    if(h[fx]<h[fy]) f[fx] = fy;
    else if(h[fy]<h[fx]) f[fy] = fx;
    else{
        f[fy] = fx;
        h[fx]++;
    }
}
void cuteCandy(){
    int N,M,K, result = 0, counter = 0;
    scanf("%d%d%d", &N, &M, &K);
    for(int i=0;i<M;i++){
        scanf("%d%d%d", Xs+i, Ys+i, Ls+i);
    }
    sort(0, M);
    for(int i=1;i<=N;i++) f[i] = i;
    int i=0;
    for(;i<M;i++){
        if(find(Xs[i])!=find(Ys[i])){
            Union(Xs[i], Ys[i]);
            result += Ls[i];
            counter++;
        }
        if(N-counter==K) break;
    }
    if(i==M) cout<<"No Answer";
    else cout<<result;
}