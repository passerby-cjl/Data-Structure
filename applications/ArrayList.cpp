#include<iostream>
#define USE_OS
using namespace std;

class error : public exception {
private:
    string msg;

public:
    explicit error(const char *_msg_) : msg(_msg_) {}

    const char *toString() {
        return msg.c_str();
    }
};

template<class T>
class ArrayList{
    template<class Type>
    friend ostream &operator<<(ostream &os,const ArrayList<Type> &arr2);
private:
    int length;
    T *arr;
public:
    ArrayList(T *_arr, int _length){
        if(_length < 0) throw error("invalid length");
        this->length = _length;
        this->arr = new T[_length];
        for(int i=0;i<_length;i++) this->arr[i] = _arr[i];
    }
    ArrayList(int _length){
        if(_length < 0) throw error("invalid length");
        this->length = _length;
        this->arr = new T[_length];
        for(int i=0;i<_length;i++) this->arr[i] = T();
    }
    ArrayList(const ArrayList &al){
        if(this == &al) return;
        this->length = al.length;
        this->arr = new T[this->length];
        for(int i=0;i<this->length;i++) this->arr[i] = al.arr[i];
    }
    ArrayList(){
        this->length = 0;
        this->arr = NULL;
    }
    ~ArrayList(){
        delete [] arr;
        length = 0;
    }
    int size() const{return length;}
    ArrayList operator+(const ArrayList &arr2) const{
        ArrayList dst = ArrayList(this->length + arr2.length);
        for(int i=0;i<this->length;i++) dst[i] = this->arr[i];
        for(int i=0;i<arr2.length;i++) dst[i+this->length] = arr2.arr[i];
        return dst;
    }
    void print()const{
    for(int i=0;i<size()-1;i++) cout<<arr[i]<<' ';
    cout<<arr[size()-1];
    }
    ArrayList &operator=(const ArrayList &arr2){
        if(this == &arr2) return *this;
        this->length = arr2.length;
        delete [] this->arr;
        this->arr = new T[this->length];
        for(int i=0;i<this->length;i++) this->arr[i] = arr2.arr[i];
        return *this;
    }
    bool operator==(const ArrayList<T> &arr2)const{
        if(this->length != arr2.length) return 0;
        for(int i=0;i<this->length;i++)
            if(arr[i] == arr2[i]) continue;
            else return 0;
        return 1;
    }
    bool operator!=(const ArrayList<T> &arr2)const{
        if(this->size() != arr2.size()) return 1;
        for(int i=0;i<this->size();i++)
            if(arr[i] == arr2[i]) continue;
            else return 1;
        return 0;
    }
    T &operator[](int index){
        if(index < 0 || index >= this->size()) throw error("index out of bound");
        return this->arr[index];
    }
    const T operator[](int index) const{
        if(index < 0 || index >= this->size()) throw error("index out of bound");
        return arr[index];
    }
};
template<class T>
ostream &operator<<(ostream &os, const ArrayList<T> &arr2){
    for(int i=0;i<arr2.size()-1;i++) os<<arr2[i]<<' ';
    os<<arr2[arr2.size()-1];
    return os;
}
