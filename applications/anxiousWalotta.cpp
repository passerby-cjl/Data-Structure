//
// Created by Passerby on 2022/3/24.
//
#include "iostream"
using namespace std;
void anxiousWalotta(){
    const int SIZE = 1000;
    int n,m,a;
    cin>>n>>m>>a;
    int farm[SIZE][SIZE] = {0};
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            cin>>farm[i][j];
    int linemin[SIZE][SIZE] = {0};
    int linemax[SIZE][SIZE] = {0};
    for(int j=0;j<m;j++){
        int headmin = 0, tailmin=-1, headmax=0, tailmax=-1;
        short queuemin[SIZE] = {0};
        short queuemax[SIZE] = {0};
        for(int i=0;i<n;i++){
            while(tailmin>=headmin&&farm[queuemin[tailmin]][j]>farm[i][j])
                tailmin--;
            queuemin[++tailmin] = i;
            while(queuemin[headmin]<=i-a)
                headmin++;
            if(i>=a-1) linemin[i-a+1][j]=farm[queuemin[headmin]][j];
            while(tailmax>=headmax&&farm[queuemax[tailmax]][j]<farm[i][j])
                tailmax--;
            queuemax[++tailmax] = i;
            while(queuemax[headmax]<=i-a)
                headmax++;
            if(i>=a-1) linemax[i-a+1][j]=farm[queuemax[headmax]][j];
        }
    }
    int result = 1133773;
    for(int i=0; i<n-a+1; i++){
        int headmin = 0, tailmin=-1, headmax=0, tailmax=-1;
        short queuemin[SIZE] = {0};
        short queuemax[SIZE] = {0};
        for(int j=0;j<m;j++){
            int Min,Max;
            while(tailmin>=headmin&&linemin[i][queuemin[tailmin]]>linemin[i][j])
                tailmin--;
            queuemin[++tailmin] = j;
            while(queuemin[headmin]<=j-a)
                headmin++;
            if(j>=a-1) {
                Min=linemin[i][queuemin[headmin]];
            }
            while(tailmax>=headmax&&linemax[i][queuemax[tailmax]]<linemax[i][j])
                tailmax--;
            queuemax[++tailmax] = j;
            while(queuemax[headmax]<=j-a)
                headmax++;
            if(j>=a-1) {
                Max=linemax[i][queuemax[headmax]];
                result = result<(Max-Min)?result:(Max-Min);
            }
        }
    }
    cout<<result;
}