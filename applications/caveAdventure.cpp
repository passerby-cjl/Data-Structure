//
// Created by Passerby on 2022/5/15.
//
#include "iostream"
using namespace std;
const int SIZE = 1e6+5, SIZE2 = 5e3+5;
int last[SIZE2];
int prv[2*SIZE];
int to[2*SIZE];
int t[2*SIZE];
int queue[10*SIZE];
int total[SIZE2];
bool inqueue[SIZE2];
int n,m;
int dijkstra(int src, int banned) {
    int head = 0, tail = -1, u, v;
    queue[++tail] = src;
    inqueue[src] = true;
    for(int i=1;i<=n;i++) total[i]=2e9;
    total[src]=0;
    while (head <= tail) {
        u = queue[head++];
        inqueue[u] = false;
        for (int index = last[u]; index; index = prv[index]) {
            if (index == banned) continue;
            v = to[index];
            if (total[v] > total[u] + t[index]) {
                total[v] = total[u] + t[index];
                if (!inqueue[v]) {
                    inqueue[v] = true;
                    queue[++tail] = v;
                }
            }
        }
    }
    return total[1];
}

void caveAdventure(){
    int a,b,c,d;
    scanf("%d%d", &n,&m);
    for(int i=0;i<m;i++){
        scanf("%d%d%d%d", &a,&b,&c,&d);
        prv[2*i+1]=last[a];
        prv[2*i+2]=last[b];
        last[a]=2*i+1;
        last[b]=2*i+2;
        to[2*i+1]=b;
        to[2*i+2]=a;
        t[2*i+1]=c;
        t[2*i+2]=d;
    }
    int result = 2e9;
    for(int index=last[1];index;index=prv[index]){
        int temp=t[index]+dijkstra(to[index], index-1+2*(index%2));
        result=min(result, temp);
    }
    printf("%d",result);
}