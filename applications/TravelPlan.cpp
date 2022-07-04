//
// Created by Passerby on 2022/4/26.
//
#include "iostream"
using namespace std;
const int SIZE = 2e5+5;
int road[SIZE][2];
int f[SIZE];
int h[SIZE];
int prevappear[2*SIZE];
int lastappear[SIZE];
int closeorder[SIZE];
bool connected[SIZE];
int separatenum = 0;
bool opened[SIZE];
int find(int x){
    if(x==f[x]) return x;
    return f[x] = find(f[x]);
}

void Union(int x, int y){
    int fx = find(x), fy = find(y);
    if(fx==fy) {
        separatenum ++;
        return;
    }
    if(h[fx]<h[fy]) f[fx] = fy;
    else if(h[fy]<h[fx]) f[fy] = fx;
    else{
        f[fy] = fx;
        h[fx]++;
    }
}

void TravelPlan(){
    int n, m, u, v;
    scanf("%d%d", &n, &m);
    for(int i=0;i<m;i++){
        scanf("%d%d" ,&u,&v);
        prevappear[2*i+1] = lastappear[u];
        prevappear[2*i+2] = lastappear[v];
        lastappear[u] = 2*i+1;
        lastappear[v] = 2*i+2;
        road[i][0]=u;
        road[i][1]=v;
    }
    for(int i=1;i<=n;i++) {
        f[i] = i;
        scanf("%d", closeorder+i);
    }
    for(int i=n;i>0;i--){
        opened[closeorder[i]] = true;
        separatenum++;
        for(int index = lastappear[closeorder[i]]; index; index=prevappear[index]) {
            int other;
            if (index % 2) {
                other = road[(index - 1) / 2][1];
            } else {
                other = road[(index - 2) / 2][0];
            }
            if (opened[other]) {
                separatenum--;
                Union(other, closeorder[i]);
            }
        }
        if(separatenum==1) connected[i]= true;
        else connected[i] = false;
    }
    for(int i=1;i<=n;i++)
        if(connected[i]) printf("YES\n");
        else printf("NO\n");
}