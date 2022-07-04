//
// Created by Passerby on 2022/5/10.
//

#ifndef DATA_STRUCTURE_B_TREE_HPP
#define DATA_STRUCTURE_B_TREE_HPP

#endif //DATA_STRUCTURE_B_TREE_HPP

#include <functional>
#include <cstddef>
#include "iostream"
#include "fstream"
#include "exceptions.hpp"
#include "utility.hpp"

namespace sjtu {
    template<class Key, class Value>
    class BTree {
    private:
        const static int M = 228, L = 8192 / sizeof(pair<Key, Value>);//bytes taken by B+tree
        struct FNode {
            size_t pointer = 0;
            FNode *father = nullptr;
        };

        class BNode {
        public:
            int sonnum = 0;
            size_t nextleaf = 0;
            Key keylist[M];
            size_t sonlist[M];//son's index in file
            BNode() = default;

            bool isBleaf() { return false; }
        };

        class Bleaf {
        public:
            int sonnum = 0;
            size_t nextleaf = 0;//nextleaf's index
            Key keylist[L];
            Value sonlist[L];

            Bleaf() = default;

            bool isBleaf() { return true; }
        };

        const char *file_name;
        std::fstream file;
        size_t root = 0;//root's index in file
        size_t height = 0;
        size_t nxtEmpNpos = 0;
        size_t nxtEmpLpos = 0;

        // Your private members go here
        void delfnode(FNode *fNode) {
            FNode *p, *temp = fNode;
            while (temp->father) {
                p = temp;
                temp = p->father;
                delete p;
            }
            delete temp;
        }

        template<class T>
        size_t split(T &t){
            size_t len = t.isBleaf()?L:M;
            T ntemp;
            if (t.sonnum != len) throw runtime_error();
            ntemp.sonnum = len - len / 2;
            t.sonnum = len / 2;
            for (int i = len / 2; i < len; i++) {
                ntemp.keylist[i - len / 2] = t.keylist[i];
                ntemp.sonlist[i - len / 2] = t.sonlist[i];
            }
            ntemp.nextleaf = t.nextleaf;
            size_t npointer = write(ntemp);
            if(t.isBleaf()) t.nextleaf = npointer;
            return npointer;
        }

        pair<bool, int> binasearch(const Key *arr, const Key &key, int length) {
            int l = -1, r = length, m;
            while (l + 1 < r) {
                m = (l + r) >> 1;
                if (arr[m] > key) r = m;
                else l = m;
            }
            m = (l + r) >> 1;
            if (arr[m] > key) return pair<bool, int>(false, -1);
            if (arr[m] == key) return pair<bool, int>(true, m);
            return pair<bool, int>(false, m);
        }

        pair<size_t, FNode *> findleaf(const Key &key) {//return index of Bleaf
            if (!root) return pair<size_t, FNode *>(0, nullptr);
            size_t deep = height;
            size_t pointer = root;
            BNode temp;
            FNode *ftemp = new FNode;
            ftemp->pointer = root;
            while (--deep) {
                FNode *f = new FNode;
                f->father = ftemp;
                read(temp, pointer);
                pointer = temp.sonlist[binasearch(temp.keylist, key, temp.sonnum - 1).second + 1];
                f->pointer = pointer;
                ftemp = f;
            }
            return pair<size_t, FNode *>(pointer, ftemp);
        }


        template<class T>
        void update(T &t, const size_t pointer) {
            file.seekp(pointer);
            file.write(reinterpret_cast<char *>(&t), sizeof(T));
            if (file.fail()) throw runtime_error();
        }

        template<class T>
        void read(T &t, const size_t pointer) {
            file.seekg(pointer);
            if (file.eof()) throw runtime_error();
            file.read(reinterpret_cast<char *>(&t), sizeof(T));
        }

        template<class T>
        size_t write(T &t) {
            size_t pointer;
            if (t.isBleaf()) pointer = nxtEmpLpos;
            else pointer = nxtEmpNpos;
            if (!pointer) {
                file.seekp(0, std::ios_base::end);
                pointer = file.tellp();
            } else {
                file.seekg(pointer);
                size_t nxtempty;
                file.read(reinterpret_cast<char *>(&nxtempty), sizeof(size_t));
                if (t.isBleaf()) nxtEmpLpos = nxtempty;
                else nxtEmpNpos = nxtempty;
                file.seekp(pointer);
            }
            file.write(reinterpret_cast<char *>(&t), sizeof(T));
            if (file.fail()) throw runtime_error();
            return pointer;
        }

