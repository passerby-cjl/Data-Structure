#include<iostream>
#include<cmath>
using namespace std;
/*void HeartAttack(){
    int n, m;
    cin>>n>>m;
    int *s = new int[n];
    int *f = new int[n+1];////
    int *lastgap = new int[n];
    int leftzero = 0;
    for(int i=0;i<n;i++){
        scanf("%d", &(s[i]));
        if(s[i] == 0) {
            f[i] = leftzero++;
            if(i) lastgap[i] = lastgap[i-1];
            else lastgap[i] = -1;
        }
        else {
            if(i) {
                f[i] = leftzero;
                if(!s[i-1]) lastgap[i] = i;
                else lastgap[i] = lastgap[i-1];
            }
            else {
                f[i] = 0;
                lastgap[i] = 0;
            }
        }
    }
    f[n] = leftzero;


    for(int i=0;i<m;i++){
        int type,l,r;
        scanf("%d", &type);
        scanf("%d", &l);
        scanf("%d", &r);
        if(type == 1){
            int damage=0;
            int damage0;
            int gap;
            gap = lastgap[r-1];
            while(l<gap+1){
                damage0 = 2 * f[gap] - f[l-1] + r - gap - f[r];
                if(damage < damage0) damage = damage0;
                gap = lastgap[gap-1];
            }
            damage0 = f[r] - f[l-1];
            if(damage < r - l + 1 - damage0) damage = r - l + 1 - damage0;
            if(damage < damage0) damage = damage0;
            printf("%d\n", damage);
        }
        if(type == 2){
            int rate;
            if(l<lastgap[r-1]+1) rate = 2;
            else rate=1;
            printf("%d\n",rate);
        }
    }

}*/
void HeartAttack(){
    int n, m;
    cin>>n>>m;
    int *s = new int[n+1];
    int *l0 = new int[n+2];
    int *lastgap = new int[n+1];
    int leftzero = 0;
    lastgap[0] = -1;
    l0[0] = 0;
    for(int i=1;i<=n;i++){
        scanf("%d", &(s[i]));
        if(s[i] == 0) {
            l0[i] = leftzero++;
            lastgap[i] = lastgap[i-1];
        }
        else {
            l0[i] = leftzero;
            if(!s[i-1]) lastgap[i] = i;
            else lastgap[i] = lastgap[i-1];
        }
    }
    l0[n+1] = leftzero;
    int **f = new int *[n];
    for(int i=1;i<=n;i++){
        f[i] = new int[int(log(n)/log(2))];
        f[i][0] = 1 + l0[i] + n - i - (l0[n+1] - l0[i+1]);
    }
    for(int j=1;j<=int(log(n)/log(2));j++)
        for(int i=1;i+(1<<j)-1<=n;i++)
            f[i][j] = max(f[i][j-1], f[i+(1<<(j-1))][j-1]);

    for(int i=0;i<m;i++){
        int type,l,r;
        scanf("%d", &type);
        scanf("%d", &l);
        scanf("%d", &r);
        if(type == 1){
            int x = int(log(r-l+1)/log(2));
            int damage = max(f[l][x], f[r+1-(1<<x)][x]) - l0[l] - (n - r - (l0[n+1] - l0[r+1]));
            printf("%d\n", damage);
        }
        if(type == 2){
            int rate;
            if(l<lastgap[r]) rate = 2;
            else rate=1;
            printf("%d\n",rate);
        }
    }
}
