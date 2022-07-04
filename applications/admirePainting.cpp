//
// Created by Passerby on 2022/3/23.
//

#include "iostream"
using namespace std;
void admirePainting(){
    int n,m;
    cin>>n>>m;
    short numbers[1000005];
    int *amounts = new int[m+1];
    for(int i=0;i<=m;i++) amounts[i] = 0;
    for(int i=1;i<=n;i++){
        cin>>numbers[i];
    }
    int leftp = 1, rightp = 1;
    amounts[numbers[leftp]] += 1;
    int masternum = 1;
    int minl=1,minr=1,result=n;
    while(rightp<n){
        rightp++;
        if(amounts[numbers[rightp]] == 0)
            masternum++;
        amounts[numbers[rightp]] ++;
        while(masternum==m){
            amounts[numbers[leftp]]--;
            if(amounts[numbers[leftp]]==0) {
                if(rightp-leftp+1<result){
                    result = rightp-leftp+1;
                    minl = leftp;
                    minr = rightp;
                }
                masternum--;
            }
            leftp++;
        }
    }
    cout<<minl<<' '<<minr;
}