        template<class T>
        void del(size_t pointer) {
            size_t tpointer;
            if (T().isBleaf()) {
                tpointer = nxtEmpLpos;
                nxtEmpLpos = pointer;
            } else {
                tpointer = nxtEmpNpos;
                nxtEmpNpos = pointer;
            }
            file.seekp(pointer);
            file.write(reinterpret_cast<char *>(&tpointer), sizeof(size_t));
            if (file.fail()) throw runtime_error();
        }

        template<class T1, class T2>
        void adjustadd(T1 &temp, size_t pointer, Key key, T2 value, FNode *fnode) {
            int i = temp.sonnum - 1 - !temp.isBleaf();
            for (; i >= 0 && temp.keylist[i] > key; i--) {
                temp.keylist[i + 1] = temp.keylist[i];
                temp.sonlist[i + 1 + !temp.isBleaf()] = temp.sonlist[i + !temp.isBleaf()];
            }
            temp.sonnum++;
            temp.keylist[i + 1] = key;
            temp.sonlist[i + 1 + !temp.isBleaf()] = value;
            if (temp.sonnum < (temp.isBleaf() ? L : M)) {
                update(temp, pointer);
                return;
            }
            if (pointer == root) {
                BNode nroot;
                root = write(nroot);
                size_t npointer = split(temp);
                nroot.sonnum = 2;
                nroot.keylist[0] = temp.keylist[(temp.isBleaf() ? L / 2 : M / 2 - 1)];
                update(temp, pointer);
                nroot.sonlist[0] = pointer;
                nroot.sonlist[1] = npointer;
                update(nroot, root);
                height++;
                return;
            }
            size_t npointer = split(temp);
            update(temp, pointer);
            BNode father;
            read(father, fnode->father->pointer);
            adjustadd<BNode, size_t>(father, fnode->father->pointer, temp.keylist[temp.isBleaf() ? L / 2 : M / 2 - 1],
                                     npointer, fnode->father);
        }

