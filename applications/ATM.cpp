//
// Created by Passerby on 2022/5/10.
//
#include "iostream"
using namespace std;
const int SIZE = 5e5+5;
int prevappear[SIZE];
int lastfrom[SIZE];
int to[SIZE];
int scclast[SIZE];
int sccprv[SIZE];
int sccto[SIZE];
int money[SIZE];
int totalmoney[SIZE];
int sccmoney[SIZE];
int dfn[SIZE], low[SIZE], stack[SIZE], col[SIZE], queue[SIZE];
bool inqueue[SIZE];
bool sccbar[SIZE];
int cnt=0, top=0, color=0;
void tarjan(int u){
    dfn[u] = low[u] = ++cnt;
    stack[++top] = u;
    int v;
    for(int index=lastfrom[u];index;index=prevappear[index]){
        v=to[index];
        if(!dfn[v]){
            tarjan(v);
            low[u] = min(low[u],low[v]);
        }else if(!col[v])
            low[u] = min(low[u], dfn[v]);
    }
    if(dfn[u]==low[u]){
        ++color;
        while(stack[top]!=u){
            col[stack[top]]=color;
            sccmoney[color] += money[stack[top]];
            --top;
        }
        col[u] = color;
        sccmoney[color] += money[u];
        --top;
    }
}
void ATM(){
    int N,M,S,P;
    scanf("%d%d", &N, &M);
    for(int i=1,a,b;i<=M;i++) {
        scanf("%d%d", &a, &b);
        prevappear[i] = lastfrom[a];
        to[i]=b;
        lastfrom[a] = i;
    }
    for(int i=1;i<=N;i++) {
        scanf("%d", money+i);
    }
    scanf("%d%d", &S, &P);
    tarjan(S);
    for(int u=1,count=color;u<=N;u++){
        for(int index=lastfrom[u];index;index=prevappear[index]){
            int v=to[index];
            if(col[v]!=col[u]&&col[u]&&col[v]){
                sccprv[++count] = scclast[col[u]];
                scclast[col[u]] = count;
                sccto[count] = col[v];
            }
        }
    }
    for(int i=0,k;i<P;i++) {
        scanf("%d", &k);
        sccbar[col[k]] = 1;
    }
    int tail = -1, head=0;
    queue[++tail] = col[S];
    inqueue[col[S]] = true;
    totalmoney[col[S]] = sccmoney[col[S]];
    int u, v;
    while(head<=tail){
        u=queue[head];
        head++;
        inqueue[u]= false;
        for(int index=scclast[u];index;index=sccprv[index]){
            v=sccto[index];
            if(totalmoney[v]<totalmoney[u]+sccmoney[v]){
                totalmoney[v]=totalmoney[u]+sccmoney[v];
                if(!inqueue[v]){
                    inqueue[v]= true;
                    queue[++tail] = v;
                }
            }
        }
    }
    int result=0;
    for(int i=1;i<=color;i++){
        if(sccbar[i]&&totalmoney[i]>result) result=totalmoney[i];
    }
    printf("%d", result);
}
