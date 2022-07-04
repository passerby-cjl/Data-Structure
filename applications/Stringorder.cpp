//
// Created by Passerby on 2022/4/16.
//

#include <cstring>
#include "iostream"
using namespace std;
const int SIZE = 1e5+5;
char s[SIZE];
int ch[4*SIZE][26];
int lz[4*SIZE];
void pushup(int rt){
    for(int i=0;i<26;i++)
        ch[rt][i] = ch[rt<<1][i] + ch[rt<<1|1][i];
}
void change(int rt, int l, int r, int type, int *ch_num){
    memset(ch[rt], 0, sizeof(ch[rt]));
    if(type) {
        for (int num = 0, i = 0; i < 26 && num < r - l + 1; i++)
            if (ch_num[i] < r - l + 1 - num) {
                num += ch[rt][i] = ch_num[i];
                ch_num[i] = 0;
            } else {
                if (r - l + 1 - num > 0)
                    ch_num[i] -= ch[rt][i] = r - l + 1 - num;
                break;
            }
        lz[rt] = 1;
    }else{
        for (int num = 0, i = 25; i >= 0 && num < r - l + 1; i--)
            if (ch_num[i] < r - l + 1 - num) {
                num += ch[rt][i] = ch_num[i];
                ch_num[i] = 0;
            } else {
                if (r - l + 1 - num > 0)
                    ch_num[i] -= ch[rt][i] = r - l + 1 - num;;
                break;
            }
        lz[rt] = -1;
    }
}
void pushdown(int rt, int l, int r){
    if(!lz[rt]||l==r) return;
    int mid = (l+r)>>1;
    bool type;
    if(lz[rt]==1)
        type = true;
    else
        type = false;
    int ch_num[26];
    for(int i=0;i<26;i++) ch_num[i] = ch[rt][i];
    change(rt<<1, l, mid, type, ch_num);
    change(rt<<1|1, mid+1, r, type, ch_num);
    lz[rt] = 0;
}
void getch_num(int rt, int l, int r, int x, int y, int *ch_num){
    pushdown(rt, l, r);
    if(x<=l&&y>=r) {
        for (int i = 0; i < 26; i++)
            ch_num[i] += ch[rt][i];
        return;
    }
    int mid = (l+r)>>1;
    if(x<=mid) getch_num(rt<<1, l, mid, x, y, ch_num);
    if(y>mid) getch_num(rt<<1|1, mid+1, r, x, y, ch_num);
}
void build(int rt, int l, int r){
    if(l==r){
        ch[rt][s[l]-'a'] = 1;
        return;
    }
    int mid = (l+r)>>1;
    build(rt<<1, l, mid);
    build(rt<<1|1, mid+1, r);
    pushup(rt);
}
void update(int rt, int l, int r, int x, int y, bool type, int *ch_num){
    pushdown(rt, l, r);
    if(x<=l&&y>=r){
        change(rt, l, r, type, ch_num);
        return;
    }
    int mid = (l+r)>>1;
    if(x<=mid) update(rt<<1, l, mid, x, y, type, ch_num);
    if(y>mid) update(rt<<1|1, mid+1, r, x, y, type, ch_num);
    pushup(rt);
}
void pushdownall(int rt, int l, int r){
    if(l==r) {
        for(int i=0;i<26;i++){
            char temp = 'a'+i;
            if(ch[rt][i]) s[l] = temp;
        }
        return;
    }
    pushdown(rt, l, r);
    pushup(rt);
    int mid = (l+r)>>1;
    pushdownall(rt<<1, l, mid);
    pushdownall(rt<<1|1, mid+1, r);
}
void Stringorder(){
    int n, m, l, r, opt;
    scanf("%d%d\n", &n, &m);
    scanf("%s", s+1);
    build(1, 1, n);
    for(int i=0;i<m;i++){
        scanf("%d%d%d", &l, &r, &opt);
        int ch_num[26] = {0};
        getch_num(1, 1, n, l, r, ch_num);
        update(1, 1, n, l, r, opt, ch_num);
    }
    pushdownall(1, 1, n);
    for(int i=1; i<=n;i++) printf("%c", s[i]);
}
