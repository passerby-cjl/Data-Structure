#include<iostream>
using namespace std;
void SpringBattle(){
    int N,M;
    cin>>N>>M;
    int length = N;
    int out[100005] = {0};
    int pointer = 1;
    int step = 1;
    while(length>1){
        pointer --;//扣除刚删掉的那个人
        pointer += M;
        length--;
        if(((pointer-1)/length)%2) step *= -1;
        pointer = pointer % length;
        if(!pointer) pointer = length;
        if(step == -1) out[N-length-1] = length + 2 - pointer;
        else out[N-length-1] = pointer;
    }
    int position = 1;
    for(int i=N-2;i>=0;i--)
        if(out[i] <= position) position++;
    cout<<position<<endl;
}


/*1 2 3 4 5 6 7 8 9
struct SpringNode{
    SpringNode *next;
    SpringNode *prev;
    int num;
};

void listout(){
    int M, N;
    cin>>N>>M;
    SpringNode *head = new SpringNode;
    SpringNode *p = head;
    for(int i=0;i<N;i++){
        SpringNode *temp = new SpringNode;
        p->next = temp;
        temp->prev = p;
        temp->num = i+1;
        p = temp;
    }
    for(int i=0;i<N;i++){
        p->next
    }
    p = head->next;
    while(N>1){
        int m=M%(2*(length-1));
        if(m==0||m==1) m += 2*(length-1);
        for(int i=0;i<m;i++){
            if(p->next)
        }
    }
}

void SpringBattle(){
    int N,M;
    cin>>N>>M;
    int n=1;
    int
    for(int i=2;i<=N;i++){
        if(M%i>=n) n++;
    }

}
*/
