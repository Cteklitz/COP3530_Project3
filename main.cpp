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

void parseBooks(hashTable& hashtableName, hashTable& hashtableISBN)
{
    vector<string> test; // for testing

    fstream fin;
    fin.open("data/Books.csv", ios::in);

    string tempS;
    getline(fin, tempS); // skips the first line of the file

    int i = 0;
    bool last = false;

    while(!last)// for loop for testing, change to while(fin >> temp) for final
    {
        //cout << i << endl;
        getline(fin, tempS);
        book tempB;

        string word = "";
        string name = "";

        if (tempS == "")
        {
            last = true;
            break;
        }

        auto k = tempS.begin();

        while (*k != ',') // proccesses the ISBN
        {
            word += *k;
            k++;
        }
       // cout << word << endl;
        tempB.setISBN(word);
        word = "";
        k++;

        if (*k == '"') // proccesses the title, has to account for some titles having commas
        {
            int skips = 0;
            k++;
            while (*k != '"' || skips != 0)
            {
                if (*k == '\\')
                {
                    skips += 2;
                }
                else if(*k == '"')
                {
                    skips--;
                }
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
        //cout << word << endl;
        tempB.setName(word);
        test.push_back(word);
        word = "";
        k++;

        if (*k == '"') // proccesses the author, has to account for some titles having commas
        {
            int skips = 0;
            k++;
            while (*k != '"' || skips != 0)
            {
                if (*k == '\\')
                {
                    skips += 2;
                }
                else if(*k == '"')
                {
                    skips--;
                }
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
        //cout << word << endl;
        tempB.setAuthor(word);
        word = "";
        k++;

        while (*k != ',') // proccesses the year
        {
            word += *k;
            k++;
        }
        //cout << word << endl << endl;
        tempB.setYear(stoi(word));
        word = "";
        k++;

        hashtableName.insertbyName(tempB);
        hashtableISBN.insertbyISBN(tempB);
        i++;
    }
}


int main()
{
    hashTable hashtableTitle(100000,0.7);
    hashTable hashtableISBN(100000,0.7);

    parseBooks(hashtableTitle, hashtableISBN);

    return 0;
}