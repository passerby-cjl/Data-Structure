//
// Created by Passerby on 2022/4/26.
//
#include "iostream"
using namespace std;
const int SIZE = 1e5+5;
const int base = 101;
const int mod = 2e5+3;
int words[mod];
int nxt[SIZE];
int first[mod];
int Hash(char *word){
    int result=0;
    for(int i=0;word[i];i++)
        result=(result*base+word[i])%mod;
    return result;
}
void cuteMemorize(){
    int n, m, length, minlength, maxn=0, tail = 0, head = 1;
    scanf("%d", &n);
    char word[11];
    for(int i=1;i<=n;i++) {
        scanf("%s", word);
        words[i] = Hash(word);
    }
    scanf("%d", &m);
    for(int i=1;i<=m;i++) {
        scanf("%s", word);
        int hsh = Hash(word);
        if(!first[hsh]) {
            first[hsh] = i;
        }
        else {
            int index=first[hsh];
            while(nxt[index]) index = nxt[index];
            nxt[index] = i;
        }
    }
    for(int i=1;i<=n;i++) {
        tail = max(tail, first[words[i]]);
        if (first[words[i]]) maxn++;
    }
    minlength = length = tail-head+1;
    printf("%d\n", maxn);
    while(1){
        if(nxt[head]>tail) {
            length += nxt[head]-tail;
            tail = nxt[head];
        }
        if(!nxt[head]) break;
        head++;
        length--;
        minlength = min(minlength, length);
    }
    printf("%d", minlength);

}
int main(){
    cuteMemorize();
}