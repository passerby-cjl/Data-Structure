//
// Created by Passerby on 2022/4/16.
//
#include "iostream"
using namespace std;
const int SIZE = 5e4+5;
int maxAvai[SIZE<<2];
int leftAvai[SIZE<<2];
int rightAvai[SIZE<<2];
int lz[SIZE<<2];
void pushup(int rt, int l, int r){
    int mid = (l+r)>>1;
    leftAvai[rt] = leftAvai[rt<<1] == mid-l+1?leftAvai[rt<<1]+leftAvai[rt<<1|1]:leftAvai[rt<<1];
    rightAvai[rt] = rightAvai[rt<<1|1] == r-mid?rightAvai[rt<<1|1]+rightAvai[rt<<1]:rightAvai[rt<<1|1];
    maxAvai[rt] = max(rightAvai[rt<<1]+leftAvai[rt<<1|1], max(maxAvai[rt<<1], maxAvai[rt<<1|1]));
}
void pushdown(int rt, int l, int r){
    if(!lz[rt]||l==r) return;
    int mid = (l+r)>>1;
    if(lz[rt]==1) {
        maxAvai[rt << 1] = leftAvai[rt << 1] = rightAvai[rt << 1] = mid - l + 1;
        maxAvai[rt << 1 | 1] = leftAvai[rt << 1 | 1] = rightAvai[rt << 1 | 1] = r - mid;
    }else {
        maxAvai[rt << 1] = leftAvai[rt << 1] = rightAvai[rt << 1] = 0;
        maxAvai[rt << 1 | 1] = leftAvai[rt << 1 | 1] = rightAvai[rt << 1 | 1] = 0;
    }
    lz[rt << 1] = lz[rt];
    lz[rt << 1 | 1] = lz[rt];
    lz[rt] = 0;
}
void build(int rt, int l, int r){
    if(l==r){
        maxAvai[rt] = leftAvai[rt] = rightAvai[rt] = 1;
        return;
    }
    int mid = (l+r)>>1;
    build(rt<<1, l, mid);
    build(rt<<1|1, mid+1, r);
    pushup(rt, l, r);
}
int query_max(int rt, int l, int r, int D){
    if(maxAvai[rt]<D) return 0;
    pushdown(rt, l, r);
    int mid = (l+r)>>1;
    if(maxAvai[rt<<1]>=D) return query_max(rt<<1, l, mid, D);
    if(rightAvai[rt<<1]+leftAvai[rt<<1|1]>=D) return mid - rightAvai[rt<<1] + 1;
    return query_max(rt<<1|1, mid+1, r, D);
}
void update(int rt, int l, int r, int x, int y, bool type){
    pushdown(rt, l, r);
    if(x<=l&&r<=y){
        if(type){
            maxAvai[rt] = leftAvai[rt] = rightAvai[rt] = r-l+1;
            lz[rt] = 1;
            return;
        }else{
            maxAvai[rt] = leftAvai[rt] = rightAvai[rt] = 0;
            lz[rt] = -1;
            return;
        }
    }
    int mid = (l+r)>>1;
    if(x<=mid) update(rt<<1, l, mid, x, y, type);
    if(y>mid) update(rt<<1|1, mid+1, r, x, y, type);
    pushup(rt, l, r);
}
void Hotel(){
    int N,M,opt;
    scanf("%d%d", &N, &M);
    build(1, 1, N);
    for(int i=0;i<M;i++){
        scanf("%d", &opt);
        if(opt==1){
            int D,x;
            scanf("%d", &D);
            x=query_max(1, 1, N, D);
            printf("%d\n", x);
            if(x) update(1, 1, N, x, x+D-1, 0);
        }else {
            int D, x;
            scanf("%d%d", &x, &D);
            update(1, 1, N, x, x + D - 1, 1);
        }
    }
}