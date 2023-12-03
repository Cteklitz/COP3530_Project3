/*
Corey Teklitz
12/1/2023
COP3530
Project 3
*/

#include "hashTable.h"
#include "book.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <list>
#include <vector>

using namespace std;

void parseBooks(hashTable& hashtable)
{
    vector<string> test; // for testing

    fstream fin;
    fin.open("data/Books.csv", ios::in);

    string tempS;
    getline(fin, tempS); // skips the first line of the file

    for(int i = 0; i < 1000; i++) // for loop for testing, change to while(fin >> temp) for final
    {
        cout << i << endl;
        getline(fin, tempS);
        book tempB;

        string word = "";
        string name = "";

        auto k = tempS.begin();

        while (*k != ',') // proccesses the ISBN
        {
            word += *k;
            k++;
        }
        cout << word << endl;
        tempB.setISBN(word);
        word = "";
        k++;

        if (*k == '"') // proccesses the title, has to account for some titles having commas
        {
            k++;
            while (*k != '"')
            {
                word += *k;
            k++;
            }
            k++;
        }
        else
        {
            while (*k != ',') 
            {
                word += *k;
             k++;
           }
        }
        cout << word << endl;
        tempB.setName(word);
        test.push_back(word);
        word = "";
        k++;

        if (*k == '"') // proccesses the author, has to account for some titles having commas
        {
            k++;
            while (*k != '"')
            {
                word += *k;
            k++;
            }
            k++;
        }
        else
        {
            while (*k != ',') 
            {
                word += *k;
             k++;
           }
        }
        cout << word << endl;
        tempB.setAuthor(word);
        word = "";
        k++;

        while (*k != ',') // proccesses the year
        {
            word += *k;
            k++;
        }
        cout << word << endl << endl;
        tempB.setYear(stoi(word));
        word = "";
        k++;

        hashtable.insert(tempB);
    }

    cout << "BOOKS PROCCESSED" << endl;

    for (auto i : test)
    {
        cout << i << endl;
        book testB = hashtable.getBook(i);
        cout << testB.getName() << ", " << testB.getAuthor() << ", " << testB.getYear() << ", " << testB.getISBN() << endl;
    }
}

int main()
{
    hashTable hashtable(500,0.7);

    parseBooks(hashtable);

    return 0;
}