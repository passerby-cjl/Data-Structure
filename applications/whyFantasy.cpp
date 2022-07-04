//
// Created by Passerby on 2022/4/13.
//

#include "iostream"
using namespace std;
const int SIZE = 1e5+5;
double sum[4*SIZE];
double sum2[4*SIZE];
double lz[4*SIZE];
double a[SIZE];
void pushup(int rt){
    sum[rt] = sum[rt<<1]+sum[rt<<1|1];
    sum2[rt] = sum2[rt<<1]+sum2[rt<<1|1];
}
void build(int rt, int l, int r){
    if(l==r){
        sum[rt] = a[l];
        sum2[rt] = a[l]*a[l];
        return;
    }
    int mid = (l+r)>>1;
    build(rt<<1, l, mid);
    build(rt<<1|1, mid+1, r);
    pushup(rt);
}
void change(int rt, int l, int r, double k){
    sum2[rt] += 2*k*sum[rt] + (r-l+1)*k*k;
    sum[rt] += (r-l+1)*k;
    if(l<r)
        lz[rt] += k;
}
void pushdown(int rt, int l, int r){
    if(!lz[rt]) return;
    int mid = (l+r)>>1;
    change(rt<<1, l, mid, lz[rt]);
    change(rt<<1|1, mid+1, r, lz[rt]);
    lz[rt] = 0;
}
void update(int rt, int l, int r, int x, int y, double k){
    pushdown(rt, l, r);
    if(x<=l&&r<=y){
        change(rt, l, r, k);
        return;
    }
    int mid = (l+r)>>1;
    if(x<=mid) update(rt<<1, l, mid, x, y, k);
    if(y>mid) update(rt<<1|1, mid+1, r, x, y, k);
    pushup(rt);
}
double query_sum(int rt, int l, int r, int x, int y, int type){
    pushdown(rt, l, r);
    if(x<=l&&r<=y) {
        if(type == 1)
            return sum[rt];
        if(type == 2)
            return sum2[rt];
    }
    int mid = (l+r)>>1;
    if(y<=mid) return query_sum(rt<<1, l, mid, x, y, type);
    if(x>mid) return query_sum(rt<<1|1, mid+1, r, x, y, type);
    return query_sum(rt<<1, l, mid, x, y, type) + query_sum(rt<<1|1, mid+1, r, x, y, type);
}
void whyFantasy(){
    int n,m;
    scanf("%d%d", &n,&m);
    for(int i=1;i<=n;i++) scanf("%lf", a+i);
    build(1, 1, n);
    for(int i=0;i<m;i++){
        int opt, x, y;
        scanf("%d%d%d", &opt, &x, &y);
        switch (opt) {
            case 1:
                double k;
                scanf("%lf", &k);
                update(1, 1, n, x, y, k);
                break;
            case 2: {
                int result = query_sum(1, 1, n, x, y, 1) / (y-x+1) * 100;
                printf("%d\n", result);
                break;
            }
            case 3: {
                double temp = query_sum(1, 1, n, x, y, 1) / (y-x+1);
                int result = (query_sum(1, 1, n, x, y, 2) / (y-x+1) - temp * temp)*100;
                printf("%d\n", result);
                break;
            }
        }
    }
}