//
// Created by Passerby on 2022/3/28.
//

#include "iostream"
using namespace std;
void FireAttack(){
    const int LAYOUR = 31;
    class node{
    public:
        bool is_end;
        bool value;
        node *leftson=NULL;
        node *rightson=NULL;
        node(){}
    };
    int n,m,ai,k;
    node *root = new node;
    node *pointer = root;
    cin>>n>>m;
    for(int i=0;i<n;i++){
        scanf("%d", &ai);
        for(int j=LAYOUR-1;j>=0;j--){
            if(ai/(1<<j)){
                if(!pointer->rightson)
                    pointer->rightson = new node;
                pointer = pointer->rightson;
                ai-=(1<<j);
            }else{
                if(!pointer->leftson)
                    pointer->leftson = new node;
                pointer = pointer->leftson;
            }
        }
        pointer->is_end = true;
        pointer = root;
    }
    for(int i=0;i<m;i++){
        int result=0;
        scanf("%d", &k);
        for(int j=LAYOUR-1;j>=0;j--){
            if(k/(1<<j)){
                if(pointer->leftson) {
                    pointer = pointer->leftson;
                    result += (1<<j);
                }
                else{
                    pointer = pointer->rightson;
                }
                k-=1<<j;
            }else{
                if(pointer->rightson) {
                    pointer = pointer->rightson;
                    result += 1<<j;
                }else{
                    pointer = pointer->leftson;
                }
            }
        }
        pointer = root;
        printf("%d\n", result);
    }
}