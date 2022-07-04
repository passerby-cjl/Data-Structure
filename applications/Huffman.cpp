//
// Created by Passerby on 2022/3/26.
//
#include "iostream"
using namespace std;
void sort(int *w, int low, int high){
    if(low>=high) return;
    int i=low;
    int j=high+1;
    int mid = w[low];
    while(1){
        while(w[++i] < mid)
            if(i==high) break;
        while(w[--j] > mid)
            if(j==low) break;
        if(i>=j) break;
        int temp = w[i];
        w[i] = w[j];
        w[j] = temp;
    }
    w[low] = w[j];
    w[j] = mid;
    sort(w, low, j-1);
    sort(w, j+1, high);
}
void Huffman(){
    const int SIZE = 1e6;
    int n,m,head=0;
    cin>>n>>m;
    //int w[SIZE];
    int zero=0;
    if((n-1)%(m-1)) zero = (m-1)-((n-1)%(m-1));
    n += zero;
    int empty = (n-1)/(m-1);
    int headF = empty;
    int *F = new int[n+empty];
    int *A = new int[n];
    for(int i=0;i<zero; i++) A[i] = 0;
    for(int i=zero;i<n;i++) scanf("%d", A+i);
    sort(A, 0, n-1);
    for(int i=0;i<n;i++) {
        F[i+empty]=A[i];
        //A[i] = F[i+empty];
    }
    for(int i=0;i<(n-1)/(m-1);i++){
        int temp = 0;
        for(int j=0;j<m;j++)
            temp += A[head+j];
        F[--headF] = temp;
        head += m-1;
        int j=head+1;
        while(j<n&&A[j]<temp){
            A[j-1] = A[j];
            j++;
        }
        A[j-1] = temp;
    }
    long long result = 0;
    for(int i=0;i<empty;i++)
        result+=F[i];
    cout<<result;
}