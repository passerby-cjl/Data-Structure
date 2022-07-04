//
// Created by Passerby on 2022/5/29.
//
#include <cstring>
#include "iostream"
using namespace std;
const int SIZE = 1e5+5;
int last[SIZE];
int prv[SIZE];
int to[SIZE];
int col[SIZE];
bool vis[SIZE];
int T,n,m,color=0;
void dfs(int u){
    vis[u]= true;
    col[u]=color;
    for(int index=last[u];index;index=prv[index]){
        int v=to[index];
        if(!vis[v]) dfs(v);
    }
}
void connectFactory(){
    scanf("%d", &T);
    for(int t=0;t<T;t++){
        memset(last, 0, sizeof last);
        memset(prv, 0, sizeof prv);
        memset(col, 0, sizeof col);
        memset(vis, 0, sizeof vis);
        memset(to, 0, sizeof to);
        color=0;
        int a,b;
        scanf("%d%d", &n, &m);
        for(int k=0;k<m;k++){
            scanf("%d%d", &a,&b);
            prv[2*k+1]=last[a];
            last[a]=2*k+1;
            to[2*k+1]=b;
            prv[2*k+2]=last[b];
            last[b]=2*k+2;
            to[2*k+2]=a;
        }
        for(int i=1;i<=n;i++){
            if(!vis[i]){
                color++;
                dfs(i);
            }
        }
        int result=1e9;
        if(col[1]==col[n]) {
            printf("%d\n", 0);
            continue;
        }else{
            for(int i=1;i<=n;i++)
                for(int j=1;j<=n;j++)
                    if(col[i]==col[1]&&col[j]==col[n])
                        result=min(result, (i-j)*(i-j));
            if(color<3) {
                printf("%d\n", result);
                continue;
            }
            for(int i=1;i<=color;i++){
                if(i==col[1]||i==col[n]) continue;
                int temp1=1e9, temp2=1e9;
                for(int s=1;s<=n;s++)
                    for(int f=1;f<=n;f++)
                        if(col[s]==col[1]&&col[f]==i)
                            temp1=min(temp1, (s-f)*(s-f));

                for(int s=1;s<=n;s++)
                    for(int f=1;f<=n;f++)
                        if(col[s]==col[1]&&col[f]==i)
                            temp2=min(temp2, (s-f)*(s-f));
                result=min(result, temp1+temp2);
            }
            printf("%d\n", result);
        }
    }
}

int main(){
    connectFactory();
}