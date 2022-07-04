//
// Created by Passerby on 2022/5/13.
//
#include "iostream"
using namespace std;
const int SIZE = 1e5+5;
int h[SIZE];
long long D[SIZE];
int S[SIZE];
int T[SIZE];
int f[SIZE];
long long num[SIZE];
void sort(int beg, int end){
    int len = end-beg;
    if(len<=1) return;
    int i=beg, j=end-1;
    int pivot = D[beg+(len+1)/2-1];
    while(i<=j){
        while(D[i]<pivot) i++;
        while(pivot<D[j]) j--;
        if(i<=j){
            swap(D[i], D[j]);
            swap(S[i], S[j]);
            swap(T[i], T[j]);
            i++,j--;
        }
    }
    if(i+1<end) sort(i, end);
    if(j>beg) sort(beg, i);
}
int find(int x){
    if(f[x]==x) return x;
    return f[x]=find(f[x]);
}
void Union(int x, int y){
    int fx = find(x), fy = find(y);
    if(fx==fy) return;
    if(h[fx]>h[fy]) {
        f[fy] = fx;
        num[fx]+=num[fy];
    }
    else if(h[fy]>h[fx]) {
        f[fx] = fy;
        num[fy]+=num[fx];
    }
    else{
        f[fx] = fy;
        num[fy] += num[fx];
        h[fy]++;
    }
}
void LeastCompGame(){
    int N;
    long long result=0;
    scanf("%d", &N);
    for(int i=1;i<N;i++){
        scanf("%d%d%d", S+i, T+i, D+i);
        result+=D[i];
    }
    sort(1, N);
    for(int i=1;i<=N;i++) {
        f[i]=i;
        num[i]=1;
    }
    for(int i=1;i<N;i++){
        result+=(D[i]+1)*(num[find(S[i])]*num[find(T[i])]-1);
        Union(S[i],T[i]);
    }
    printf("%lld", result);
}