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

    //������n��int��ֵ����tmp��1_base
    void get_info(int &tmp, int n) {
        if (n > info_len) return;
        file.open(file_name, std::ios::in|std::ios::out|std::ios::binary);
        file.seekg((n-1)*sizeof(int));
        file.read(reinterpret_cast<char *>(&tmp), sizeof(int));
        file.close();
        /* your code here */
    }

    //��tmpд���n��int��λ�ã�1_base
    void write_info(int tmp, int n) {
        if (n > info_len) return;
        file.open(file_name, std::ios::out|std::ios::in|std::ios::binary);
        file.seekp((n-1)*sizeof(int));
        file.write(reinterpret_cast<char *>(&tmp), sizeof(int));
        file.close();

        /* your code here */
    }

    //���ļ�����λ��д�������t��������д���λ������index
    //λ��������ζ�ŵ�������ȷ��λ������index�����������������ж���˳�����ҵ�Ŀ�������в���
    //λ������index����ȡΪ����д�����ʼλ��
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

    //��t��ֵ����λ������index��Ӧ�Ķ��󣬱�֤���õ�index������write��������
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

    //����λ������index��Ӧ��T�����ֵ����ֵ��t����֤���õ�index������write��������
    void read(T &t, const int index) {
        Blocks temp;
        file.open(file_name, std::ios::in|std::ios::binary);
        file.seekg(2*sizeof(int)+index*sizeof(Blocks));
        file.read(reinterpret_cast<char*>(&temp), sizeof(Blocks));
        file.close();
        t = temp.data;
        /* your code here */
    }

    //ɾ��λ������index��Ӧ�Ķ���(���漰�ռ����ʱ���ɺ��Դ˺���)����֤���õ�index������write��������
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


