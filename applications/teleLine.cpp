//
// Created by Passerby on 2022/5/14.
//
#include <cstring>
#include "iostream"
using namespace std;
const int SIZE = 1e5+5;
int last[SIZE];
int prv[2*SIZE];
int other[SIZE];
int weight[SIZE];
int queue[SIZE];
int len[SIZE];
bool inqueue[SIZE];
int K,N;
bool SPFA(int money){
    int head=0,tail=-1,u,v;
    for(int i=2;i<=N;i++) len[i]=SIZE;
    for(int i=2;i<=N;i++) inqueue[i]= false;
    queue[++tail]=1;
    inqueue[1]= true;
    len[1]=0;
    while(head<=tail){
        u=queue[head++];
        inqueue[u]= false;
        for(int index=last[u];index;index=prv[index]){
            v=other[index];
            if(len[v]>len[u]+(weight[(index-1)>>1]>money)){
                len[v]=len[u]+(weight[(index-1)>>1]>money);
                if(!inqueue[v]){
                    queue[++tail]=v;
                    inqueue[v]= true;
                }
            }
        }
    }
    return len[N]<=K;
}
void teleLine(){
    int P,A,B,L;
    scanf("%d%d%d", &N, &P, &K);
    for(int i=0;i<P;i++){
        scanf("%d%d%d",&A,&B,&L);
        prv[2 * i + 1] = last[A];
        prv[2 * i + 2] = last[B];
        last[A] = 2 * i + 1;
        last[B] = 2 * i + 2;
        other[2 * i + 1] = B;
        other[2 * i + 2] = A;
        weight[i]=L;
    }
    int l=0,r=1e6+5;
    if(!SPFA(r)) printf("-1");
    else {
        while(l<r){
            int mid=(l+r)>>1;
            if(SPFA(mid)) r=mid;
            else l=mid+1;
        }
        printf("%d", l);
    }
}