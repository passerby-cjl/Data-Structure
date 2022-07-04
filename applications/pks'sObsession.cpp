
#include "iostream"
#include "cmath"
using namespace std;
void Obsession(){
    int n,q;
    cin>>n>>q;
    int a[200010];
    int sum[200010];
    int f1[200010][20];
    int f2[200010][20];
    for(int i=1;i<=n;i++) scanf("%d", a+i);
    int b;
    sum[0] = 0;
    for(int i=1;i<=n;i++) {scanf("%d", &b);f1[i][0] = f2[i][0] = sum[i] = sum[i-1] + a[i]-b;}
    for(int j=1; j<=int(log(n)/log(2)); j++)
        for(int i=1; i+(1<<j)-1<=n;i++) {
            f1[i][j] = max(f1[i][j-1], f1[i+(1<<(j-1))][j-1]);
            f2[i][j] = min(f2[i][j-1], f2[i+(1<<(j-1))][j-1]);
        }
    for(int i=0;i<q;i++){
        int l,r;
        scanf("%d%d", &l, &r);
        int x = int(log(r-l+1)/log(2));
        if((sum[l-1]-sum[r])||(max(f1[l][x], f1[r-(1<<x)+1][x])-sum[l-1])>0) printf("%d\n", -1);
        else printf("%d\n", -(min(f2[l][x], f2[r-(1<<x)+1][x])-sum[l-1]));
    }

}