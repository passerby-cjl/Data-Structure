//
// Created by Passerby on 2022/5/24.
//
#include "iostream"
using namespace std;
const int SIZE = 85;
int matrix[SIZE][SIZE];
int dp[SIZE][SIZE];
void matrixGame(){
    int n,m;
    long long result=0;
    scanf("%d%d", &n,&m);
    for(int i=1;i<=n;i++)
        for (int j = 1; j <= m; j++)
            scanf("%d", &(matrix[i][j]));
    for(int i=1;i<=n;i++) {
        for(int l=1;l<=m;l++) dp[l][l]=matrix[i][l]*(m*m+m+1);
        for (int k = 2; k <= m; k++) {
            int factor = (m+1-k) * (m+1-k) + (m+1-k) + 1;
            for(int l=1;l+k-1<=m;l++)
                dp[l][l+k-1]=max(dp[l][l+k-2]+matrix[i][l+k-1]*factor, dp[l+1][l+k-1]+matrix[i][l]*factor);
        }
        result+=dp[1][m];
    }
    printf("%lld", result);
}