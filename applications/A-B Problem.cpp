//
// Created by Passerby on 2022/4/11.
//

#include "iostream"
#include "ctime"
using namespace std;
const int SIZE = 2e5+5;
int a[SIZE];
int diff[SIZE];
void sort(int *begin, int *end){
    int len = end - begin;
    if (len <= 1) return ;
    int *i = begin, *j = end - 1;
    int pivot = *(begin + (len + 1) / 2 - 1);
    while (j - i >= 0){
        while (*i< pivot) i++;
        while (pivot< *j) j--;
        if (j - i >= 0){
            std::swap(*i, *j);
            i++, j--;
        }
    }
    if (j - begin > 0) sort(begin, i);
    if (end - i > 1) sort(i, end);
}
void A_BProblem(){
    int n, c, last=0, now, result=0, head=1, tail=1;
    scanf("%d%d", &n,&c);
    for(int i=1;i<=n;i++) {
        scanf("%d", a+i);
    }
    sort(a+1, a+n+1);
    for(int i=1;i<=n;i++) {
        diff[i] = a[i] - a[i-1];
    }
    for(int i=1;i<=n;i++){
        while(tail<=n&&a[tail]-a[head]!=c){
            if(a[tail]-a[head]<c) ++tail;
            if(a[tail]-a[head]>c) ++head;
        }
        if(tail>n) break;
        int samehead=0, sametail=0;
        while(!diff[++tail]&&tail<=n) sametail++;
        while(!diff[++head]) samehead++;
        result += (samehead+1)*(sametail+1);
    }
    cout<<result;
}