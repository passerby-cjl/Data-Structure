//
// Created by Passerby on 2022/4/17.
//

#include "iostream"
using namespace std;
const int SIZE = 1e5+5;
int minx[4*SIZE];
int lz[4*SIZE];
int a[SIZE];
int b[SIZE];
void pushup(int rt){
    minx[rt] = min(minx[rt<<1], minx[rt<<1|1]);
}
void change(int rt, int l, int r, int k){
    minx[rt]-=k;
    if(l<r) lz[rt]+=k;
}
void pushdown(int rt, int l, int r){
    if(!lz[rt]) return;
    int mid = (l+r)>>1;
    change(rt<<1, l, mid, lz[rt]);
    change(rt<<1|1, mid+1, r, lz[rt]);
    lz[rt] = 0;
}
void build(int rt, int l, int r){
    if(l==r){
        minx[rt] = b[l];
        return;
    }
    int mid = (l+r)>>1;
    build(rt<<1, l, mid);
    build(rt<<1|1, mid+1, r);
    pushup(rt);
}
void update(int rt, int l, int r, int x){
    if(x<l) {
        change(rt, l, r, 1);
        return;
    }
    if(l==r) return;
    int mid = (l+r)>>1;
    if(mid>x) update(rt<<1, l, mid, x);
    update(rt<<1|1, mid+1, r, x);
    pushup(rt);
}
int query(int rt, int l, int r){
    pushdown(rt, l, r);
    if(l==r) {
        if(!minx[rt]) {
            minx[rt] = __INT_MAX__;
            return l;
        }else return 0;
    }
    pushup(rt);
    int mid = (l+r)>>1;
    if(minx[rt<<1|1]<=0) {
        int x = query(rt<<1|1, mid+1, r);
        if(x) return x;
    }
    return query(rt<<1, l, mid);
}
void reformsort(){
    int n;
    scanf("%d", &n);
    for(int i=1;i<=n;i++)
        scanf("%d", b+i);
    build(1, 1, n);
    for(int i=1;i<=n;i++){
        int x = query(1, 1, n);
        a[x] = i;
        update(1, 1, n, x);
    }
    for(int i=1;i<=n;i++) printf("%d ", a[i]);
}