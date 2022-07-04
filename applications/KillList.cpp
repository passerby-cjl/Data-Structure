//
// Created by Passerby on 2022/4/3.
//
#include "iostream"
using namespace std;
const int SIZE=1e6;
int tree[SIZE][26]={0};
int fail[SIZE];
int thisLayour[SIZE];
int nextLayour[SIZE];
bool isend[SIZE]={0};
int total = 0;
void BFS(int length){
    int counter=0;
    for(int j=0;j<length;j++) {
        for (int i = 0; i < 26; i++)
            if (tree[thisLayour[j]][i]) {
                int prev = fail[thisLayour[j]];
                while (1) {
                    if (prev==-1||tree[prev][i]) break;
                    prev = fail[prev];
                }
                if(prev==-1) fail[tree[thisLayour[j]][i]] = 0;
                else fail[tree[thisLayour[j]][i]] = tree[prev][i];
                nextLayour[counter++] = tree[thisLayour[j]][i];
            }
    }
    for(int i=0;i<counter;i++)
        thisLayour[i] = nextLayour[i];
    if(counter)
        BFS(counter);
}
void KillList(){
    int n;
    scanf("%d\n",&n);
    int pointer = 0;
    for(int i=0;i<n;i++){
        while(1){
            char ch;
            scanf("%c", &ch);
            if(ch=='\n') break;
            if(!tree[pointer][ch-'a'])
                tree[pointer][ch-'a'] = ++total;
            pointer = tree[pointer][ch-'a'];
        }
        isend[pointer] = true;
        pointer=0;
    }
    thisLayour[0]=0;
    fail[0]=-1;
    BFS(1);
    char text[SIZE];
    scanf("%s", text);
    for(int i=0;text[i];i++){
        if(tree[pointer][text[i]-'a']){
            pointer = tree[pointer][text[i]-'a'];
        }else{
            if(pointer) {
                pointer = fail[pointer];
                --i;
            }
        }
        if(isend[pointer]){
            cout<<"valar morghulis";
            return;
        }
    }
    cout<<"valar dohaeris";
}