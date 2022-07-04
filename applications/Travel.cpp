//
// Created by Passerby on 2022/4/3.
//
#include "iostream"
using namespace std;
const int SIZE = 5e5+5;
const int LAYOUR = 13;
int Trie[2][5*SIZE][2];
int origin[SIZE][3];
int lastappear[SIZE];
int prevappear[2*SIZE];
int deep[SIZE];
int sumjoy[SIZE];
bool appeared[(1<<LAYOUR)][2]={0};
int total=0;
int extrajoy=0;
void createTree(int self, int father){
    deep[self] = deep[father]+1;
    bool isodd = deep[father]%2;
    for(int index=lastappear[self];index;index = prevappear[index]) {
        int temp,joy;
        if(index%2) {
            temp=origin[(index-1)/2][1];
            joy=origin[(index-1)/2][2];
        }else{
            temp=origin[(index-2)/2][0];
            joy=origin[(index-2)/2][2];
        }
        if (temp == father) continue;
        sumjoy[temp] = sumjoy[self] ^ joy;
        appeared[sumjoy[temp]][isodd] = true;
        createTree(temp, self);
    }
}
void add(int n, bool isodd){
    int pointer = 0;
    for(int i=LAYOUR;i>=0;i--){
        if(!Trie[isodd][pointer][n/(1<<i)]){
            Trie[isodd][pointer][n/(1<<i)] = ++total;
        }
        pointer = Trie[isodd][pointer][n/(1<<i)];
        if(n/(1<<i)) n-=(1<<i);
    }
}
int findMax(int num, bool isodd){
    int pointer = 0;
    int result = 0;
    for(int i=LAYOUR;i>=0;i--){
        if(Trie[isodd][pointer][1-num/(1<<i)]) {
            result += 1 << i;
            pointer = Trie[isodd][pointer][1-num/(1<<i)];
        }else{
            pointer = Trie[isodd][pointer][num/(1<<i)];
        }
        if(num/(1<<i)) num-=(1<<i);
    }
    return result;
}
void Travel(){
    int n,m;
    scanf("%d%d", &n,&m);
    for(int i=0;i<n-1;i++){
        int a,b,c;
        scanf("%d%d%d" ,&a,&b,&c);
        prevappear[2*i+1] = lastappear[a];
        prevappear[2*i+2] = lastappear[b];
        lastappear[a] = 2*i+1;
        lastappear[b] = 2*i+2;
        origin[i][0]=a;
        origin[i][1]=b;
        origin[i][2]=c;
    }
    createTree(1, 0);
    appeared[0][1] = true;
    for(int i=0;i<(1<<LAYOUR);i++)
        for(int j=i;j<(1<<LAYOUR);j++){
            if((appeared[i][0]&&appeared[j][0])||(appeared[i][1]&&appeared[j][1]))
                add(i^j, 0);
            if((appeared[i][0]&&appeared[j][1])||(appeared[i][1]&&appeared[j][0]))
                add(i^j, 1);
        }
    for(int i=0;i<m;i++){
        int opt;
        scanf("%d", &opt);
        if(opt==2) {
            int joy;
            scanf("%d", &joy);
            extrajoy ^= joy;
        }else{
            int x,y;
            scanf("%d%d", &x, &y);
            int tmpres = sumjoy[x]^sumjoy[y];
            if((deep[x]-deep[y])%2) tmpres ^= extrajoy;
            int result = tmpres;
            result = max(result, findMax(tmpres, 0));
            result = max(result, findMax(tmpres ^ extrajoy, 1));
            printf("%d\n", result);
        }
    }
}