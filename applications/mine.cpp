//
// Created by Passerby on 2022/5/15.
//
#include <cstring>
#include "iostream"
using namespace std;
const int SIZE = 5e4+5;
long long last[SIZE]; long long prv[2*SIZE]; long long to[2*SIZE];
long long dfn[SIZE]; long long low[SIZE];
bool calced[SIZE];
bool iscut[SIZE];
long long st[SIZE];
long long ccnt=0,vcnt=0,cnt=0,root;
long long result1=0,result2=0;

void tarjan(long long u, long long fa){
    low[u]=dfn[u]=++cnt;
    long long son=0;
    bool ok = false;
    for(long long index=last[u];index;index=prv[index]){
        long long v=to[index];
        if(v==fa&&!ok) {
            ok = true;
            continue;
        }
        if(!dfn[v]){
            tarjan(v, u);
            if(u==root) son++;
            else if(dfn[u]<=low[v]) {
                iscut[u]= true;
            }
            low[u] = min(low[u],low[v]);
        }else low[u] = min(low[u],dfn[v]);
    }
    if(u==root && son>=2) iscut[u]= true;
}

void count(long long u){
    ++vcnt;
    calced[u]= true;
    for(long long index=last[u];index;index=prv[index]){
        long long v=to[index];
        if(calced[v])continue;
        else if(iscut[v]) {
            st[++ccnt]=v;
            calced[v]= true;
            continue;
        }
        count(v);
    }
}

void mine(){
    long long a,b,m,n,t=0;
    scanf("%lld", &m);
    while(m) {
        memset(last,0,sizeof(last));
        memset(dfn,0,sizeof(dfn));
        memset(low,0,sizeof(low));
        memset(iscut,0,sizeof(iscut));
        memset(calced,0,sizeof(calced));
        n=result1=result2=cnt=0;
        for (long long i = 0; i < m; i++) {
            scanf("%lld%lld", &a, &b);
            prv[2 * i + 1] = last[a];
            prv[2 * i + 2] = last[b];
            last[a] = 2 * i + 1;
            last[b] = 2 * i + 2;
            to[2 * i + 1] = b;
            to[2 * i + 2] = a;
            n=max(a,max(b,n));
        }
        for(long long i=1;i<=n;i++)
            if(!dfn[i]) {
                root=i;
                tarjan(i,0);
            }
        for(long long i=1;i<=n;i++){
            ccnt=vcnt=0;
            if(!iscut[i]&&!calced[i]) count(i);
            if(vcnt==n&&!ccnt){
                result1=2;
                result2=n*(n-1)/2;
            }
            else if(vcnt&&ccnt<2){
                ++result1;
                if(result2) result2*=vcnt;
                else result2=vcnt;
            }
            while(ccnt) calced[st[ccnt--]]= false;
        }
        printf("Case %lld: %lld %lld\n", ++t, result1, result2);
        scanf("%lld",&m);
    }
}