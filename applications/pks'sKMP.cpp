#include "iostream"
#include "cstring"
using namespace std;
void getNext(string S){
    //string S;
    //cin>>S;
    int k = -1;
    int l = 0;
    int *next = new int[S.size()+1];
    next[l] = k;
    while(S[l]!='\0'){
        if(k==-1||S[l] == S[k]){
            k++;
            l++;
            next[l] = k;
        }else k=next[k];
    }
    if(next[S.size()]>1) {
        getNext(S.substr(0, next[S.size()]));
        cout<<next[S.size()]<<endl;
    }
    else if(next[S.size()]==1) cout<<1<<endl;
    return;
    for(int i=0;i<=S.size();i++) cout<<next[i];
}
int pksKMP(){
    string S;
    cin>>S;
    getNext(S);
    cout<<S.size();
}