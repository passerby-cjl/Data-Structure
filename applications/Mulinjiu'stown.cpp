//
// Created by Passerby on 2022/5/15.
//
#include "iostream"
#include "cmath"
using namespace std;
const int SIZE = 500;
int position[SIZE][2];
float dist[SIZE][SIZE];
float w[SIZE*SIZE];
bool S[SIZE];
int s,p,cnt=0;
float lowcost[SIZE];
void prim()
{
    for(int i=0;i<p;i++)
    {
        lowcost[i] = 1e8;
    }
    S[0] = true;
    int num = 0,e = 0;
    while (num < p-1)
    {
        float micost = 1e8;
        int mine = -1;
        for(int i=0;i<p;i++)
            if(!S[i])
            {
                float temp = dist[e][i];
                if(temp < lowcost[i])
                    lowcost[i] = temp;
                if(lowcost[i] < micost)
                    micost = lowcost[mine=i];
            }
        w[cnt++] = micost;
        S[e=mine] = true;
        num++;
    }
    return;
}
void sort(int beg,int end){
    int len=end-beg;
    if(len<=1) return;
    int i=beg,j=end-1;
    float pivot = w[beg+(len+1)/2-1];
    while(i<=j){
        while(w[i]>pivot) i++;
        while(pivot>w[j]) j--;
        if(i<=j){
            swap(w[i],w[j]);
            i++,j--;
        }
    }
    if(i>beg) sort(beg,i);
    if(end>j) sort(i,end);
}
void Town(){
    scanf("%d%d", &s,&p);
    for(int i=0;i<p;i++) scanf("%d%d", &(position[i][0]), &(position[i][1]));
    for(int i=0;i<p;i++) {
        for (int j = i + 1; j < p; j++) {
            dist[i][j] = dist[j][i] = sqrt((position[i][0] - position[j][0]) * (position[i][0] - position[j][0]) +
                                               (position[i][1] - position[j][1]) * (position[i][1] - position[j][1]));
        }
    }
    prim();
    sort(0, cnt);
    float result = w[s-1];
    printf("%.2f", result);
}
