#ifndef SJTU_LIST_HPP
#define SJTU_LIST_HPP

#include "exceptions.hpp"
#include "algorithm.hpp"

#include <climits>
#include <cstddef>
namespace sjtu {
/**
 * a data container like std::list
 * allocate random memory addresses for data and they are doubly-linked in a list.
 */
    template<typename T>
    class list {
    protected:
        class node {
        public:
            /**
             * add data members and constructors & destructor
             */
            node *next;
            node *prev;
            T *data;
            node(const T &_data){
                next = NULL;
                prev = NULL;
                data = new T(_data);
            }
            node(){
                next = NULL;
                prev = NULL;
                data = NULL;
            }
            node(node &other){
                next = other.next;
                prev = other.prev;
                data = new T(*(other.data));
            }
            ~node(){
                delete data;
            }
        };

    protected:
        /**
         * add data members for linked list as protected members
         */
        size_t length;
        node *head;
        node *tail;
        /**
         * insert node cur before node pos
         * return the inserted node cur
         */
        node *insert(node *pos, node *cur) {
            cur->prev = pos->prev;
            cur->next = pos;
            pos->prev->next = cur;
            pos->prev = cur;
            return cur;
        }
        /**
         * remove node pos from list (no need to delete the node)
         * return the removed node pos
         */
        node *erase(node *pos) {
            pos->prev->next = pos->next;
            pos->next->prev = pos->prev;
            pos->prev = NULL;
            pos->next = NULL;
            return pos;
        }

