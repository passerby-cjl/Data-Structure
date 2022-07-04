#include <iostream>

using namespace std;

template<class T> class LinkedList;
template<class T> class Stack;
template<class T> class Queue;

template<class T>
class Arraynode{
    friend class LinkedList<T>;
    friend class Stack<T>;
    friend class Queue<T>;
private:
    T data;
    Arraynode *next;
public:
    Arraynode(){
        this->next = NULL;
    }
};
template<class T>
class LinkedList{
public:
    int length;
    Arraynode<T> *head;
    Arraynode<T> *tail;
    LinkedList(){
        this->head = new Arraynode<T>;
        this->tail = this->head;
        this->head->next = NULL;
        this->length = 0;
    }
    LinkedList(const LinkedList<T> *that){
        this->head = new Arraynode<T>;
        this->tail = this->head;
        this->head->next = NULL;
        this->length = 0;
        if(that->head->next == NULL) return;
        Arraynode<T> *node_this = this->head;
        Arraynode<T> *node_that = that->head;
        while(node_that->next){
            node_this->next = new Arraynode<T>;
            node_this->next->data = node_that->next->data;
            node_this = node_this->next;
            node_that = node_that->next;
        }
        this->length = that->length;
        node_this->next = NULL;
        this->tail = node_this;
    }
    void pushFront(T _data){
        Arraynode<T> *node = new Arraynode<T>;
        node->next = this->head->next;
        node->data = _data;
        this->head->next = node;
        if(this->length == 0) this->tail = node;
        this->length ++;
    }
    void pushBack(T _data){
        Arraynode<T> *node = new Arraynode<T>;
        this->tail->next = node;
        node->next = NULL;
        node->data = _data;
        this->tail = node;
        this->length++;
    }
    T popFront(){
        if(this->length == 0) return T();
        if(this->length == 1) this->tail = this->head;
        T _data = this->head->next->data;
        Arraynode<T> *temp = this->head->next;
        this->head->next = temp->next;
        delete temp;
        this->length--;
        return _data;
    }
    T popBack(){
        if(this->length == 0) return T();
        T _data = this->tail->data;
        Arraynode<T> *node = this->head;
        while(node->next != this->tail) node = node->next;
        delete this->tail;
        this->tail = node;
        node->next = NULL;
        this->length--;
        return _data;
    }
    int size(){
        return this->length;
    }
    ~LinkedList(){
        Arraynode<T> *node = this->head->next;
        Arraynode<T> *temp;
        while(node != NULL){
            temp = node->next;
            delete node;
            node = temp;
        }
        this->length = 0;
        delete this->head;
    }
    void print(){
        if(this->length == 0) return;
        Arraynode<T> *node = this->head->next;
        while(node->next){
            cout<<node->data<<' ';
            node = node->next;
        }
        cout<<node->data<<endl;
    }
    virtual const char* name(){}
    virtual T peak(){}
    virtual T pop(){}
    virtual void push(T val){}
};

template<class T>
class Stack : public LinkedList<T>{
public:
    const char* name(){
        return "Stack";
    }
    T peak(){
        return this->head->next->data;
    }
    T pop(){
        if(this->length == 0) return T();
        T _data = this->head->next->data;
        Arraynode<T> *temp = this->head->next;
        this->head->next = temp->next;
        delete temp;
        this->length--;
        return _data;
    }
    void push(T val){
        Arraynode<T> *node = new Arraynode<T>;
        if(this->length == 0) this->tail = node;
        node->data = val;
        node->next = this->head->next;
        this->head->next = node;
        this->length ++;
    }
};

template<class T>
class Queue : public LinkedList<T>{
public:
    const char* name(){
        return "Queue";
    }
    T peak(){
        return this->head->next->data;
    }
    T pop(){
        if(this->length == 0) return T();
        if(this->length == 1) this->tail = this->head;
        T _data = this->head->next->data;
        Arraynode<T> *temp = this->head->next;
        this->head->next = temp->next;
        delete temp;
        this->length--;
        return _data;
    }
    void push(T val){
        Arraynode<T> *node = new Arraynode<T>;
        node->data = val;
        node->next = NULL;
        this->tail->next = node;
        this->tail = node;
        this->length ++;
    }
};