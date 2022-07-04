#include "iostream"
#include "cstring"
using namespace std;
string unzip(string zipped){
    string unzipped;
    string temp;
    int times=0;
    int l;
    for(l=0;l<zipped.size();l++){
        if(isalpha(zipped[l])) unzipped += zipped[l];
        if(isdigit(zipped[l])) {
            int layour = 0;
            while (zipped[l] != '[') {
                times = times * 10 + zipped[l] - 48;
                l++;
            }
            layour++;
            l++;
            while(layour){
                if(zipped[l]=='[') layour++;
                if(zipped[l]==']') layour--;
                if(layour) {
                    temp+=zipped[l];
                    l++;
                }
            }
            temp = unzip(temp);
            for(int i=0;i<times;i++) unzipped+=temp;
            temp = "";
            times = 0;
        }
    }
    return unzipped;
}
void tiptrick(){
    string unzipped,zipped;
    cin>>zipped;
    unzipped = unzip(zipped);
    cout<<unzipped;
}