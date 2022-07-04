//
// Created by Passerby on 2022/5/2.
//
#ifndef SJTU_LINKED_HASHMAP_HPP_STD
#define SJTU_LINKED_HASHMAP_HPP_STD

#include <cstddef>
#include <functional>
#include <iostream>
#include "utility.hpp"
#include "algorithm.hpp"
#include "exceptions.hpp"
#include "list.hpp"

namespace sjtu {
    /**
     *  Maintains key-value pairs just like MAP
     *  Dynamically sized hash table who handles collision with linked lists
     *  Iterators arrange in order of insertion (maintained by base class LIST)
     */

    template <
            class Key,
            class Value,
            class Hash = std::hash<Key>,
            class Equal = std::equal_to<Key>
    >
    class linked_hashmap : public list<pair<const Key, Value> > {
    public:
        using value_type = pair<const Key, Value>;

    private:
        class Node : public list<value_type>::node {
            friend class BucketList;
        public:
            /**
             * add data members in addition to class node in LIST
             */
            Node *Next=NULL;
            Node(){}
            Node(value_type _val){
                this->val = new value_type (_val);
            }

        };

        /**
         * add data members as needed and necessary private function such as resize()
         */
        /**
         * singly-linked list used for hash collision
         */
        class BucketList {
        public:
            /**
             * data members, constructors and destructor
             */
            size_t Capacity[7] = {1009, 10007, 100003, 1000003, 10000019, 100000007, 1000000007};
            size_t index;
            Node **Buckets;
            Hash hash;
            Equal equal;
            BucketList() {
                index = 0;
                Buckets = new Node*[Capacity[index]];
                for(size_t i=0;i<Capacity[index];i++) Buckets[i] = NULL;
            }
            BucketList(size_t _index){
                index = _index;
                Buckets = new Node*[Capacity[index]];
                for(size_t i=0;i<Capacity[index];i++) Buckets[i] = NULL;
            }
            ~BucketList(){
                delete [] Buckets;
            }
            void clear(){
                for(size_t i=0;i<Capacity[index];i++) Buckets[i] = NULL;
            }
            /**
             *  TODO find corresponding Node with key o
             */
            Node * find(const Key &o) const{
                size_t hsh = hash(o)%Capacity[index];
                Node *pointer = Buckets[hsh];
                if(!pointer) return NULL;
                while(!equal(pointer->val->first, o) && pointer->Next) pointer = pointer->Next;
                if(!equal(pointer->val->first, o)) return NULL;
                return pointer;
            }
            /**
             * TODO insert key-value pair(k, v) into this BucketList
             * return this new Node
             */

            Node * insert(const Key &k, const Value &v) {
                size_t hsh = hash(k)%Capacity[index];
                Node *pointer = Buckets[hsh];
                Node *temp = new Node(pair<Key, Value>(k, v));
                if(!pointer) {
                    Buckets[hsh] = temp;
                }
                else {
                    while(pointer->Next) pointer = pointer->Next;
                    pointer->Next = temp;
                }
                return temp;
            }
            Node * insert(const value_type &kv) {
                const Key k = kv.first;
                const Value v = kv.second;
                return insert(kv.first, kv.second);
            }
            /**
             * TODO remove the Node with key k from this BucketList (no need to delete)
             * return the removed Node
             */
            Node * erase(const Key &k) {
                size_t hsh = hash(k)%Capacity[index];
                Node *pointer = Buckets[hsh];
                if(equal(pointer->val->first, k)){
                    Buckets[hsh] = pointer->Next;
                    return pointer;
                }
                if(!pointer->Next) return NULL;
                while(pointer->Next->Next && !equal(pointer->Next->val->first, k)) pointer = pointer->Next;
                if(!equal(pointer->Next->val->first, k)) return NULL;
                Node *temp = pointer->Next;
                pointer->Next = temp->Next;
                return temp;
            }
        };


        BucketList *bucketList;
        size_t LoadFactor;
        void checkCapacity(){
            if(this->num < bucketList->Capacity[bucketList->index]*LoadFactor) return;
            size_t x = bucketList->index;
            while(this->num >= bucketList->Capacity[x]*LoadFactor) x++;
            BucketList *temp = new BucketList(x);
            Node *nhead, *ntail, *nnil;
            size_t nnum = this->num;
            nhead = ntail = new Node;
            ntail->nxt = nnil = new Node;
            nnil->prv = ntail;
            for(iterator it = this->begin(); it != this->end(); ++it) {
                list<value_type>::insert(nnil, temp->insert(*it));
            }
            clear();
            delete this->head;
            delete this->nil;
            this->head = nhead;
            this->nil = nnil;
            this->num = nnum;
            this->tail = nnil->prv;
            delete bucketList;
            bucketList = temp;
        }
    public:
        /**
         * iterator is the same as LIST
         */
        using iterator = typename list<value_type>::iterator;
        using const_iterator = typename list<value_type>::const_iterator;

