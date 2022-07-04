//
// Created by Passerby on 2022/4/17.
//

#include "iostream"
using namespace std;
const int SIZE = 1e5+5;
int heap[SIZE];
int a[SIZE];
int length = 0;
void push(int n){
    heap[++length] = n;
    int pointer = length;
    while(pointer/2&&n>heap[pointer/2]){
        swap(heap[pointer], heap[pointer/2]);
        pointer /= 2;
    }
}
void spreaddown(int rt){
    if(rt<<1>length) return;
    if((rt<<1|1)>length) {
        if (heap[rt << 1] > heap[rt])
            swap(heap[rt << 1], heap[rt]);
        return;
    }
    if(heap[rt<<1]>=heap[rt<<1|1] && heap[rt<<1]>heap[rt]){
        swap(heap[rt<<1], heap[rt]);
        spreaddown(rt<<1);
        return;
    }
    if(heap[rt<<1|1]>heap[rt<<1] && heap[rt<<1|1]>heap[rt]){
        swap(heap[rt<<1|1], heap[rt]);
        spreaddown(rt<<1|1);
        return;
    }
}
void exchange(int i){
    a[i] = heap[1];
    heap[1] = heap[length--];
    spreaddown(1);
}
void heapsort(){
    int n;
    scanf("%d", &n);
    for(int i=1;i<=n;i++){
        scanf("%d", a+i);
        push(a[i]);
    }
    //spreaddown(1);
    for(int i=1;i<=n;i++) printf("%d ", heap[i]);
    cout<<endl;
    for(int i=n;i>0;i--){
        exchange(i);
    }
    for(int i=1;i<=n;i++) printf("%d ", a[i]);
}