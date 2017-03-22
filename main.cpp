#include <iostream>
#include <cstddef>
#include <string>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include "HashTable.cpp"

using namespace std;

typedef unsigned long keyType;
typedef string valueType;

int main()
{
     int choice;
     cout << "What is the size of the hash table that you want to create?\n\t: ";
     cin >> choice;

     HashTable<keyType, valueType>  table_01(choice);
     keyType key;
     valueType value;
     Entry<keyType, valueType> * e;

     cout << "Do you want to fill the table with random 100,000 entries?(only for string) [1 for yes/ 0 for no]\n\t: ";
     cin >> choice;

     if (choice == 1) {
          //seed the random number generator
          srand(42);

          // Fill the table with random entries
          for (int i = 0; i < 100000; i++)
          {
               /* create a random entry */
               key = (sizeof(int) < sizeof(long)) ? (static_cast<int>(((unsigned long)rand()) << (sizeof(int) * 8)) | rand()) : rand();
               value = "";
               for (int j = 0; j < (rand() % 45 + 1); j++)
                    value += 'a' + rand() % 26;
               e = new Entry<unsigned long, string>(key, value);

               table_01.insert(e);
          }
     }

     bool resizeBool;
     Entry<keyType, valueType> * e2;

     //please update the below line if you change any of the data type so the user knows what to input
     cout << "\n***key type is unsigned long***\n***data type is string***\n";

     //prints out a menu and lets the user choose what to do.
     do {
          cout << "\nwhat do you want to do?"
               << "\n\t1. insert"
               << "\n\t2. replace"
               << "\n\t3. remove"
               << "\n\t4. resize"
               << "\n\t5. compute load factor"
               << "\n\t6. longest chain length"
               << "\n\t7. print"
               << "\n\t8. exit\n\t: ";
          cin >> choice;

          switch (choice) {
          case 1: cout << "enter value : ";
               cin >> value;
               cout << "enter key : ";
               cin >> key;
               e = new Entry<keyType, valueType>(key, value);
               table_01.insert(e);
               break;
          case 2: cout << "enter value to replace : ";
               cin >> value;
               cout << "enter key : ";
               cin >> key;
               e = new Entry<keyType, valueType>(key, value);
               cout << "enter value to be replaced with : ";
               cin >> value;
               e2 = new Entry<keyType, valueType>(key, value);
               table_01.replace(e, e2);
               break;
          case 3: cout << "enter value to remove : ";
               cin >> value;
               cout << "enter key : ";
               cin >> key;
               e = new Entry<keyType, valueType>(key, value);
               table_01.remove(e);
               break;
          case 4: cout << "do you want to increase or decrease the size? (1 to increase / 0 to decrease): ";
               cin >> resizeBool;
               table_01.resize(resizeBool);
               break;
          case 5: cout << "Load Factor: " << table_01.compute_load_factor() << endl;
               break;
          case 6: cout << "Longest Chain: " << table_01.longest_chain_length() << endl;
               break;
          case 7: table_01.print();
               break;
          case 8: return 0;
          }
     } while (1);

     return 0;
}
