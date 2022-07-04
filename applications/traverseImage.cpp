//
// Created by Passerby on 2022/5/21.
//
#include "iostream"
using namespace std;
const int SIZE = 1e5+5;
int last[SIZE];
int prv[SIZE];
int to[SIZE];
int f[SIZE];
int dfn[SIZE];
int low[SIZE];
int stack[SIZE];
int col[SIZE];
int col_max[SIZE];
int sccprv[SIZE];
int scclast[SIZE];
int sccto[SIZE];
int indegree[SIZE];
int queue[SIZE];
int n,m,top=0,cnt=0,color=0;

void tarjan(int u){
    dfn[u] = low[u] = ++cnt;
    stack[++top] = u;
    int v;
    for(int index=last[u];index;index=prv[index]){
        v=to[index];
        if(!dfn[v]){
            tarjan(v);
            low[u] = min(low[u],low[v]);
        }else if(!col[v])
            low[u] = min(low[u], dfn[v]);
    }
    if(dfn[u]==low[u]){
        int mnum=0;
        ++color;
        while(stack[top]!=u){
            col[stack[top]]=color;
            mnum=max(mnum,stack[top]);
            --top;
        }
        mnum=max(u,mnum);
        col_max[color]=mnum;
        col[u] = color;
        --top;
    }
}
void traverseImage(){
    scanf("%d%d", &n,&m);
    for(int i=1,a,b;i<=m;i++){
        scanf("%d%d",&a,&b);
        prv[i]=last[b];
        last[b]=i;
        to[i]=a;
    }
    for(int i=1;i<=n;i++)
        if(!col[i]){
            tarjan(i);
        }
    for(int u=1,count=0;u<=n;u++){
        for(int index=last[u];index;index=prv[index]){
            int v=to[index];
            if(col[v]!=col[u]){
                sccprv[++count] = scclast[col[u]];
                scclast[col[u]] = count;
                sccto[count] = col[v];
                ++indegree[col[v]];
            }
        }
    }
    int tail=-1,head=0,u;
    for(int i=1;i<=color;i++) {
        f[i]=col_max[i];
        if (!indegree[i]) queue[++tail] = i;
    }
    while(head<=tail) {
        u=queue[head++];
        for (int index = scclast[u]; index; index = sccprv[index]) {
            int v = sccto[index];
            f[v] = max(f[u], f[v]);
            if(--indegree[v]==0)
                queue[++tail]=v;
        }
    }

    for(int i=1;i<n;i++) printf("%d ", f[col[i]]);
    printf("%d",f[col[n]]);
}
