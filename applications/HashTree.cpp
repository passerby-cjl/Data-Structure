//
// Created by Passerby on 2022/4/21.
//

#include <cstring>
#include "iostream"
using namespace std;
const int SIZE = 1e2+5;
const int SIZE2 = 3e4+5;
int origin[SIZE][2];
int lastappear[SIZE];
int prevappear[2*SIZE];
int s[SIZE];
int prime[SIZE];
bool st[600];
long long Hash[SIZE]={0};
long long HASH[SIZE2];
inline int read() {
    char ch = getchar();
    int x = 0, f = 1;
    while(ch < '0' || ch > '9')
    {
        if(ch == '-') f = -1;
        ch = getchar();
    }
    while('0' <= ch && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
void sort(long long *begin, long long *end){
    int len = end - begin;
    if (len <= 1) return ;
    long long *i = begin, *j = end - 1;
    long long pivot = *(begin + (len + 1) / 2 - 1);
    while (j - i >= 0){
        while (*i > pivot) i++;
        while (pivot > *j) j--;
        if (j - i >= 0){
            std::swap(*i, *j);
            i++, j--;
        }
    }
    if (j - begin > 0) sort(begin, i);
    if (end - i > 1) sort(i, end);
}
void getPrime(){
    int counter=0;
    int n=550;
    for(int i=2;i<=n;i++) {
        if(!st[i]) {
            prime[++counter] = i;
        }
        for(int j=1;prime[j]<=n/i;j++){
            st[prime[j]*i] = true;
            if(i%prime[j]==0)break;
        }
    }
}
void createTree(int self, int father){
    s[self] = 1;
    bool leaf=true;
    for(int index=lastappear[self];index;index = prevappear[index]) {
        int temp;
        if(index%2) {
            temp=origin[(index-1)/2][1];
        }else{
            temp=origin[(index-2)/2][0];
        }
        if (temp == father) continue;
        createTree(temp, self);
        s[self]+=s[temp];
        leaf= false;
        Hash[self]+=Hash[temp]*prime[s[temp]];
    }
    if(leaf) Hash[self] = 1;
}
void HashTree(){
    getPrime();
    int n, m;
    scanf("%d%d", &n,&m);
    int a,b;
    for(int j=0;j<m;j++) {
        int root;
        root = read();
        for (int i = 0; i < n-1; i++) {
            a=read();
            b=read();
            prevappear[2 * i + 1] = lastappear[a];
            prevappear[2 * i + 2] = lastappear[b];
            lastappear[a] = 2 * i + 1;
            lastappear[b] = 2 * i + 2;
            origin[i][0] = a;
            origin[i][1] = b;
        }
        createTree(root, -1);
        HASH[j] = Hash[root];
        memset(Hash, 0, sizeof(Hash));
        memset(prevappear, 0, sizeof(prevappear));
        memset(lastappear, 0, sizeof(lastappear));
        memset(s, 0, sizeof(s));
    }
    sort(HASH, HASH+m);
    int maxsame=0;
    long long now=HASH[0];
    int num=1;
    for(int i=1;i<m;i++){
        if(now==HASH[i]) {
            num++;
        }else{
            maxsame=max(num, maxsame);
            num=1;
            now = HASH[i];
        }
    }
    maxsame = max(maxsame, num);
    printf("%d", maxsame);
}