        template<class T>
        void adjustsub(T &temp, size_t pointer, int index, FNode *fnode) {
            if (pointer == root) {
                for (int i = index; i < temp.sonnum - 1 - (!temp.isBleaf()); i++) {
                    temp.keylist[i] = temp.keylist[i + 1];
                    temp.sonlist[i + (!temp.isBleaf())] = temp.sonlist[i + 1 + (!temp.isBleaf())];
                }
                temp.sonnum--;
                update(temp, pointer);
                if (temp.sonnum == 1 && !temp.isBleaf()) {
                    root = temp.sonlist[0];
                    del<T>(pointer);
                    height--;
                } else if (!temp.sonnum) {
                    clear();
                }
                return;
            }
            BNode father;
            read(father, fnode->father->pointer);
            int tmp_in_f = binasearch(father.keylist, temp.keylist[0], father.sonnum - 1).second;
            for (int i = index; i < temp.sonnum - 1 - (!temp.isBleaf()); i++) {
                temp.keylist[i] = temp.keylist[i + 1];
                temp.sonlist[i + (!temp.isBleaf())] = temp.sonlist[i + 1 + (!temp.isBleaf())];
            }
            if (temp.isBleaf() && !index && tmp_in_f >= 0) {
                father.keylist[tmp_in_f] = temp.keylist[0];
                update(father, fnode->father->pointer);
            }
            temp.sonnum--;
            if (temp.sonnum >= (temp.isBleaf() ? L / 2 : M / 2)) {
                update(temp, pointer);
                return;
            }
            if (tmp_in_f != -1) {
                T bro;
                read(bro, father.sonlist[tmp_in_f]);//temp左侧
                if (bro.sonnum > (temp.isBleaf() ? L / 2 : M / 2)) {
                    for (int i = temp.sonnum; i > 0; i--) {
                        temp.keylist[i] = temp.keylist[i - 1];
                        temp.sonlist[i] = temp.sonlist[i - 1];
                    }
                    if (!temp.isBleaf())
                        temp.keylist[0] = father.keylist[tmp_in_f];
                    else
                        temp.keylist[0] = bro.keylist[bro.sonnum - 1];
                    temp.sonlist[0] = bro.sonlist[bro.sonnum - 1];
                    father.keylist[tmp_in_f] = bro.keylist[bro.sonnum - 1 - (!temp.isBleaf())];
                    bro.sonnum--;
                    temp.sonnum++;
                    update(father, fnode->father->pointer);
                    update(bro, father.sonlist[tmp_in_f]);
                    update(temp, pointer);
                    return;
                }
            }
            if (tmp_in_f != father.sonnum - 2) {
                T bro;
                read(bro, father.sonlist[tmp_in_f + 2]);
                if (bro.sonnum > (temp.isBleaf() ? L / 2 : M / 2)) {
                    if (temp.isBleaf()) temp.keylist[temp.sonnum] = bro.keylist[0];
                    else temp.keylist[temp.sonnum - 1] = father.keylist[tmp_in_f + 1];
                    father.keylist[tmp_in_f + 1] = bro.keylist[temp.isBleaf()];
                    temp.sonlist[temp.sonnum] = bro.sonlist[0];
                    for (int i = 0; i < bro.sonnum - 1; i++) {
                        bro.keylist[i] = bro.keylist[i + 1];
                        bro.sonlist[i] = bro.sonlist[i + 1];
                    }
                    bro.sonnum--;
                    temp.sonnum++;
                    update(father, fnode->father->pointer);
                    update(bro, father.sonlist[tmp_in_f + 2]);
                    update(temp, pointer);
                    return;
                }
            }
            if (tmp_in_f != -1) {
                T bro;
                read(bro, father.sonlist[tmp_in_f]);
                if (!temp.isBleaf())
                    bro.keylist[bro.sonnum - 1] = father.keylist[tmp_in_f];
                for (int i = 0; i < temp.sonnum; i++) {
                    bro.keylist[bro.sonnum] = temp.keylist[i];
                    bro.sonlist[bro.sonnum++] = temp.sonlist[i];
                }
                if (temp.isBleaf())
                    bro.nextleaf = temp.nextleaf;
                del<T>(pointer);
                update(bro, father.sonlist[tmp_in_f]);
                adjustsub(father, fnode->father->pointer, tmp_in_f, fnode->father);
                return;
            } else {
                T bro;
                read(bro, father.sonlist[tmp_in_f + 2]);
                if (!temp.isBleaf())
                    temp.keylist[temp.sonnum - 1] = father.keylist[tmp_in_f + 1];
                for (int i = 0; i < bro.sonnum; i++) {
                    temp.keylist[temp.sonnum] = bro.keylist[i];
                    temp.sonlist[temp.sonnum++] = bro.sonlist[i];
                }
                if (temp.isBleaf())
                    temp.nextleaf = bro.nextleaf;
                del<T>(father.sonlist[tmp_in_f + 2]);
                update(temp, pointer);
                adjustsub(father, fnode->father->pointer, tmp_in_f + 1, fnode->father);
                return;
            }
        }

    public:
        BTree() {
            file_name = "temp.txt";
            size_t tmp = 0;
            std::ifstream f(file_name);
            if (!f.good()) {
                file.open(file_name, std::ios::out | std::ios::in | std::ios::binary | std::ios::trunc);
                for (int i = 0; i < 4; ++i)
                    file.write(reinterpret_cast<char *>(&tmp), sizeof(tmp));
            } else {
                file.open(file_name, std::ios::out | std::ios::in | std::ios::binary);
                read(nxtEmpNpos, 0);
                read(nxtEmpLpos, 1 * sizeof(size_t));
                read(root, 2 * sizeof(size_t));
                read(height, 3 * sizeof(size_t));
            }
        }

        BTree(const char *fname) : file_name(fname) {
            size_t tmp = 0;
            std::ifstream f(file_name);
            if (!f.good()) {
                file.open(file_name, std::ios::in | std::ios::out | std::ios::binary | std::ios::trunc);
                for (int i = 0; i < 4; ++i)
                    file.write(reinterpret_cast<char *>(&tmp), sizeof(tmp));
            } else {
                file.open(file_name, std::ios::in | std::ios::out | std::ios::binary);
                read(nxtEmpNpos, 0);
                read(nxtEmpLpos, 1 * sizeof(size_t));
                read(root, 2 * sizeof(size_t));
                read(height, 3 * sizeof(size_t));
            }
        }

