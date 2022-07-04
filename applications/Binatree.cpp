//
// Created by Passerby on 2022/3/20.
//
#include "iostream"
using namespace std;
const int SIZE = 5000;
struct node{
    int data;
    node *leftson = NULL;
    node *rightson = NULL;
};
void makeTree(node *pointer, int *tempm, const int *tempf, const int length){
    int tlm[SIZE];
    int tlf[SIZE];
    int trm[SIZE];
    int trf[SIZE];
    if(length==1) {
        pointer->data = tempf[0];
        return;
    }
    int i;
    for (i = 0; tempm[i] != tempf[0]; i++) {
        tlm[i] = tempm[i];
        tlf[i] = tempf[i + 1];
    }
    int j;
    for(j=0,i++;i<length;i++,j++) {
        trf[j] = tempf[i];
        trm[j] = tempm[i];
    }
    pointer->data = tempf[0];
    if(length-j-1) {
        pointer->leftson = new node;
        makeTree(pointer->leftson, tlm, tlf, length-j-1);
    }
    if(j) {
        pointer->rightson = new node;
        makeTree(pointer->rightson, trm, trf, j);
    }
    return;
}
void backPrint(node *pointer){
    if(pointer->leftson)
        backPrint(pointer->leftson);
    if(pointer->rightson)
        backPrint(pointer->rightson);
    cout<<pointer->data<<' ';
}
void Binarytree(){
    int n;
    node *root = new node;
    node *pointer = root;
    cin>>n;
    int front[SIZE];
    int mid[SIZE];
    for(int i=0;i<n;i++) cin>>front[i];
    for(int i=0;i<n;i++) cin>>mid[i];
    makeTree(pointer, mid, front, n);
    backPrint(root);
}