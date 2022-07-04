#include<iostream>
using namespace std;
class EasyLinkedList{
private:
    class Easynode{
    public:
        int num;
        Easynode *next;
    };
    Easynode *head;
    Easynode *findnum(int _num){
        if(_num == 0){
            Easynode *temp = new Easynode;
            temp->next = this->head;
            return temp;
        }
        Easynode *temp = this->head;
        int counter=1;
        while(counter < _num) {
            temp = temp->next;
            counter++;
        }
        return temp;
    }
    void init(int N){
        Easynode *iter = this->head;;
        for(int i=0;i<N;i++){
            int k;
            cin>>k;
            Easynode *temp = new Easynode;
            temp->num = k;
            temp->next = NULL;
            iter->next = temp;
            iter = temp;
        }
    }
    void append(int _num, int i){
        Easynode *temp = new Easynode;
        Easynode *k = findnum(_num);
        temp->num = i;
        temp->next = k->next->next;
        k->next->next = temp;
    }
    void del(int _num){
        Easynode *k = findnum(_num);
        if(k != NULL){
            Easynode *temp = k->next;
            k->next = k->next->next;
            delete temp;
        }
    }
    void print(){
        Easynode *temp = this->head->next;
        while(temp->next!=NULL) {
            cout<<temp->num<<' ';
            temp = temp->next;
        }
        cout<<temp->num<<endl;
    }
public:
    EasyLinkedList(){
        this->head = new Easynode;
        this->head->next = NULL;
    }
    void process(){
        int M, N;
        cin>>N>>M;
        init(N);
        for(int i=0;i<M;i++){
            int m;
            cin>>m;
            if(m==1) {
                int a,b;
                cin>>a>>b;
                append(a, b);
            }else{
                int a;
                cin>>a;
                del(a);
            }
        }
        print();
    }
};