        ~BTree() {
            file.seekp(0);
            file.write(reinterpret_cast<char *>(&nxtEmpNpos), sizeof(nxtEmpNpos));
            file.write(reinterpret_cast<char *>(&nxtEmpLpos), sizeof(nxtEmpLpos));
            file.write(reinterpret_cast<char *>(&root), sizeof(root));
            file.write(reinterpret_cast<char *>(&height), sizeof(height));
            file.close();
        }

        // Clear the BTree
        void clear() {
            size_t tmp = 0;
            for (int i = 0; i < 4; ++i)
                file.write(reinterpret_cast<char *>(&tmp), sizeof(tmp));
            root = 0;
            height = 0;
            nxtEmpNpos = 0;
            nxtEmpLpos = 0;
        }

        bool insert(const Key &key, const Value &value) {
            if (!height) {
                Bleaf leaf;
                leaf.sonlist[0] = value;
                leaf.keylist[0] = key;
                leaf.sonnum++;
                root = write(leaf);
                height++;
                return true;
            }
            pair<size_t, FNode *> result = findleaf(key);
            Bleaf leaf;
            read(leaf, result.first);
            if (binasearch(leaf.keylist, key, leaf.sonnum).first) {
                delfnode(result.second);
                return false;
            }
            adjustadd<Bleaf, Value>(leaf, result.first, key, value, result.second);
            delfnode(result.second);
            return true;
        }

        bool modify(const Key &key, const Value &value) {
            pair<size_t, FNode *> lresult = findleaf(key);
            size_t pointer = lresult.first;
            delfnode(lresult.second);
            Bleaf leaf;
            read(leaf, pointer);
            pair<bool, int> result = binasearch(leaf.keylist, key, leaf.sonnum);
            if (!result.first) return false;
            leaf.sonlist[result.second] = value;
            update(leaf, pointer);
            return true;
        }

        Value at(const Key &key) {
            if (!height) return Value();
            pair<size_t, FNode *> lresult = findleaf(key);
            size_t pointer = lresult.first;
            delfnode(lresult.second);
            Bleaf leaf;
            read(leaf, pointer);
            pair<bool, int> result = binasearch(leaf.keylist, key, leaf.sonnum);
            if (!result.first) return Value();
            return leaf.sonlist[result.second];
        }

        bool erase(const Key &key) {
            pair<size_t, FNode *> lresult = findleaf(key);
            size_t pointer = lresult.first;
            Bleaf leaf;
            read(leaf, pointer);
            pair<bool, int> result = binasearch(leaf.keylist, key, leaf.sonnum);
            if (!result.first) return false;
            adjustsub(leaf, pointer, result.second, lresult.second);
            delfnode(lresult.second);
            return true;
        }


        class iterator {
        private:
            // Your private members go here
            BTree<Key, Value> *father;
            int index;
            size_t pointer;

            int binasearch(Key *arr, Key key, size_t length) {
                int l = 0, r = length - 1, m;
                while (l < r) {
                    m = (l + r + 1) >> 1;
                    if (arr[m] >= key) r = m - 1;
                    if (arr[m] < key) l = m;
                }
                m = (l + r) >> 1;
                if (arr[m] > key) return -1;
                return m;
            }

        public:
            iterator() = default;

            iterator(BTree<Key, Value> *_f, int _index, size_t _pointer) {
                father = _f;
                index = _index;
                pointer = _pointer;
            }

            iterator(const iterator &other) {
                father = other.father;
                index = other.index;
                pointer = other.pointer;
            }

            // modify by iterator
            bool modify(const Value &value) {
                Bleaf leaf;
                father->read(leaf, pointer);
                if (index >= leaf.sonnum) return false;
                leaf.sonlist[index] = value;
                father->update(leaf, pointer);
                return true;
            }

            Key getKey() const {
                Bleaf leaf;
                father->read(leaf, pointer);
                return leaf.keylist[index];
            }