    public:
        class const_iterator;
        class iterator {
            friend class list;
        private:
            /**
             * TODO add data members
             *   just add whatever you want.
             */
            list *father;
            node *target;
        public:
            iterator(){}
            iterator(const iterator &other){
                father = other.father;
                target = other.target;
            }
            iterator(list *_father, node *_target){
                father = _father;
                target = _target;
            }
            iterator operator+(int a){
                iterator temp = *this;
                while(a--) temp = iterator(temp.father, temp.target->next);
                return temp;
            }
            iterator operator-(int a){
                iterator temp = *this;
                while(a--) temp = iterator(temp.father, temp.target->prev);
                return temp;
            }
            /**
             * iter++
             */
            iterator operator++(int) {
                if(!target->next) throw invalid_iterator();
                iterator temp = iterator(*this);
                target = target->next;
                return temp;
            }
            /**
             * ++iter
             */
            iterator & operator++() {
                if(!target->next) throw invalid_iterator();
                target = target->next;
                return *this;
            }
            /**
             * iter--
             */
            iterator operator--(int) {
                if(!target->prev||target->prev==father->head) throw invalid_iterator();
                iterator temp = iterator(*this);
                target = target->prev;
                return temp;
            }
            /**
             * --iter
             */
            iterator & operator--() {
                if(!target->prev||target->prev==father->head) throw invalid_iterator();
                target = target->prev;
                return *this;
            }
            /**
             * TODO *it
             * remember to throw if iterator is invalid
             */
            T & operator *() const {
                if(!target->data) throw invalid_iterator();
                return *(target->data);
            }
            /**
             * TODO it->field
             * remember to throw if iterator is invalid
             */
            T * operator ->() const noexcept {
                //if(target->data==NULL) throw invalid_iterator();
                return target->data;
            }
            /**
             * a operator to check whether two iterators are same (pointing to the same memory).
             */
            bool operator==(const iterator &rhs) const {
                return target == rhs.target;
            }
            bool operator==(const const_iterator &rhs) const {
                return target == rhs.target;
            }
            /**
             * some other operator for iterator.
             */
            bool operator!=(const iterator &rhs) const {
                return target != rhs.target;
            }
            bool operator!=(const const_iterator &rhs) const {
                return target != rhs.target;
            }
        };
        /**
         * TODO
         * has same function as iterator, just for a const object.
         * should be able to construct from an iterator.
         */
        class const_iterator {
            friend class list;
        private:
            /**
             * TODO add data members
             *   just add whatever you want.
             */
            const list *father;
            const node *target;
        public:
            /**
             * iter++
             */
            const_iterator(){}
            const_iterator(const list *_father, const node *_target){
                father = _father;
                target = _target;
            }
            const_iterator(const iterator &other){
                father = other.father;
                target = other.target;
            }
            const_iterator(const const_iterator &other){
                father = other.father;
                target = other.target;
            }
            const_iterator operator++(int) {
                if(!target->next) throw invalid_iterator();
                const_iterator temp = const_iterator(*this);
                target = target->next;
                return *this;
            }
            /**
             * ++iter
             */
            const_iterator & operator++() {
                if(!target->next) throw invalid_iterator();
                target = target->next;
                return *this;
            }
            /**
             * iter--
             */
            const_iterator operator--(int) {
                if(!target->prev||target->prev==father->head) throw invalid_iterator();
                const_iterator temp = const_iterator(*this);
                target = target->prev;
                return temp;
            }
            /**
             * --iter
             */
            const_iterator & operator--() {
                if(!target->prev||target->prev==father->head) throw invalid_iterator();
                target = target->prev;
                return *this;
            }
            /**
             * TODO *it
             * remember to throw if iterator is invalid
             */
            const T & operator *() const {
                if(!target->data) throw invalid_iterator();
                return *(target->data);
            }
            /**
             * TODO it->field
             * remember to throw if iterator is invalid
             */
            const T * operator ->() const noexcept {
                if(!target->data) throw invalid_iterator();
                return target->data;
            }
            /**
             * a operator to check whether two iterators are same (pointing to the same memory).
             */
            bool operator==(const iterator &rhs) const {
                return target == rhs.target;
            }
            bool operator==(const const_iterator &rhs) const {
                return target == rhs.target;
            }
            /**
             * some other operator for iterator.
             */
            bool operator!=(const iterator &rhs) const {
                return target != rhs.target;
            }
            bool operator!=(const const_iterator &rhs) const {
                return target != rhs.target;
            }
        };
        /**
         * TODO Constructs
         * Atleast two: default constructor, copy constructor
         */
        list() {
            length = 0;
            head = new node;
            tail = new node;
            head->next = tail;
            head->prev = NULL;
            tail->next = NULL;
            tail->prev = head;
        }
        list(const list &other) {
            length = other.length;
            const_iterator it(&other, other.head->next);
            head = new node;
            tail = new node;
            node *pointer = head;
            while(it.target != other.tail){
                node *temp = new node;
                temp->prev = pointer;
                temp->data = new T(*it);
                pointer->next = temp;
                pointer = pointer->next;
                it++;
            }
            pointer->next = tail;
            tail->prev = pointer;
        }
        /**
         * TODO Destructor
         */
        virtual ~list() {
            node *eraser = head;
            iterator it(this, head->next);
            while(it.target != tail){
                delete eraser;
                eraser = it.target;
                it++;
            }
            delete tail->prev;
            delete tail;
        }
        /**
         * TODO Assignment operator
         */
        list &operator=(const list &other) {
            if(this == &other) return *this;
            node *eraser = head;
            iterator it(this, head->next);
            while(it.target != tail){
                delete eraser;
                eraser = it.target;
                it++;
            }
            delete tail->prev;
            delete tail;
            length = other.length;
            const_iterator it2 = const_iterator(&other, other.head->next);
            head = new node;
            tail = new node;
            node *pointer = head;
            while(it2.target != other.tail){
                node *temp = new node;
                temp->prev = pointer;
                temp->data = new T(*it2);
                pointer->next = temp;
                pointer = pointer->next;
                it2++;
            }
            pointer->next = tail;
            tail->prev = pointer;
            return *this;
        }
        /**
         * access the first / last element
         * throw container_is_empty when the container is empty.
         */
        const T & front() const {
            if(!length) throw container_is_empty();
            return *(head->next->data);
        }
        const T & back() const {
            if(!length) throw container_is_empty();
            return *(tail->prev->data);
        }
        /**
         * returns an iterator to the beginning.
         */
        iterator begin() {
            return iterator(this, head->next);
        }
        const_iterator cbegin() const {
            return const_iterator(this, head->next);
        }
        /**
         * returns an iterator to the end.
         */
        iterator end() {
            return iterator(this, tail);
        }
        const_iterator cend() const {
            return const_iterator(this, tail);
        }
        /**
         * checks whether the container is empty.
         */
        virtual bool empty() const {
            return length==0;
        }
        /**
         * returns the number of elements
         */
        virtual size_t size() const {
            return length;
        }

