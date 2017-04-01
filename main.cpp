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
     //please update the below line if you change any of the data type so the user knows what to input
     cout << "\n***  key type is unsigned long  and  data type is string  ***\n";
     
     int choice;
     cout << "What is the size of the hash table that you want to create?\n";
     do {
          cout << "\t: ";
          cin >> choice;
     } while (choice <= 0);

     HashTable<keyType, valueType>  table_01(choice);
     keyType key;
     valueType value;
     Entry<keyType, valueType> * e;

     cout << "\nDo you want to fill the table with random 100,000 entries?(only for string) [1 for yes/ 0 for no]" << endl;
     do {
          cout << "\t: ";
          cin >> choice;
     } while (choice > 1 || choice < 0);

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

     Entry<keyType, valueType> * e2;

     //prints out a menu and lets the user choose what to do.
     do {
          cout << "\nwhat do you want to do?"
               << "\n\t1. insert"
               << "\n\t2. replace"
               << "\n\t3. remove"
               << "\n\t4. compute load factor"
               << "\n\t5. longest chain length"
               << "\n\t6. print"
               << "\n\t7. exit" << endl;
          do {
               cout << "\t: ";
               cin >> choice;
          } while ( choice < 1 || choice > 7 );

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
          case 4: cout << "Load Factor: " << table_01.compute_load_factor() << endl;
               break;
          case 5: cout << "Longest Chain: " << table_01.longest_chain_length() << endl;
               break;
          case 6: table_01.print();
               break;
          case 7: return 0;
          }
     } while (1);

     return 0;
}
