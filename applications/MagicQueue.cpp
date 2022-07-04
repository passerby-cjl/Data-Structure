#include<iostream>
using namespace std;


/*void queue(){
    int N;
    cin>>N;
    int *array = new int[N];
    array[0] = -1;
    array[1] = 0;
    int k, lr;
    for(int i=2;i<=N;i++){
        cin>>k>>lr;
        for(int j=1;j<i;j++)
            if(array[j]>array[k]) array[j]++;
        if(!lr) array[i] = array[k]++;
        else array[i] = array[k]+1;
    }
    int M,m;
    cin>>M;
    for(int i=0;i<M;i++){
        cin>>m;
        if(m<=N) array[m]=-1;
    }
    for(int j=0;j<N;j++)
    for(int i=1;i<=N;i++)
        if(array[i]==j){
            cout<<i<<' ';
            break;
        }
    cout<<endl;
}*/
/*
class MagicQueue{
private:
    class Magicnode{
    public:
        int num;
        Magicnode *next;
    };
    Magicnode *head;
    Magicnode *findnum(int _num){
        Magicnode *temp = this->head;
        while(temp->next->next != NULL && temp->next->num != _num) temp = temp->next;
        if(temp->next->num != _num) return NULL;
        return temp;
    }
    void insert(int _num, int p, int i){
        Magicnode *temp = new Magicnode;
        Magicnode *k = findnum(_num);
        temp->num = i;
        if(p){
            temp->next = k->next->next;
            k->next->next = temp;
        }else{
            temp->next = k->next;
            k->next = temp;
        }
    }
    void del(int _num){
        Magicnode *k = findnum(_num);
        if(k != NULL){
            Magicnode *temp = k->next;
            k->next = k->next->next;
            delete temp;
        }
    }
    void print(){
        Magicnode *temp = this->head->next;
        while(temp->next!=NULL) {
            cout<<temp->num<<' ';
            temp = temp->next;
        }
        cout<<temp->num<<endl;
    }
public:
    MagicQueue(){
        this->head = new Magicnode;
        Magicnode *temp = new Magicnode;
        temp->num = 1;
        temp->next = NULL;
        this->head->next = temp;
    }
    void process(){
        int M, N;
        cin>>N;
        for(int i=2;i<=N;i++){
            int k,p;
            cin>>k>>p;
            insert(k, p, i);
        }
        cin>>M;
        for(int i=0;i<M;i++){
            int m;
            cin>>m;
            del(m);
        }
        print();
    }
};*/
int *leftof;
int *rightof;
bool *out;
void insert(int k, int p, int i){
    if(p){
        rightof[i] = rightof[k];
        leftof[rightof[k]] = i;
        leftof[i] = k;
        rightof[k] = i;
    }else{
        leftof[i] = leftof[k];
        rightof[leftof[k]] = i;
        rightof[i] = k;
        leftof[k] = i;
    }
}
void queueup(int N){
    leftof = new int[N+1];
    rightof = new int[N+1];
    leftof[1] = 0;
    rightof[1] = 0;
    leftof[0] = 1;
    rightof[0] = 1;
    for(int i=2;i<=N;i++){
        int k, p;
        cin>>k>>p;
        insert(k, p, i);
    }
}

void del(int M, int N){
    out = new bool[N+1];
    int m;
    for(int i=0;i<M;i++){
        cin>>m;
        out[m] = true;
    }
}

void print(){
    int i = rightof[0];
    //for(i=1;leftof[i]!=0;i++){}
    while(rightof[i] != 0){
        if(!out[i]) cout<<i<<' ';
        i=rightof[i];
    }
    if(!out[i]) cout<<i<<endl;
}

void process(){
    int M,N;
    cin>>N;
    queueup(N);
    cin>>M;
    del(M, N);
    print();
}
