#ifndef BPT_MEMORYRIVER_HPP
#define BPT_MEMORYRIVER_HPP

#include <fstream>
#include<ios>
#include<iostream>

using std::string;
using std::fstream;
using std::ifstream;
using std::ofstream;

template<class T, int info_len = 2>
class MemoryRiver {
private:
    /* your code here */
    int length=0;
    int dele=0;
    fstream file;
    string file_name;
    int sizeofT = sizeof(T);
    struct Blocks{
        int next;
        T data;
    };
public:
    MemoryRiver() = default;

    MemoryRiver(const string& file_name) : file_name(file_name) {}

    void initialise(string FN = "") {
        if (FN != "") file_name = FN;
        file.open(file_name, std::ios::out|std::ios::trunc|std::ios::binary);
        int tmp = 0;
        for (int i = 0; i < info_len; ++i)
            file.write(reinterpret_cast<char *>(&tmp), sizeof(int));
        file.close();
    }

    //读出第n个int的值赋给tmp，1_base
    void get_info(int &tmp, int n) {
        if (n > info_len) return;
        file.open(file_name, std::ios::in|std::ios::out|std::ios::binary);
        file.seekg((n-1)*sizeof(int));
        file.read(reinterpret_cast<char *>(&tmp), sizeof(int));
        file.close();
        /* your code here */
    }

    //将tmp写入第n个int的位置，1_base
    void write_info(int tmp, int n) {
        if (n > info_len) return;
        file.open(file_name, std::ios::out|std::ios::in|std::ios::binary);
        file.seekp((n-1)*sizeof(int));
        file.write(reinterpret_cast<char *>(&tmp), sizeof(int));
        file.close();

        /* your code here */
    }

    //在文件合适位置写入类对象t，并返回写入的位置索引index
    //位置索引意味着当输入正确的位置索引index，在以下三个函数中都能顺利的找到目标对象进行操作
    //位置索引index可以取为对象写入的起始位置
    int write(T &t) {
        int index;//, length;
        Blocks temp;
        //get_info(index, 1);
        index = dele;
        //get_info(length, 2);
        if(index == 0) index = length;
        else{
            file.open(file_name, std::ios::out|std::ios::in|std::ios::binary);
            file.seekg(2*sizeof(int)+index*sizeof(Blocks));
            file.read(reinterpret_cast<char*>(&temp), sizeof(Blocks));
            file.close();
            //write_info(temp.next, 1);
            dele = temp.next;
        }
        //write_info(length+1, 2);
        length ++;
        file.open(file_name, std::ios::out|std::ios::in|std::ios::binary);
        temp.data = t;
        temp.next = 0;
        file.seekp(2*sizeof(int)+index*sizeof(Blocks));
        file.write(reinterpret_cast<char*>(&temp), sizeof(Blocks));
        file.close();
        return index;

        /* your code here */
    }

    //用t的值更新位置索引index对应的对象，保证调用的index都是由write函数产生
    void update(T &t, const int index) {
        Blocks temp;
        temp.data = t;
        temp.next = 0;
        file.open(file_name, std::ios::out|std::ios::in|std::ios::binary);
        file.seekp(2*sizeof(int)+index*sizeof(Blocks));
        file.write(reinterpret_cast<char*>(&temp), sizeof(Blocks));
        file.close();
        /* your code here */
    }

    //读出位置索引index对应的T对象的值并赋值给t，保证调用的index都是由write函数产生
    void read(T &t, const int index) {
        Blocks temp;
        file.open(file_name, std::ios::in|std::ios::binary);
        file.seekg(2*sizeof(int)+index*sizeof(Blocks));
        file.read(reinterpret_cast<char*>(&temp), sizeof(Blocks));
        file.close();
        t = temp.data;
        /* your code here */
    }

    //删除位置索引index对应的对象(不涉及空间回收时，可忽略此函数)，保证调用的index都是由write函数产生
    void Delete(int index) {
        Blocks temp;
        int tmp;//,length;
        //get_info(tmp, 1);
        tmp = dele;
        //write_info(index, 1);
        dele = index;
        temp.next = tmp;
        //get_info(length, 2);
        //write_info(length-1, 2);
        length --;
        file.open(file_name, std::ios::out|std::ios::in|std::ios::binary);
        file.seekp(2*sizeof(int)+index*sizeof(Blocks));
        file.write(reinterpret_cast<char*>(&temp), sizeof(Blocks));
        file.close();
        /* your code here */
    }
};
#endif //BPT_MEMORYRIVER_HPP


