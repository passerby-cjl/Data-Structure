//
// Created by Passerby on 2022/5/22.
//
#include "iostream"
using namespace std;
const int SIZE = 5e5+5;
int low[SIZE];
int dfn[SIZE];
int last[SIZE];
int prv[2*SIZE];
int to[2*SIZE];
int s[SIZE];
int t[SIZE];
int cost1[SIZE];
int cost2[SIZE];
int cost[SIZE];
int f[SIZE];
int h[SIZE];
bool isbridge[SIZE];
int cnt=0,n,m;
void tarjan(long long u, long long fa){
    low[u]=dfn[u]=++cnt;
    bool ok = false;
    for(long long index=last[u];index;index=prv[index]){
        long long v=to[index];
        if(v==fa&&!ok) {
            ok = true;
            continue;
        }
        if(!dfn[v]){
            tarjan(v, u);
            if(dfn[u]<low[v]) {
                isbridge[(index-1)/2]= true;
            }
            low[u] = min(low[u],low[v]);
        }else low[u] = min(low[u],dfn[v]);
    }
}
void sort(int beg,int end){
    int len=end-beg;
    if(len<=1) return;
    int i=beg,j=end-1;
    float pivot = cost[beg+(len+1)/2-1];
    while(i<=j){
        while(cost[i]<pivot) i++;
        while(pivot<cost[j]) j--;
        if(i<=j){
            swap(s[i],s[j]);
            swap(t[i],t[j]);
            swap(cost[i],cost[j]);
            i++,j--;
        }
    }
    if(i>beg) sort(beg,i);
    if(end>j) sort(i,end);
}

int find(int x){
    if(x==f[x]) return x;
    return f[x]=find(f[x]);
}

void merge(int x, int y){
    int fx=find(x),fy=find(y);
    if(fx==fy) return;
    if(h[fx]>h[fy]) f[fy]=fx;
    else if(h[fx]<h[fy]) f[fx]=fy;
    else{
        f[fx]=fy;
        h[fy]++;
    }
}

long long Kruskal() {
    long long result = 0;
    for (int i = 0; i < m; i++) {
        if (find(s[i]) == find(t[i])) continue;
        result += cost[i];
        merge(s[i], t[i]);
    }
    return result;
}

void Earthquake(){
    scanf("%d%d",&n,&m);
    for(int i=0;i<m;i++){
        scanf("%d%d%d%d",s+i,t+i,cost1+i,cost2+i);
        prv[2*i+1]=last[s[i]];
        last[s[i]]=2*i+1;
        to[2*i+1]=t[i];
        prv[2*i+2]=last[t[i]];
        last[t[i]]=2*i+2;
        to[2*i+2]=s[i];
    }
    tarjan(1,0);
    for(int i=0;i<m;i++) cost[i]=isbridge[i]?cost2[i]:cost1[i];
    sort(0,m);
    for(int i=1;i<=n;i++) f[i]=i;
    printf("%lld",Kruskal());
}