            Value getValue() const {
                Bleaf leaf;
                father->read(leaf, pointer);
                return leaf.sonlist[index];
            }

            iterator operator++(int) {
                iterator temp = *this;
                Bleaf leaf;
                father->read(leaf, pointer);
                if (index < leaf.sonnum - 1) {
                    index++;
                    return temp;
                } else {
                    if (!leaf.nextleaf && index >= 0)
                        index = -1;
                    else if (!leaf.nextleaf)
                        throw invalid_iterator();
                    Bleaf nleaf;
                    father->read(nleaf, leaf.nextleaf);
                    pointer = leaf.nextleaf;
                    index = 0;
                    return temp;
                }
            }

            iterator &operator++() {
                Bleaf leaf;
                father->read(leaf, pointer);
                if (index < leaf.sonnum - 1) {
                    index++;
                    return *this;
                } else {
                    if (!leaf.nextleaf)
                        index = -1;
                    else if (!leaf.nextleaf)
                        throw invalid_iterator();
                    Bleaf nleaf;
                    father->read(nleaf, leaf.nextleaf);
                    pointer = leaf.nextleaf;
                    index = 0;
                    return *this;
                }

            }

            iterator operator--(int) {
                iterator temp = *this;
                Bleaf leaf;
                father->read(leaf, pointer);
                if (index > 0) {
                    index--;
                    return temp;
                } else {
                    if (!father->root) throw container_is_empty();
                    size_t deep = father->height - 1;
                    size_t tpointer = father->root;
                    Key tkey = leaf.keylist[0];
                    BNode btemp;
                    while (--deep) {
                        father->read(btemp, tpointer);
                        tpointer = btemp.sonlist[binasearch(btemp.keylist, leaf.keylist[0], btemp.sonnum - 1).second +1];
                    }
                    if (leaf.keylist[0] == tkey) throw invalid_iterator();
                    pointer = tpointer;
                    index = leaf.sonnum - 1;
                    return temp;
                }
            }

            iterator &operator--() {
                Bleaf leaf;
                father->read(leaf, pointer);
                if (index > 0) {
                    index--;
                    return *this;
                } else {
                    if (!father->root) throw container_is_empty();
                    size_t deep = father->height - 1;
                    size_t tpointer = father->root;
                    Key tkey = leaf.keylist[0];
                    BNode btemp;
                    while (--deep) {
                        father->read(btemp, tpointer);
                        tpointer = btemp.sonlist[binasearch(btemp.keylist, leaf.keylist[0], btemp.sonnum - 1).second +
                                                 1];
                    }
                    if (leaf.keylist[0] == tkey) throw invalid_iterator();
                    pointer = tpointer;
                    index = leaf.sonnum - 1;
                    return *this;
                }
            }

            // Overloaded of operator '==' and '!='
            // Check whether the iterators are same
            bool operator==(const iterator &rhs) const {
                return pointer == rhs.pointer || (index == -1 && rhs.index == -1);
            }

            bool operator!=(const iterator &rhs) const {
                return !(pointer == rhs.pointer || (index == -1 && rhs.index == -1));
            }
        };

        iterator begin() {
            return iterator(this, 0, 4*sizeof(size_t));
        }

        // return an iterator to the end(the next element after the last)
        iterator end() {
            return iterator(this, -1, 0);
        }

        iterator find(const Key &key) {
            Bleaf leaf;
            pair<size_t, FNode *> lresult = findleaf(key);
            size_t pointer = lresult.first;
            delfnode(lresult.second);
            read(leaf, pointer);
            int index = binasearch(leaf.keylist, key, leaf.sonnum).second;
            return iterator(this, index, pointer);
        }

        // return an iterator whose key is the smallest key greater or equal than 'key'
        iterator lower_bound(const Key &key) {
            Bleaf leaf;
            pair<size_t, FNode *> lresult = findleaf(key);
            size_t pointer = lresult.first;
            delfnode(lresult.second);
            read(leaf, pointer);
            int index = binasearch(leaf.keylist, key, leaf.sonnum).second;
            if(index==-1) index++;
            iterator iter = iterator(this, index, pointer);
            if (leaf.keylist[index] >= key) return iter;
            return ++iter;
        }
    };
}