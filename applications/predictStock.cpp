//
// Created by Passerby on 2022/3/26.
//
#include "iostream"
using namespace std;
int search(int *queue, int *l, int head, int tail, int target){//比target大的最后一个树在队列中的位置
    int left=head, r=tail, m;
    if(head==tail) return head;
    while(left<r){
        m=(left+r)>>1;
        if(l[queue[m]]>target) left=m+1;
        else r=m;
    }
    m=((left+r)>>1)-1;
    return m;
}
void predictStock(){
    const int SIZE = 1e6;
    int n, l[SIZE], r[SIZE];
    cin>>n;
    for(int i=0;i<n;i++) scanf("%d%d", l+i, r+i);
    int result = 1, price=-1e9, tmpresult=0, queue[SIZE], tail=-1, head = 0;
    for(int i=0;i<n;i++){
        while(tail>=head&&l[i]>=l[queue[tail]]) tail--;
        queue[++tail] = i;
        price=max(l[i], price);
        if(price>r[i]){
            result = max(result, tmpresult);
            head = search(queue, l, head, tail, r[i]);
            tmpresult = i-queue[head]-1;
            head++;
            price = l[queue[head]];
        }
        tmpresult++;
    }
    result = max(result, tmpresult);
    cout<<result;
}