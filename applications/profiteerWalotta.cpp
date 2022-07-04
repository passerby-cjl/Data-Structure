//
// Created by Passerby on 2022/3/20.
//

#include "iostream"
using namespace std;
void profiteerWalotta(){
    int n,m,k;
    cin>>n>>m>>k;
    int head = 0;
    int tail = -1;
    int *p = new int[n];
    int pp = 0;
    for(int i=0;i<n;i++) {
        cin>>p[i];
        pp += p[i];
    }
    int **a = new int*[n];
    int *queue = new int[m];
    int *max = new int[m];
    int *yuan = new int[m];
    int maxe = 0;
    yuan[0] = 0;
    for(int i=0;i<n;i++){
        a[i] = new int[m];
        for(int j=0;j<m;j++) {
            queue[j]=0;
            cin>>a[i][j];
        }
        yuan[0] += a[i][0]*p[i];
    }
    for(int j=0;j<m;j++){
        max[j] = 0;
        for(int i=0;i<n;i++) {
            max[j] = max[j]>a[i][j]?max[j]:a[i][j];
        }
    }
    for(int j=0;j<m;j++) {
        while(tail>=head&&max[queue[tail]]<=max[j])
                tail--;
            queue[++tail] = j;
            while(queue[head]<=j-k)
                head++;
        if(j>0){
            yuan[j] = yuan[j-1];
            for(int i=0;i<n;i++)
                yuan[j]+=a[i][j]*p[i];
        }
        if(j>=k) {
            for (int i = 0; i < n; i++) yuan[j] -= a[i][j - k] * p[i];
        }
        if(j>=k-1){
            int result = max[queue[head]]*pp*k - yuan[j];
            maxe = maxe>result?maxe:result;
        }
    }cout<<maxe;
}