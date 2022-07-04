#include "iostream"
#include "cmath"
using namespace std;
int gcd(int a, int b){
    return b?gcd(b, a%b):a;
}

void GCDQuestion(){
    int n,m;
    cin>>n>>m;
    int *a = new int[n];
    const int N = n;
    const int Nj = int(log(n)/log(2))+1;
    int f[N][Nj]={0};
    for(int i=0; i<n;i++) {
        scanf("%d", a+i);
        f[i][0] = a[i];
    }
    for(int j=1;j<=int(log(n)/log(2));j++)
        for(int i=0;i+(1<<j)-1<n;i++)
            f[i][j] = gcd(f[i][j-1], f[i+(1<<(j-1))][j-1]);
    int l,r,x;
    for(int i=0;i<m;i++) {
        scanf("%d%d", &l, &r);
        x = int(log(r - l + 1) / log(2));
        int result = gcd(f[l-1][x], f[r - (1 << x)][x]);
        printf("%d ", result);
        int l1=l-1, r1=r;
        int l2 = r, r2=n+1;
        while(l1 + 1 < r1){
            int midl = (l1+r1)>>1;
            int tempx = int(log(midl - l + 1) / log(2));
            if(gcd(f[l-1][tempx], f[midl - (1<<tempx)][tempx])>result) l1 = midl;
            else r1 = midl;
        }while(l2 + 1 < r2){
            int midr = (r2+l2)>>1;
            int tempx = int(log(midr - l + 1) / log(2));
            if(gcd(f[l-1][tempx], f[midr - (1<<tempx)][tempx])<result) r2 = midr;
            else l2 = midr;
        }
        printf("%d\n", l2-r1);
    }
}