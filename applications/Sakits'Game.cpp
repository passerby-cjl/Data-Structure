//
// Created by Passerby on 2022/4/22.
//
//BAAAAAAAAAAAAAAAD
//VERSION1
/*
#include "iostream"
using namespace std;
const int SIZE = 4e5+5;
long long w[SIZE];
long long WIs[SIZE];
long long Ks[SIZE];
long long sum[4*SIZE];
int wnum[4*SIZE];
int cnt[SIZE];
int opts[SIZE];
int a2b[SIZE];
int b2a[SIZE];
int Wnum = 0;

inline long long read() {
    char ch = getchar();
    long long x = 0, fu = 1;
    while(ch < '0' || ch > '9')
    {
        if(ch == '-') fu = -1;
        ch = getchar();
    }
    while('0' <= ch && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * fu;
}

void sort(int begin, int end){
    int len = end - begin;
    if (len <= 1) return ;
    int i = begin, j = end - 1;
    long long pivot = w[(begin + (len+1)/2-1)];
    while (j - i >= 0){
        while (w[i] < pivot) i++;
        while (pivot < w[j]) j--;
        if (j - i >= 0){
            swap(w[i], w[j]);
            swap(cnt[i], cnt[j]);
            a2b[b2a[j]] = i, a2b[b2a[i]] = j;
            swap(b2a[i], b2a[j]);
            i++, j--;
        }
    }
    if (j - begin > 0) sort(begin, i);
    if (end - i > 1) sort(i, end);
}

void pushup(int rt){
    sum[rt] = sum[rt<<1]+sum[rt<<1|1];
    wnum[rt] = wnum[rt<<1]+wnum[rt<<1|1];
}

void build(int rt, int l, int r){
    if(l==r){
        wnum[rt] = cnt[l];
        sum[rt] = cnt[l]*w[l];
        return;
    }
    int mid = (l+r)>>1;
    build(rt<<1, l, mid);
    build(rt<<1|1, mid+1, r);
    pushup(rt);
}
int search(int rt, int l, int r, long long target, bool type){//0 for existed
    if(!(wnum[rt] || type) || w[r]<target) return 0;
    if(l==r) return rt;
    int mid = (l+r)>>1;
    long long result = search(rt<<1, l, mid, target, type);
    if(result) return result;
    return search(rt<<1|1, mid+1, r, target, type);
}

int query(int rt, int l, int r, long long target){
    if(l==r)
        return rt;
    int mid = (l+r)>>1;
    if(w[mid]<target) return query(rt<<1|1, mid+1, r, target);
    return query(rt<<1, l, mid, target);
}

void add(long long wi){
    int i = search(1, 1, Wnum, wi, 1);
    wnum[i]++;
    sum[i]+=wi;
    i>>=1;
    while(i){
        pushup(i);
        i>>=1;
    }
}

void del(long long wi){
    int i= search(1, 1, Wnum, wi, 0);
    wnum[i]--;
    sum[i]-=wi;
    i>>=1;
    while(i){
        pushup(i);
        i>>=1;
    }
}

int solve(int rt, int l, int r, long long &W, long long k){
    int counter=0;
    if(!wnum[rt]||w[l]>=W) return 0;
    if(w[r]<W&&W+sum[rt]<=k){
        W+=sum[rt];
        counter+=wnum[rt];
        return counter;
    }
    if(l==r&&W+sum[rt]>k){
        int temp=W;
        W+=sum[rt];
        if((k-W)%w[l]) return (k-temp)/w[l]+1;
        return (k-temp)/w[l];
    }
    int mid = (l+r)>>1;
    counter+=solve(rt<<1|1, mid+1, r, W, k);
    if(W<k) counter+= solve(rt<<1, l, mid, W, k);
    return counter;
}

void SakitsGame(){
    int n=read();
    for(int i=1;i<=n;i++) w[i] = read();
    int Q = read();
    int num = n;
    for(int i=1;i<=Q;i++){
        opts[i] = read();
        WIs[i] = read();
        if(opts[i]==1)
            Ks[i] = read();
        else {
            w[++num] = WIs[i];
            a2b[i] = num;
            b2a[num] = i;
            --cnt[num];
        }
    }
    sort(1, num+1);
    for(int i=1;i<=num;i++){
        if(i==1||w[i]!=w[Wnum]) {
            w[++Wnum] = w[i];
            cnt[Wnum] = 0;
        }
        cnt[Wnum]+=cnt[i];
        ++cnt[Wnum];
        a2b[b2a[i]] = Wnum;
    }
    build(1, 1, n);
    for(int i=1;i<=Q;i++) {
        switch (opts[i]) {
            case 1: {
                int result=0;
                while(WIs[i]<Ks[i]) {
                    int newRT = search(1, 1, Wnum, WIs[i], 0);
                    long long target = newRT?min(sum[newRT]/wnum[newRT]+1, Ks[i]):Ks[i];
                    result += solve(1, 1, Wnum, WIs[i], target);
                    if(WIs[i]<target) break;
                }
                if(WIs[i]<Ks[i]) printf("%d\n", -1);
                else printf("%d\n", result);
                break;
            }
            case 2: {
                add(WIs[i]);
                break;
            }
            case 3: {
                del(WIs[i]);
                break;
            }
        }
    }
}
int main(){
    SakitsGame();
}
 */
