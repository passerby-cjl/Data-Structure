//
// Created by Passerby on 2022/4/28.
//
#include "iostream"
using namespace std;
const int SIZE = 5e4+5;
int l[SIZE];
int r[SIZE];
int t[2*SIZE];
int f[2*SIZE];
int w[2*SIZE];
bool OE[SIZE];
void sort(int begin, int end){
    int len = end-begin;
    if(len<=1) return;
    int i = begin, j = end-1;
    int pivot = t[i+(len+1)/2-1];
    while (j - i >= 0){
        while (t[i]<pivot) i++;
        while (pivot<t[j]) j--;
        if (j - i >= 0){
            std::swap(t[i], t[j]);
            i++, j--;
        }
    }
    if (j - begin > 0) sort(begin, i);
    if (end - i > 1) sort(i, end);
}
int find(int x){
    if(f[x]!=x){
        int fx = find(f[x]);
        w[x] = (w[x]+w[f[x]]) %2;
        f[x] = fx;
    }
    return f[x];
}
int search(int length, int target){
    int begin=0, end=length-1, m;
    while(begin<end){
        m=(begin+end)>>1;
        if(t[m]>target) end=m;
        else if(t[m]<target) begin=m+1;
        else return m;
    }
    m=(begin+end)>>1;
    if(t[m]!=target) return -1;
    return m;
}
bool Union(int x, int y, int _OE){
    int fx = find(x), fy = find(y);
    if(fx==fy) {
        if((w[y] - w[x] +2)%2!=_OE)
            return 1;
        return 0;
    }
    f[fy] = fx;
    w[fy] = (w[x] - w[y] + _OE + 2) % 2;
    return 0;
}
void cuteOE(){
    int n,m;
    char status[10];
    scanf("%d%d", &n, &m);
    for(int i=0;i<m;i++) {
        scanf("%d%d%s", l+i, r+i, status);
        if(status[0]=='o') OE[i] = 1;
        t[2*i]=l[i];
        t[2*i+1]=++r[i];
    }
    sort(0, 2*m);
    int num=-1;
    for(int i=0;i<2*m;i++)
        if(-1==num||t[i]!=t[num]) {
            t[++num] = t[i];
            f[num] = num;
        }
    int i=0;
    for(;i<m;i++){
        int lx = l[i], rx = r[i];
        lx = search(num, lx);
        rx = search(num, rx);
        if(Union(lx, rx, OE[i])) break;
    }
    printf("%d", i);

}