#ifndef SJTU_VECTOR_HPP
#define SJTU_VECTOR_HPP

#include "exceptions.hpp"
#include "iostream"
#include <climits>
#include <cstddef>

namespace sjtu {
/**
 * a data container like std::vector
 * store data in a successive memory and support random access.
 */
    template<typename T>
    class vector {
    public:
        /**
         * TODO
         * a type for actions of the elements of a vector, and you should write
         *   a class named const_iterator with same interfaces.
         */
        /**
         * you can see RandomAccessIterator at CppReference for help.
         */
        class const_iterator;
        class iterator {
            friend class const_iterator;
            friend class vector<T>;
        private:
            /**
             * TODO add data members
             *   just add whatever you want.
             */
             T *data;
             size_t index;
             vector *father;
        public:
            iterator(T *_data, size_t _index, vector *_father){
                data = _data;
                index = _index;
                father = _father;
            }
            iterator(const iterator &other){
                data = other.data;
                index = other.index;
                father = other.father;
            }
            iterator(){}
            /**
             * return a new iterator which pointer n-next elements
             * as well as operator-
             */
            iterator operator+(const int &n) const {
                //TODO
                return (*father).iters[index+n];
            }
            iterator operator-(const int &n) const {
                //TODO
                return (*father).iters[index-n];
            }
            // return the distance between two iterators,
            // if these two iterators point to different vectors, throw invaild_iterator.
            int operator-(const iterator &rhs) const {
                //TODO
                if(father != rhs.father) throw invalid_iterator();
                return index - rhs.index;
            }
            iterator& operator+=(const int &n) {
                //TODO
                index += n;
                data = (*father).iters[index].data;
                return *this;
            }
            iterator& operator-=(const int &n) {
                //TODO
                index -= n;
                data = (*father).iters[index].data;
                return *this;
            }
            /**
             * TODO iter++
             */
            iterator operator++(int) {
                iterator temp = iterator(data, index, father);
                index++;
                data = (*father).iters[index].data;
                return temp;
            }
            /**
             * TODO ++iter
             */
            iterator& operator++() {
                index++;
                data = (*father).iters[index].data;
                return *this;
            }
            /**
             * TODO iter--
             */
            iterator operator--(int) {
                iterator temp = iterator(data, index, father);
                index--;
                data = (*father).iters[index].data;
                return temp;
            }
            /**
             * TODO --iter
             */
            iterator& operator--() {
                index--;
                data = (*father).iters[index].data;
                return this;
            }
            /**
             * TODO *it
             */
            T& operator*() const{
                return *data;
            }
            /**
             * a operator to check whether two iterators are same (pointing to the same memory address).
             */
            bool operator==(const iterator &rhs) const {
                return father == rhs.father && index == rhs.index;
            }
            bool operator==(const const_iterator &rhs) const {
                return father == rhs.father && index == rhs.index;
            }
            /**
             * some other operator for iterator.
             */
            bool operator!=(const iterator &rhs) const {
                return data!=rhs.data;
            }
            bool operator!=(const const_iterator &rhs) const {
                return father != rhs.father || index != rhs.index;
            }
        };
        /**
         * TODO
         * has same function as iterator, just for a const object.
         */
        class const_iterator {

