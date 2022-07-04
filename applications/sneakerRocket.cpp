//
// Created by Passerby on 2022/5/21.
//
#include "iostream"
using namespace std;
const int SIZE = 3e6+5;
int a[SIZE];
int org[SIZE];
int nw[SIZE];
long long dist[SIZE];
int queue[10*SIZE];
int last[SIZE];
int prv[10*SIZE];
int to[10*SIZE];
void sort(int beg,int end){
    int len=end-beg;
    if(len<=1) return;
    int i=beg,j=end-1;
    int pivot = a[beg+(len+1)/2-1];
    while(i<=j){
        while(a[i]<pivot) i++;
        while(pivot<a[j]) j--;
        if(i<=j){
            swap(a[i],a[j]);
            swap(org[i],org[j]);
            i++,j--;
        }
    }
    if(j>beg) sort(beg,i);
    if(end>i+1) sort(i,end);
}

void sneakerRocket(){
    int n,cnt=0;
    scanf("%d", &n);
    for(int i=1;i<=n;i++) scanf("%d",a+i);
    for(int i=1;i<=n;i++) org[i]=i;
    sort(1,n+1);
    for(int i=1;i<=n;i++) nw[org[i]]=i;
    int temp1=1,temp2=1;
    for(int i=2;i<=n+1;i++) {
        if(a[i]==a[temp1]){
            temp2=i;
        }else {
            for(int j=temp1;j<=temp2;j++)
                for(int k=temp1;k<=temp2;k++){
                    if(j==k) continue;
                    prv[++cnt]=last[j];
                    last[j]=cnt;
                    to[cnt]=k;
                }
            temp1=i;
            temp2=i;
        }
    }
    for(int i=1;i<n;i++){
        prv[++cnt]=last[nw[i]];
        last[nw[i]]=cnt;
        to[cnt]=nw[i+1];
        prv[++cnt]=last[nw[i+1]];
        last[nw[i+1]]=cnt;
        to[cnt]=nw[i];
    }
    long long head=0,tail=-1;
    int u;
    queue[++tail]=nw[1];
    for(int i=1;i<=n;i++) dist[i]=-1;
    dist[nw[1]]=0;
    while(head<=tail){
        u=queue[head++];
        for(int index=last[u];index;index=prv[index]){
            int v=to[index];
            if(dist[v]==-1){
                dist[v]=dist[u]+1;
                queue[++tail] = v;
            }
        }
    }
    printf("%lld", dist[nw[n]]);
}
int main(){
    sneakerRocket();
}