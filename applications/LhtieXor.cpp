//
// Created by Passerby on 2022/4/5.
//
#include "iostream"
using namespace std;
const int SIZE = 4e5+5;
const int TOTAL = 2e7+5;
int TrieL[TOTAL][2]={0};
int TrieR[TOTAL][2]={0};
int Max_L[SIZE]={0};
int Max_R[SIZE]={0};
int A[SIZE];
int total=0;
void add(int n, int Trie[TOTAL][2]){
    int pointer = 0;
    for(int i=30;i>=0;i--){
        if(!Trie[pointer][n/(1<<i)]){
            Trie[pointer][n/(1<<i)] = ++total;
        }
        pointer = Trie[pointer][n/(1<<i)];
        if(n/(1<<i)) n-=(1<<i);
    }
}
int findMax(int num, int Trie[TOTAL][2]){
    int pointer = 0;
    int result = 0;
    for(int i=30;i>=0;i--){
        if(Trie[pointer][1-num/(1<<i)]) {
            result += 1 << i;
            pointer = Trie[pointer][1-num/(1<<i)];
        }else{
            pointer = Trie[pointer][num/(1<<i)];
        }
        if(num/(1<<i)) num-=(1<<i);
    }
    return result;
}
void LhtieXor(){
    int N;
    scanf("%d", &N);
    for(int i=1;i<=N;i++) scanf("%d", A+i);
    int sum=0;
    add(0,TrieL);
    for(int i=2;i<=N;i++){
        sum ^= A[i-1];
        Max_L[i] = max(Max_L[i-1], findMax(sum,TrieL));
        add(sum,TrieL);
    }
    total=0;
    sum = 0;
    add(0, TrieR);
    for(int i=N;i>=2;i--){
        sum ^= A[i];
        Max_R[i] = max(Max_R[i+1], findMax(sum, TrieR));
        add(sum, TrieR);
    }
    int result=0;
    for(int i=2;i<=N;i++){
        result = max(result, Max_L[i]+Max_R[i]);
    }
    cout<<result;
}