        private:
            /**
             * TODO add data members
             *   just add whatever you want.
             */
            const T *data;
            size_t index;
            const vector *father;
        public:
            /**
             * return a new iterator which pointer n-next elements
             * as well as operator-
             */
            const_iterator(iterator &other){
                data = other.data;
                index = other.index;
                father = other.father;
            }
            const_iterator operator+(const int &n) const {
                //TODO
                return const_iterator((*father).iters[index+n]);
            }
            const_iterator operator-(const int &n) const {
                //TODO
                return const_iterator((*father).iters[index-n]);
            }
            // return the distance between two iterators,
            // if these two iterators point to different vectors, throw invaild_iterator.
            int operator-(const iterator &rhs) const {
                //TODO
                if(father != rhs.father) throw invalid_iterator();
                return index - rhs.index;
            }
            const_iterator& operator+=(const int &n) {
                //TODO
                index += n;
                data = &((*father)[index]);
                return this;
            }
            const_iterator& operator-=(const int &n) {
                //TODO
                index -= n;
                data = &((*father)[index]);
                return this;
            }
            /**
             * TODO iter++
             */
            const_iterator operator++(int) {
                const_iterator temp = const_iterator((*father).iters[index]);
                index++;
                try{
                    data = &((*father)[index]);
                }catch (index_out_of_bound &e){
                    data = NULL;
                }
                return temp;
            }
            /**
             * TODO ++iter
             */
            const_iterator& operator++() {
                index++;
                try{
                    data = &((*father)[index]);
                }catch (index_out_of_bound &e){
                    data = NULL;
                }
                return *this;
            }
            /**
             * TODO iter--
             */
            const_iterator operator--(int) {
                const_iterator temp = const_iterator((*father).iters[index]);
                index--;
                data = &((*father)[index]);
                return temp;
            }
            /**
             * TODO --iter
             */
            const_iterator& operator--() {
                index--;
                data = &((*father)[index]);
                return this;
            }
            /**
             * TODO *it
             */
            T operator*() const{
                return *data;
            }
            /**
             * a operator to check whether two iterators are same (pointing to the same memory address).
             */
            bool operator==(const iterator &rhs) const {
                return father == rhs.father && index == rhs.index;
            }
            bool operator==(const const_iterator &rhs) const {
                return father == rhs.father && index == rhs.index;
            }
            /**
             * some other operator for iterator.
             */
            bool operator!=(const iterator &rhs) const {
                return father != rhs.father || index != rhs.index;
            }
            bool operator!=(const const_iterator &rhs) const {
                return father != rhs.father || index != rhs.index;
            }

        };
        void checkVolumn(){
            if(length + 2> volumn){
                iterator *temp = iters;
                volumn *= 1024;
                iters = new iterator[volumn];
                for(size_t i=0;i<=length;i++) iters[i] = temp[i];
                delete [] temp;
            }
        }
        /**
         * TODO Constructs
         * Atleast two: default constructor, copy constructor
         */
        size_t length;
        size_t volumn;
        iterator *iters;
        vector() {
            length = 0;
            volumn = 2048;
            iters = new iterator[volumn];
            iters[length] = iterator(NULL, length, this);
        }
        vector(const vector &other) {
            volumn = other.volumn;
            length = other.length;
            iters = new iterator[volumn];
            for(size_t i=0;i<length;i++) {
                T *temp_data = new T(other[i]);
                iters[i] = iterator(temp_data, i, this);
            }
            iters[length] = iterator(NULL, length, this);
        }
        vector(vector &other) {
            volumn = other.volumn;
            length = other.length;
            iters = new iterator[volumn];
            for(size_t i=0;i<length;i++) {
                T *temp_data = new T(other[i]);
                iters[i] = iterator(temp_data, i, this);
            }
            iters[length] = iterator(NULL, length, this);
        }
        /**
         * TODO Destructor
         */
        ~vector() {
            for(size_t i=0;i<length;i++) delete iters[i].data;
            delete [] iters;
        }
        /**
         * TODO Assignment operator
         */
        vector &operator=(const vector &other) {
            if(&other == this) return *this;
            volumn = other.volumn;
            length = other.length;
            for(size_t i=0;i<length;i++) delete iters[i].data;
            delete [] iters;
            iters = new iterator[volumn];
            for(size_t i=0;i<length;i++) {
                T *temp_data = new T(other[i]);
                iters[i] = iterator(temp_data, i, this);
            }
            iters[length] = iterator(NULL, length, this);
            return *this;
        }
        /**
         * assigns specified element with bounds checking
         * throw index_out_of_bound if pos is not in [0, size)
         */
        T & at(const size_t &pos) {
            if(pos>=length||pos<0) throw index_out_of_bound();
            return *(iters[pos]);
        }
        const T & at(const size_t &pos) const {
            if(pos>=length||pos<0) throw index_out_of_bound();
            return *(iters[pos]);
        }
        /**
         * assigns specified element with bounds checking
         * throw index_out_of_bound if pos is not in [0, size)
         * !!! Pay attentions
         *   In STL this operator does not check the boundary but I want you to do.
         */
        T & operator[](const size_t &pos) {
            if(pos>=length||pos<0) throw index_out_of_bound();
            return *(iters[pos]);
        }
        const T & operator[](const size_t &pos) const {
            if(pos>=length||pos<0) throw index_out_of_bound();
            return *(iters[pos]);
        }
        /**
         * access the first element.
         * throw container_is_empty if size == 0
         */
        const T & front() const {
            if(length == 0) throw container_is_empty();
            return *(iters[0]);
        }
        /**
         * access the last element.
         * throw container_is_empty if size == 0
         */
        const T & back() const {
            if(length == 0) throw container_is_empty();
            return *(iters[length-1]);
        }
        /**
         * returns an iterator to the beginning.
         */
        iterator begin() {
            return iters[0];
        }
        const_iterator cbegin() const {
            return const_iterator(iters[0]);
        }
        /**
         * returns an iterator to the end.
         */
        iterator end() {
            return iters[length];
        }
        const_iterator cend() const {
            return const_iterator(iters[length]);
        }
        /**
         * checks whether the container is empty
         */
        bool empty() const {
            return length==0;
        }
        /**
         * returns the number of elements
         */
        size_t size() const {
            return length;
        }
        /**
         * clears the contents
         */
        void clear() {
            for(size_t i=0;i<length;i++) delete iters[i].data;
            length = 0;
            volumn = 16;
            delete [] iters;
        }
        /**
         * inserts value before pos
         * returns an iterator pointing to the inserted value.
         */
        iterator insert(iterator pos, const T &value) {
            size_t counter = 0;
            while(iters[counter]!= pos) counter++;
            length++;checkVolumn();
            for(size_t i=length;i>counter;i--) { iters[i].data = iters[i-1].data;iters[i].index++; }
            T *temp_data = new T(value);
            iters[counter] = iterator(temp_data, counter, this);
            return iters[counter];
        }
        /**
         * inserts value at index ind.
         * after inserting, this->at(ind) == value
         * returns an iterator pointing to the inserted value.
         * throw index_out_of_bound if ind > size (in this situation ind can be size because after inserting the size will increase 1.)
         */
        iterator insert(const size_t &ind, const T &value) {
            if(ind > length||ind < 0) throw index_out_of_bound();
            length++;checkVolumn();
            for(size_t i=length;i>ind;i--) { iters[i].data = iters[i-1].data;iters[i].index++; }
            T *temp_data = new T(value);
            iters[ind] = iterator(temp_data, ind, this);
            return iters[ind];
        }
        /**
         * removes the element at pos.
         * return an iterator pointing to the following element.
         * If the iterator pos refers the last element, the end() iterator is returned.
         */
        iterator erase(iterator pos) {
            size_t counter = 0;
            while(iters[counter]!= pos) counter++;
            delete iters[counter].data;
            for(size_t i=counter;i<=length;i++) {iters[i].data = iters[i+1].data;iters[i+1].index--;}
            length--;
            return iters[counter];
        }
        /**
         * removes the element with index ind.
         * return an iterator pointing to the following element.
         * throw index_out_of_bound if ind >= size
         */
        iterator erase(const size_t &ind) {
            if(ind >= length||ind < 0) throw index_out_of_bound();
            delete iters[ind].data;
            for(size_t i=ind;i<=length;i++) {iters[i].data = iters[i+1].data;iters[i+1].index--;}
            length--;
            return iters[ind];}
        /**
         * adds an element to the end.
         */
        void push_back(const T &value) {
            T *temp = new T(value);
            length++;checkVolumn();
            iters[length] = iterator(NULL, length, this);
            iters[length-1] = iterator(temp, length-1, this);
        }
        /**
         * remove the last element from the end.
         * throw container_is_empty if size() == 0
         */
        void pop_back() {
            if(length == 0) throw container_is_empty();
            length--;
            delete iters[length].data;
            iters[length] = iters[length+1];
        }
    };


}

#endif