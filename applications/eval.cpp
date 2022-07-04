//
// Created by Passerby on 2022/3/20.
//
#include "cstring"
#include "iostream"
using namespace std;
struct node{
    node *leftson=NULL;
    node *rightson=NULL;
    int data=-6;
};
int getValue(string toCal, int &pointer){
    int answer = 0;
    if(isdigit(toCal[pointer]))
        while(isdigit(toCal[pointer]))
            answer = answer*10+toCal[pointer++]-48;
    else{
        switch (toCal[pointer++]) {
            case '+':
                answer=-1;
                break;
            case '-':
                answer=-2;
                break;
            case '^':
                answer=-3;
                break;
            case '(':
                answer=-4;
                break;
            case ')':
                answer=-5;
                break;
        }
    }
    return answer;
}
int getResult(node *root){
    int rl, rr;
    switch (root->data) {
        case -1:
            rl = getResult(root->leftson);
            rr = getResult(root->rightson);
            return rl+rr;
        case -2:
            rl = getResult(root->leftson);
            rr = getResult(root->rightson);
            return rl-rr;
        case -3:
            rl = getResult(root->leftson);
            rr = getResult(root->rightson);
            return rl^rr;
        default:
            return root->data;
    }
}
string getSub(string origin, int &pointer){
    int counter = 1;
    int num = 0;
    while(counter){
        if(origin[pointer+num]==')')
            --counter;
        else if(origin[pointer+num] == '(')
            ++counter;
        ++num;
    }
    string sub = origin.substr(pointer, num-1);
    pointer = pointer + num;
    return sub;
}
node *makeTree(string toCal){
    node *root = new node;
    node *ptree = root;
    int pointer = 0;
    while(toCal[pointer]){
        int answer = getValue(toCal, pointer);
        if(answer>=0){
            if(ptree->data==-6) {
                ptree->data = answer;
            }else{
                ptree->rightson = new node;
                ptree = ptree->rightson;
                ptree->data = answer;
            }
        }else if(answer==-4){
            node *temp = makeTree(getSub(toCal, pointer));
            if(root->data==-6)
                if(toCal[pointer] == 0)
                    root = temp;
                else{
                    root->leftson = temp;
                    root->data = getValue(toCal, pointer);
                    ptree = root;
                }
            else {
                ptree->rightson = temp;
                ptree = temp;
            }
        }else if(answer==-3||root->data>-3){
            node *temp = new node;
            temp->leftson = root;
            temp->data = answer;
            root = temp;
            ptree = root;
        }else if(answer>-3){
            node *temp = new node;
            temp->data=answer;
            temp->leftson = root->rightson;
            root->rightson = temp;
            ptree = temp;
        }
    }
    return root;

}
void eval(){
    string toCal;
    cin>>toCal;
    node *root = makeTree(toCal);
    int result = getResult(root);
    cout<<result;
}