//
// Created by Passerby on 2022/4/22.
//
/*
BAAAAAAAAAAAAAAAAAAAAAAD VERSION2
#include "iostream"
using namespace std;
const int SIZE = 4e5+5;
long long w[SIZE];
long long WIs[SIZE];
long long Ks[SIZE];
int cnt[SIZE];
int opts[SIZE];
int a2b[SIZE];
int b2a[SIZE];
int reg[SIZE];
inline long long read() {
    char ch = getchar();
    long long x = 0, fu = 1;
    while(ch < '0' || ch > '9')
    {
        if(ch == '-') fu = -1;
        ch = getchar();
    }
    while('0' <= ch && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * fu;
}
void sort(int begin, int end){
    int len = end - begin;
    if (len <= 1) return ;
    int i = begin, j = end - 1;
    long long pivot = w[(begin + (len+1)/2-1)];
    while (j - i >= 0){
        while (w[i] < pivot) i++;
        while (pivot < w[j]) j--;
        if (j - i >= 0){
            swap(w[i], w[j]);
            swap(cnt[i], cnt[j]);
            a2b[b2a[j]] = i, a2b[b2a[i]] = j;
            swap(b2a[i], b2a[j]);
            i++, j--;
        }
    }
    if (j - begin > 0) sort(begin, i);
    if (end - i > 1) sort(i, end);
}
int search(int length, long long target){
    int l=0, r=length-1, m;
    while(l<r){
        m=(l+r+1)>>1;
        if(w[m]>target) r=m-1;
        else if(w[m]<target) l=m;
        else {
            while(m>=0&&!cnt[m]) --m;
            return m;
        }
    }
    m=(l+r)>>1;
    if(w[m]>target) return -1;
    while(m>=0&&!cnt[m]) --m;
    return m;
}
void SakitsGame(){
    int n=read();
    for(int i=0;i<n;i++) w[i] = read();
    int Q = read();
    int num = n;
    for(int i=1;i<=Q;i++){
        opts[i] = read();
        WIs[i] = read();
        if(opts[i]==1)
            Ks[i] = read();
        else{
            w[num++] = WIs[i];
            a2b[i] = num-1;
            b2a[num-1] = i;
            --cnt[num-1];
        }
    }
    sort(0, num);
    ++cnt[0];
    int Wnum = -1;
    for(int i=0;i<num;i++){
        if(!i||w[i]!=w[Wnum]) {
            w[++Wnum] = w[i];
            cnt[Wnum] = 0;
        }
        cnt[Wnum]+=cnt[i];
        ++cnt[Wnum];
        a2b[b2a[i]] = Wnum;
    }
    Wnum++;
    for(int i=1;i<=Q;i++){
        switch (opts[i]) {
            case 1:{
                long long counter=0;
                int boss;
                while(WIs[i]<Ks[i]){
                    boss = search(Wnum, WIs[i]-1);
                    if(boss==-1) {
                        for(int j=0;j<counter;j++) cnt[reg[j]]++;
                        counter = -1;
                        break;
                    }
                    reg[counter] = boss;
                    cnt[boss]--;
                    WIs[i]+=w[boss];
                    ++counter;
                }
                for(int j=0;j<counter;j++) cnt[reg[j]]++;
                printf("%lld\n", counter);
                break;
            }
            case 2:{
                ++cnt[a2b[i]];
                break;
            }
            case 3:{
                --cnt[a2b[i]];
                break;
            }
        }
    }
}
int main(){
    SakitsGame();
}*/
//
// Created by Passerby on 2022/4/24.
//
/*
 * PLAGIARISM! VERSION3
#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

const long long maxN = 4e5 + 5;
const long long maxQ = 1e5 + 5;
long long n, q, tot;
long long w[maxN], cnt[maxN];
bool flag[maxN];

struct Query
{
    long long op, w, k;
} Q[maxQ];

class SegmentTree
{
private:
    struct treeNode
    {
        long long num, sum;
        treeNode operator+(const treeNode &rhs) const
        { return {num + rhs.num, sum + rhs.sum}; }
    } tree[maxN << 2];

    struct recordNode
    {
        long long id;
        treeNode data;
    } rec[maxN << 2];
    long long top;

    void pushup(long long rt) { tree[rt] = tree[rt<<1] + tree[rt<<1|1]; }

    void Record(long long rt)
    {
        ++top;
        rec[top].id = rt, rec[top].data = tree[rt];
    }

    void Build(long long l, long long r, long long rt)
    {
        if(l == r)
        {
            tree[rt].num = cnt[l];
            tree[rt].sum = w[l] * cnt[l];
            return;
        }
        int mid = (l+((r-l)>>1));
        Build(l, mid, rt<<1);
        Build(mid + 1, r, rt<<1|1);
        pushup(rt);
    }

    long long Find(long long W, long long l, long long r, long long rt)
    {
        if(!tree[rt].num || w[r] < W) return 0;
        if(l == r) return w[l];
        int mid = (l+((r-l)>>1));
        long long ret = Find(W, l, mid, rt<<1);
        if(ret) return ret;
        return Find(W, mid + 1, r, rt<<1|1);
    }

    long long Increse(long long &W, long long target, long long l, long long r, long long rt)
    {
        if(!tree[rt].num || w[l] >= W) return 0;
        if(w[r] < W && W + tree[rt].sum <= target)
        {
            Record(rt);
            W += tree[rt].sum;
            long long ret = tree[rt].num;
            tree[rt].sum = tree[rt].num = 0;
            return ret;
        }
        if(l == r && W + tree[rt].sum > target)
        {
            Record(rt);
            long long ret = (target - W + w[l] - 1) / w[l];
            tree[rt].num -= ret, tree[rt].sum -= ret * w[l];
            W += ret * w[l];
            return ret;
        }
        long long ret = 0;
        int mid = (l+((r-l)>>1));
        ret += Increse(W, target, mid + 1, r, rt<<1|1);
        if(target - W > 0) ret += Increse(W, target, l, mid, rt<<1);
        Record(rt);
        pushup(rt);
        return ret;
    }

    void Undo()
    {
        for(int i=top;i>=1;i--)
            tree[rec[i].id] = rec[i].data;
        top = 0;
    }

public:
    SegmentTree(long long num) :top(0)
    {
        memset(tree, 0, sizeof tree);
        memset(rec, 0, sizeof rec);
        Build(1, num, 1);
    }
    ~SegmentTree() = default;

    long long Solve(long long W, long long K)
    {
        if(W >= K) return 0;
        long long ans = 0;
        while(W < K)
        {
            long long nextW = Find(W, 1, tot, 1);
            long long target = nextW ? min(nextW + 1, K) : K;
            ans += Increse(W, target, 1, tot, 1);
            if(W < target) break;
        }
        Undo();
        return W >= K ? ans : -1;
    }

    void Insert(long long W, long long l, long long r, long long rt)
    {
        if(l == r)
        {
            ++tree[rt].num, tree[rt].sum += W;
            return;
        }
        int mid = (l+((r-l)>>1));
        if(W <= w[mid]) Insert(W, l, mid, rt<<1);
        else Insert(W, mid + 1, r, rt<<1|1);
        pushup(rt);
    }

    void Delete(long long W, long long l, long long r, long long rt)
    {
        if(l == r)
        {
            --tree[rt].num, tree[rt].sum -= W;
            return;
        }
        int mid = (l+((r-l)>>1));
        if(W <= w[mid]) Delete(W, l, mid, rt<<1);
        else Delete(W, mid + 1, r, rt<<1|1);
        pushup(rt);
    }

};


inline long long read()
{
    long long ret = 0, f = 1;
    char c = getchar();
    while(!isdigit(c))
    {
        if(c == '-') f = -1;
        c = getchar();
    }
    while(isdigit(c))
        ret = (ret << 3) + (ret << 1) + c - '0', c = getchar();
    return f * ret;
}

void mySort(long long arr[], long long l, long long r)
{
    long long mid = arr[l + ((r - l) >> 1)];
    long long i = l, j = r;
    while(i <= j)
    {
        while(arr[i] < mid) ++i;
        while(arr[j] > mid) --j;
        if(i <= j)
        {
            swap(arr[i], arr[j]);
            swap(flag[i], flag[j]);
            ++i, --j;
        }
    }
    if(l < j) mySort(arr, l, j);
    if(i < r) mySort(arr, i, r);
}

void Unique(long long arr[], long long l, long long r)
{
    long long rt = l;
    cnt[l] = flag[l];
    for(int i=l+1;i<=r;i++)
    {
        if(arr[i] != arr[rt])
            arr[++rt] = arr[i], cnt[rt] = flag[i];
        else cnt[rt] += flag[i], --tot;
    }
}

int main()
{
    n = read();
    for(int i=1;i<=n;i++) w[++tot] = read();
    memset(flag, true, (n + 1) * sizeof(bool));
    q = read();
    for(int i=1;i<=q;i++)
    {
        Q[i].op = read();
        Q[i].w = read();
        if(Q[i].op == 1) Q[i].k = read();
        if(Q[i].op == 2) w[++tot] = Q[i].w;
    }
    mySort(w, 1, tot);
    Unique(w, 1, tot);
    auto *tree = new SegmentTree(tot);
    for(int i=1;i<=q;i++)
    {
        switch(Q[i].op)
        {
            case 1:
                printf("%lld\n", tree->Solve(Q[i].w, Q[i].k)); break;
            case 2:
                tree->Insert(Q[i].w, 1, tot, 1); break;
            case 3:
                tree->Delete(Q[i].w, 1, tot, 1); break;
        }
    }
    delete tree;
    return 0;
}*/
