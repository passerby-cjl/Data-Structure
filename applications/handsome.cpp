#include<iostream>
#include<cstring>
using namespace std;
int *GetNext(string T, int length){
    int *next = new int[length+1];
    int k=-1;
    int l=0;
    next[0]=-1;
    while(T[l]!='\0'){
        if(k==-1){
            k++;
            l++;
            next[l] = k;
        }else if(T[l] == T[k]){
            k++;
            l++;
            next[l] = k;
        }else k=next[k];
    }
    return next;
}

void handsome(){
    string S,T;
    int lenS=0,lenT=0;
    cin>>S;
    cin>>T;
    lenS=S.size();
    lenT=T.size();
    int *next = GetNext(T, lenT);
    int i=0,j=0;
    while(S[i]!='\0'){
        if(S[i]==T[j]||j==-1){
            i++;
            j++;
        }else j=next[j];
        if(j==lenT){
            cout<<i-j+1<<endl;
            j=0;
            i -= next[lenT];
        }
    }
    for(int c=1;c<=lenT;c++) cout<<next[c]<<' ';
}