        /**
        * TODO two constructors
        */
        linked_hashmap() {
            LoadFactor = 2;
            bucketList = new BucketList;
        }
        linked_hashmap(const linked_hashmap &other) {
            LoadFactor = other.LoadFactor;
            bucketList = new BucketList(other.bucketList->index);
            for(const_iterator cit = other.cbegin(); cit != other.cend(); cit++){
                list<value_type>::insert(this->nil, bucketList->insert(*cit));
            }
        }
        /**
         * TODO assignment operator
         */
        linked_hashmap &operator=(const linked_hashmap &other) {
            if(this == &other) return *this;
            delete bucketList;
            bucketList = new BucketList(other.bucketList->index);
            LoadFactor = other.LoadFactor;
            for(const_iterator cit = other.cbegin(); cit != other.cend(); cit++){
                list<value_type>::insert(this->nil, bucketList->insert(*cit));
            }
            return *this;
        }
        /**
         * TODO Destructors
         */
        ~linked_hashmap() {
            delete bucketList;
        }
        /**
         * TODO access specified element with bounds checking
         * Returns a reference to the mapped value of the element with key equivalent to key.
         * If no such element exists, an exception of type `index_out_of_bound'
         */
        Value &at(const Key &key) {
            Node *pointer = bucketList->find(key);
            if(!pointer) throw index_out_of_bound();
            return pointer->val->second;
        }
        const Value &at(const Key &key) const {
            Node *pointer = bucketList->find(key);
            if(!pointer) throw index_out_of_bound();
            return pointer->val->second;
        }
        /**
         * TODO access specified element
         * Returns a reference to the value that is mapped to a key equivalent to key,
         *   performing an insertion if such key does not already exist.
         */
        Value &operator[](const Key &key) {
            Node *temp = bucketList->find(key);
            if(temp) return temp->val->second;
            checkCapacity();
            Value v;
            return list<value_type>::insert(this->nil, bucketList->insert(key, v))->val->second;
        }
        /**
         * behave like at() throw index_out_of_bound if such key does not exist.
         */
        const Value &operator[](const Key &key) const {
            return at(key);
        }
        /**
         * TODO override clear() in LIST
         */
        void clear() override{
            list<value_type>::clear();
            bucketList->clear();
        }
        /**
         * TODO insert an element.
         * return a pair, the first of the pair is
         *   the iterator to the new element (or the element that prevented the insertion),
         *   the second one is true if insert successfully, or false.
         */
        pair<iterator, bool> insert(const value_type &value) {
            Node *temp = bucketList->find(value.first);
            if(temp) return pair<iterator, bool>(iterator(temp, this), false);
            checkCapacity();
            return pair<iterator, bool>(iterator(list<value_type>::insert(this->nil, bucketList->insert(value)), this), true);
        }
        /**
         * TODO erase the element at pos.
         * throw if pos pointed to a bad element (pos == this->end() || pos points an element out of this)
         * return anything, it doesn't matter
         */
        iterator erase(iterator pos) override{
            if(pos.invalid(this)) throw invalid_iterator();
            if(list<value_type>::empty()) throw container_is_empty();
            iterator it;
            Node * temp = bucketList->erase(pos->first);
            if(temp) {
                list<value_type>::erase(temp);
                delete temp;
            }
            return it;
        }
        /**
         * TODO Returns the number of elements with key
         *   that compares equivalent to the specified argument,
         *   which is either 1 or 0
         *     since this container does not allow duplicates.
         */
        size_t count(const Key &key) const {
            return bucketList->find(key) != NULL;
        }
        /**
         * TODO Finds an element with key equivalent to key.
         *  return iterator to an element with key equivalent to key.
         *   If no such element is found, past-the-end (see end()) iterator is returned.
         */
        iterator find(const Key &key) {
            Node *temp = bucketList->find(key);
            if(temp) return iterator(temp, this);
            return this->end();
        }
        const_iterator find(const Key &key) const {
            Node *temp = bucketList->find(key);
            if(temp) return const_iterator(temp, this);
            return this->cend();
        }
    };

}

#endif