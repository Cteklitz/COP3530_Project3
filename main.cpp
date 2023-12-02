/*
Corey Teklitz
12/1/2023
COP3530
Project 3
*/

#include "hashTable.h"
#include "book.h"
#include <iostream>
#include <string>
#include <list>
#include <vector>

using namespace std;



int main()
{
    hashTable hashtable(1,0.8);

    book temp("name", "1234", "author", 2000);
    hashtable.insert(temp);
    cout << hashtable.getBook("name").getName();

    return 0;
}