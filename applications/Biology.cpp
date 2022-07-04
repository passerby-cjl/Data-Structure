#include "iostream"
using namespace std;
const int MAXLEN = 1e6+5;
int deep[MAXLEN] = {0};
int f[MAXLEN][14]={0};
int tree[MAXLEN][26]={0};
int endpos[100000];
void append(int pieces, int &total){
    int pointer = 0;
    char temp[10000]={0};
    scanf("%s", &temp);
    for(int j=9999;j>=0;j--){
        if(temp[j]!=0){
            int alpha = temp[j]-'a';
            if(!tree[pointer][alpha]) {
                tree[pointer][alpha] = ++total;
                deep[total] = deep[pointer]+1;
                f[total][0] = pointer;
                for(int i=1;(1<<i)<deep[total];i++)
                    if(!f[total][i])
                        f[total][i] = f[f[total][i-1]][i-1];
            }
            pointer=tree[pointer][alpha];
        }
    }
    endpos[pieces] = pointer;
}
int LCA(int x, int y){
    if(deep[x]>deep[y]){
        int temp=x;
        x=y;
        y=temp;
    }
    for(int i=13;i>=0;i--){
        if(deep[y]-(1<<i)>=deep[x]){
            y=f[y][i];
        }
    }
    if(x==y) return x;
    for(int i=13;i>=0;i--){
        if(f[x][i]!=f[y][i]){
            x=f[x][i];
            y=f[y][i];
        }
    }
    return f[x][0];
}
void Biology(){
    int N,M;
    cin>>N>>M;
    int total=0;
    int pieces=0;
    for(int i=0;i<N;i++){
        append(++pieces, total);
    }
    for(int i=0;i<M;i++){
        int op;
        scanf("%d", &op);
        if(op==1){
            append(++pieces, total);
        }else{
            int num;
            scanf("%d", &num);
            int x;
            scanf("%d", &x);
            x=endpos[x];
            for(int j=1;j<num;j++){
                int y;
                scanf("%d",&y);
                x = LCA(x, endpos[y]);
            }
            printf("%d\n", deep[x]);
        }
    }
}