        /**
         * clears the contents
         */
        virtual void clear() {
            length = 0;
            node *eraser = head;
            iterator it(this, head->next);
            while(it.target!=tail){
                delete eraser;
                eraser = it.target;
                ++it;
            }
            delete tail->prev;
            head = new node;
            head->next = tail;
            tail->prev = head;
        }
        /**
         * insert value before pos (pos may be the end() iterator)
         * return an iterator pointing to the inserted value
         * throw if the iterator is invalid
         */
        virtual iterator insert(iterator pos, const T &value) {
            if(pos.father != this) throw invalid_iterator();
            length++;
            node *temp = new node;
            temp->data = new T(value);
            iterator it(this, insert(pos.target, temp));
            return it;
        }
        /**
         * remove the element at pos (the end() iterator is invalid)
         * returns an iterator pointing to the following element, if pos pointing to the last element, end() will be returned.
         * throw if the container is empty, the iterator is invalid
         */
        virtual iterator erase(iterator pos) {
            if(!length) throw container_is_empty();
            if(pos == end() || pos.father!=this) throw invalid_iterator();
            this->length--;
            iterator temp = pos+1;
            this->erase(pos.target);
            delete pos.target;
            return temp;
        }
        /**
         * adds an element to the end
         */
        void push_back(const T &value) {
            length++;
            node *temp = new node;
            temp->data = new T(value);
            insert(tail, temp);
        }
        /**
         * removes the last element
         * throw when the container is empty.
         */
        void pop_back() {
            if(length == 0)throw container_is_empty();
            length--;
            node *temp = tail->prev;
            erase(tail->prev);
            delete temp;
        }
        /**
         * inserts an element to the beginning.
         */
        void push_front(const T &value) {
            length++;
            node *temp = new node;
            temp->data = new T(value);
            insert(head->next, temp);
        }
        /**
         * removes the first element.
         * throw when the container is empty.
         */
        void pop_front() {
            if(length == 0)throw container_is_empty();
            length--;
            node *temp = head->next;
            erase(head->next);
            delete temp;
        }
        /**
         * sort the values in ascending order with operator< of T
         */

        void sort() {
            std::function<bool(const T&, const T&)> cmp = [&](const T &a, const T &b)->bool{return a<b;};
            void *raw = operator new[](length * sizeof(T));
            T *temp = static_cast<T *>(raw);
            size_t i = 0;
            for(iterator it = begin(); it != end(); ++it){
                new (&temp[i])T(*(it));
                i++;
            }
            sjtu::sort(temp+1-1, temp+i, cmp);
            i = 0;
            for(iterator it = begin(); it != end(); ++it){
                *(it.target->data) = temp[i];
                temp[i].~T();
                i++;
            }
            operator delete[](temp);
        }
        /**
         * merge two sorted lists into one (both in ascending order)
         * compare with operator< of T
         * container other becomes empty after the operation
         * for equivalent elements in the two lists, the elements from *this shall always precede the elements from other
         * the order of equivalent elements of *this and other does not change.
         * no elements are copied or moved
         */
        void merge(list &other) {
            if(!other.size()) return;
            length += other.length;
            iterator thisit = begin();
            iterator otherit = other.begin()+1;
            for(;thisit!=end();++thisit) {
                for (; otherit != other.end(); ++otherit)
                    if (*(otherit - 1) < *(thisit)) {
                        insert(thisit.target, other.erase((otherit - 1).target));
                    } else break;
                if (*(otherit - 1) < *(thisit)) {
                    insert(thisit.target, other.erase((otherit - 1).target));
                    other.length = 0;
                    return;
                }
            }
            for(;otherit!=other.end();++otherit) {
                insert(tail, other.erase((otherit-1).target));
            }
            insert(tail, other.erase((otherit-1).target));
            other.length = 0;
        }
        /**
         * reverse the order of the elements
         * no elements are copied or moved
         */
        void reverse() {
            for(iterator it=begin(); it!=end();--it){
                node *temp = it.target->prev;
                it.target->prev = it.target->next;
                it.target->next = temp;
            }
            tail->next = tail->prev;
            tail->prev = NULL;
            head->prev = head->next;
            head->next = NULL;
            node *temp = head;
            head = tail;
            tail = temp;
        }
        /**
         * remove all consecutive duplicate elements from the container
         * only the first element in each group of equal elements is left
         * use operator== of T to compare the elements.
         */
        void unique() {
            for(iterator it=begin(); it!=end();it++){
                while((it+1).target->data && *(it) == *(it+1)) erase(it+1);
            }
        }
    };

}

#endif //SJTU_LIST_HPP