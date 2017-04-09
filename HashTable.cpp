#include <iostream>
#include <cstddef>
#include <string>
#include <cstdlib>
#include "Entry.h"
using namespace std;

template<typename K, typename V>
class HashTable
{
private:
     int N;
     int count;
     Entry<K, V> **hash_table;

public:
     HashTable();
     HashTable(int N);
     
     /* hashcode string to int */
     int hashcode(string s);
     /* hashcode int to int */
     int hashcode(int i);
     /* hashcode char to int */
     int hashcode(char c);
     /* hashcode long to int */
     int hashcode(unsigned long ul);
     /* basic compression function */
     int compression(int hc);
     
     /* insert e into hash table */
     void insert(Entry<K, V> * e);
     /* replace e1 with e2 */
     void replace(Entry<K, V> * e1, Entry<K, V> * e2);
     /* find e and return */
     Entry<K, V> * find(Entry<K, V> * e);
     /* remove e from the table */
     void remove(Entry<K, V> * e);
     /* grow = 1 to increase the table by a factor of 2; grow = 0 to decrease the table by a factor of 2 */
     void resize(bool grow);
     /* computes the load factor of the hash table i.e. 'number of elements / number of buckets' */
     double compute_load_factor();
     /* returns the length of the longest chain */
     int longest_chain_length();
     /* prints the list with the index number preceding the first entry in the index */
     void print();
};
     
     template<typename K, typename V>
     HashTable<K, V>::HashTable()
     {
          this->N = 10000;
          hash_table = new Entry<K, V> *[this->N];

          for (int i = 0; i < this->N; i++)
               hash_table[i] = NULL;
          
          count = 0;
     }
     
     template<typename K, typename V>
     HashTable<K, V>::HashTable(int N)
     {
          this->N = N;
          hash_table = new Entry<K, V> *[this->N];

          for (int i = 0; i < this->N; i++)
               hash_table[i] = NULL;
          
          count = 0;
     }
   
     template<typename K, typename V>
     int HashTable<K, V>::hashcode(string s) {
          int hc = 0;
          for (int i = 0; i < s.length(); i++)
               hc = 127 * hc + static_cast<int>(s[i]) % 16908799;
          return hc;
     }
  
     template<typename K, typename V>
     int HashTable<K, V>::hashcode(int i) {
          int hc = i * 127;
          return (hc << 2);
     }

     template<typename K, typename V>
     int HashTable<K, V>::hashcode(char c) {
          int hc = 127 + static_cast<int>(c) % 16908799;
          return hc;
     }

     template<typename K, typename V>
     int HashTable<K, V>::hashcode(unsigned long ul) {
          int hc = ul * 127;
          return (hc << 3);
     }

     template<typename K, typename V>
     int HashTable<K, V>::compression(int hc) {
          return abs(((31 * hc) + 524287) % this->N);
     }
  
     template<typename K, typename V>
     void HashTable<K, V>::insert(Entry<K, V> * e) {
          e->set_next_entry(NULL);
          int hc = hashcode(e->key);
          int index = compression(hc);

          if (hash_table[index] == NULL)
               hash_table[index] = e;
          else {
               Entry<K, V>* temp = hash_table[index];
               while (temp->get_next_entry() != NULL)
                    temp = temp->get_next_entry();
               temp->set_next_entry(e);
          }
          count++;
          if(compute_load_factor() > 1.2)
               resize(1);
     }
  
     template<typename K, typename V>
     void HashTable<K, V>::replace(Entry<K, V> * e1, Entry<K, V> * e2) {
          Entry<K, V>* temp = find(e1);
          temp->set_value(e2->get_value());
     }

     template<typename K, typename V>
     Entry<K, V> * HashTable<K, V>::find(Entry<K, V> * e) {
          int hc = hashcode(e->key);
          int index = compression(hc);
          Entry<K, V> * temp = hash_table[index];

          if (temp == NULL)
               return NULL;
          else {
               while (temp->get_value() != e->get_value() && temp != NULL)
                    temp = temp->get_next_entry();
               if (temp == NULL)
                    return NULL;
               else
                    return temp;
          }
     }
 
     template<typename K, typename V>
     void HashTable<K, V>::remove(Entry<K, V> * e) {
          int hc = hashcode(e->key);
          int index = compression(hc);
          Entry<K, V> * temp = hash_table[index];
          Entry<K, V> * temp2 = NULL;

          if (temp != NULL) {
               while (temp->get_value() != e->get_value()) {
                    temp2 = temp;
                    temp = temp->get_next_entry();
                    if (temp == NULL) {
                         cout << "no such data" << endl;
                         return;
                    }
               }
               if (temp2 == NULL) {
                    temp2 = temp->get_next_entry();
                    delete temp;
                    hash_table[index] = temp2;
               }
               else {
                    temp2->set_next_entry(temp->get_next_entry());
                    delete temp;
               }
               count--;
               if(compute_load_factor() < 0.5)
                    resize(0);
          }
          else
               cout << "no such data" << endl;
     }

     template<typename K, typename V>
     void HashTable<K, V>::resize(bool grow) {
          Entry<K, V> ** old_hash_table = hash_table;
          Entry<K, V> * temp = NULL;
          Entry<K, V> * temp2 = NULL;
          int oldN = this->N;

          if (grow == 1)
               this->N = this->N * 2; //size grows by 2
          else
               this->N = this->N / 2; //size decreases by 2

          hash_table = new Entry<K, V> *[this->N];
          for (int i = 0; i < this->N; i++)
               hash_table[i] = NULL;
          count = 0;

          for (int i = 0; i < oldN; i++) {
               if (old_hash_table[i] != NULL) {
                    temp = old_hash_table[i];
                    while (temp != NULL) {
                         temp2 = temp->get_next_entry();
                         insert(temp);
                         temp = temp2;
                    }
               }
          }
          delete[] old_hash_table;
     }
  
     template<typename K, typename V>
     double HashTable<K, V>::compute_load_factor() {
          return (this->count * 1.0) / this->N;
     }
     
     template<typename K, typename V>
     int HashTable<K, V>::longest_chain_length() {
          int counter = 0, temp = 0;
          Entry<K, V> * tempP;
          for (int i = 0; i < N; i++) {
               if (hash_table[i] != NULL) {
                    tempP = hash_table[i];
                    temp = 0;
                    while (tempP->get_next_entry() != NULL) {
                         tempP = tempP->get_next_entry();
                         temp++;
                    }
                    if (temp > counter)
                         counter = temp;
               }
          }
          return counter;
     }
   
     template<typename K, typename V>
     void HashTable<K, V>::print() {
          Entry<K, V>* temp = NULL;
          for (int i = 0; i < this->N; i++) {
               temp = hash_table[i];
               if (temp != NULL) {
                    cout << "[" << i << "] " << temp->get_value() << endl;
                    while (temp->get_next_entry() != NULL) {
                         temp = temp->get_next_entry();
                         cout << "\t" << temp->get_value() << endl;
                    }
               }
          }
     }
