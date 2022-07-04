//
// Created by Passerby on 2022/3/25.
//
#include "iostream"
using namespace std;
int search(int *arr, int length, int target){
    int l=0, r=length, m;
    while(l<r){
        m=(l+r)>>1;
        if(arr[m]>target) r=m;
        if(arr[m]<target) l=m+1;
    }
    m=(l+r)>>1;
    if(arr[m]<target) return 0;
    return arr[m];
}
void wateringWalotta(){
    int n;
    cin>>n;
    const int SIZE = 1e6;
    int height[SIZE];
    int stackup[SIZE], stackdown[SIZE];
    for(int i=0;i<n;i++) cin>>height[i];
    int Topup=-1, Topdown=-1, result=1;
    for(int i=0;i<n;i++){
        int temp;
        while(Topup>=0&&height[i]<=height[stackup[Topup]]) Topup--;
        stackup[++Topup] = i;
        while(Topdown>=0&&height[i]>height[stackdown[Topdown]]) Topdown--;
        stackdown[++Topdown] = i;
        if(Topdown==0) temp=stackup[0];
        else {
            temp= search(stackup, Topup, stackdown[Topdown-1]);
        }
        result=max(i-temp+1, result);
    }
    cout<<result;
}
