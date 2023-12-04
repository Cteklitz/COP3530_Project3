/*
Corey Teklitz
12/1/2023
COP3530
Project 3
*/

#include "hashTable.h"
#include "book.h"
#include "bTree.h"
#include "user.h"
#include "rating.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <list>
#include <vector>
#include <ctime>
#include <chrono>
#include <unordered_set>

using namespace std;

long long ISBNtoInt(string in)
{
    long long out = 0;
    string sOut = "";

    for (int i = 0; i < in.length(); i++)
    {
        if (!isdigit(in[i]))
        {
            //cout << in[i];
            sOut += '0';
        }
        else
        {
            sOut += in[i];
        }
    }

    out = stoll(sOut);
    return out;
}

void parseUsers(vector<user>& users) // since users are in order by id in Users.csv, they will be indexed by ID in the vector by pushing them back in order
{                                    // also parses the ratings for the users
    // Users.csv
    fstream fin;
    fin.open("data/Users.csv", ios::in);

    string tempS;
    getline(fin, tempS); // skips the first line of the file

    int i = 0;
    bool last = false;

    while(!last)
    {
        getline(fin, tempS);
        string sId = "";

        if (tempS == "")
        {
            last = true;
            break;
        }

        for (int k = 0; tempS[k] != ','; k++)
        {
            sId += tempS[k];
        }
        //cout << sId << endl;

        user tempU(stoi(sId));
        users.push_back(tempU);
    }

    fin.close();

    // Ratings.csv
    fin.open("data/Ratings.csv", ios::in);
    getline(fin, tempS); // skips the first line of the file

    last = false;
    while(!last)
    {
        i++;
        // cout << i << " ";
        getline(fin, tempS);
        vector<string> lines;
        string cur = "";

        if (tempS == "")
        {
            last = true;
            break;
        }

        tempS += ",";

        for (int k = 0; k < tempS.length(); k++)
        {           
            if (tempS[k] == ',')
            {
                lines.push_back(cur);
                cur = "";
            }
            else if (tempS[k] == '"' || tempS[k] == '\\')
            {
                // skips formatting errors in the csv
                //cout << tempS << endl;
            }
            else
            {
                cur += tempS[k];
            }
        }

        //cout << lines[0] << ", " << lines[1] << ", " << lines[2] << endl;
        if (lines[2] != "0")
        {
            rating tempR(ISBNtoInt(lines[1]), stoi(lines[0]), stoi(lines[2]), lines[1]);
            users[stoi(lines[0])].addRating(tempR);
        }
    }

    fin.close();
}

void parseBooksHash(hashTable& hashtable, int type)
{
    fstream fin;
    fin.open("data/Books.csv", ios::in);

    string tempS;
    getline(fin, tempS); // skips the first line of the file

    int i = 0;
    bool last = false;

    while(!last) // loops thru all lines of Books.csv
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

        if (type == 0)
        {
            hashtable.insertbyName(tempB);
        }
        else if (type == 1)
        {
             hashtable.insertbyISBN(tempB);
        }
        i++;
    }
    fin.close();
}

void parseBooksB(bTree& btree)
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
        //cout << word << endl;
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

        long long tempISBN = btree.ISBNtoInt(tempB.getISBN());
        pair<long long, book> tempP;
        tempP.first = tempISBN;
        tempP.second = tempB;

        //cout << tempISBN << endl;

        btree.insert(tempP);
        
        i++;
    }
    fin.close();
}

int main()
{
    bool cont = true;
    cout << "Welcome to __! Type help for a list of commands" << endl;

    while (cont) // main user input loop, CLI for now, will change to GUI if time allows
    {
        float nameHashLF = 0.5;
        int nameHashStart = 100000;
        float ISBNHashLF = 0.5;
        int ISBNHashStart = 100000;
        int ISBNBTreeMinDeg = 3;
        int nameSearchType = 0; // 0 = hash, 1 = trie tree
        int ISBNSearchType = 0; // 0 = hash, 1 = b tree
        int minScore = 7; // min score to recommend a book

        hashTable* nameHash;
        hashTable* ISBNHash;
        bTree* ISBNBTree;
        vector<user>* users;

        vector<string> input;
        string raw;
        string temp = "";
        getline(cin, raw);
        raw += ' ';
        bool inQuote = false;

        for (int i = 0; i < raw.length(); i++) // parses raw input into a string vector of the words serperated by spaces
        {
            if (raw[i] == '"')
            {
                inQuote = !inQuote;
            }
            else if (raw[i] == ' ' && !inQuote)
            {
                input.push_back(temp);
                temp = "";
            }
            else
            {
                temp += raw[i];
            }
        }

        if (input[0] == "help") 
        {
            cout << "load --- loads all data from csvs, displays how long each loading took" << endl;
            cout << "search title [\"title\"] --- searchs the hash table for a title" << endl;
            cout << "search ISBN [btree/hash] [\"ISBN\"] --- searches either the b-tree or hash table for an ISBN" << endl;
            cout << "settings --- displays the current settings, data must be reloaded for changes to take effect" << endl;
            cout << "[titleLF/ISBNStartCap/bTreeMinDeg/...] [value] --- update the value for a setting, data must be reloaded for changes to take effect" << endl;
            cout << "recommend [\"title\"] --- will recommend books based a book inputted" << endl;
        }
        else if (input[0] == "recommend" || input[0] == "rec")
        {
            auto start = chrono::system_clock::now();

            book in;
            vector<user> reviewers;
            vector<rating> recsR;
            
            long long ISBN;

            if (nameSearchType == 0) // hash name search
            {
                in = nameHash->search(input[1]);
                if (in.getName() == "")
                {
                    cout << "Book title was not found!" << endl;
                }
                else
                {
                    ISBN = ISBNtoInt(in.getISBN());
                    cout << in.getName() << ", " << in.getISBN() << ", " << ISBN << endl;
                    cout << users->at(35).getId() << endl;
                    for (auto i : *users) // goes thru all users and adds the ones that reviewed the input book >= minScore to reviewers
                    {
                        if (i.checkISBNScore(ISBN, minScore))
                        {
                            reviewers.push_back(i);
                        }
                    }

                    for (auto i : reviewers) // goes thru the reveiwers and gets all the books they rated >= minScore
                    {
                        vector<rating> temp = i.getRatingsScored(ISBN, minScore);
                        for (auto j : temp)
                        {
                            bool found = false;
                            for (auto l : recsR)
                            {
                                if (l.getISBN() == ISBN) // prevent duplicates
                                {
                                    found = true;
                                }
                            }
                            if (!found)
                            {
                                recsR.push_back(j);
                                cout << j.getScore() << endl;
                            }
                        }
                    }
                }
            }
            else if (nameSearchType == 1) // trie name search
            {

            }

            if (ISBNSearchType == 0) // hash isbn search
            {
                for (auto i : recsR)
                {
                    book temp = ISBNHash->search(i.getsISBN());
                    if (temp.getName() != "")
                    {
                        cout << temp.getName() << ", by " << temp.getAuthor() << ". Published in " <<  temp.getYear() << endl;
                    }
                }
            }

            auto end = chrono::system_clock::now();
            chrono::duration<double> dur = end-start;

            cout << "Recommendation complete. Recommendation took: " << dur.count() << " seconds" << endl;
        }
        else if (input[0] == "load" || input[0] == "l")
        {
            // load users
            auto start = chrono::system_clock::now();

            users = new vector<user>;
            parseUsers(*users);

            auto end = chrono::system_clock::now();
            chrono::duration<double> dur = end-start;

            cout << "Users data loaded. Loading took: " << dur.count() << " seconds" << endl;

            // load hash by name
            start = chrono::system_clock::now();

            nameHash = new hashTable(nameHashStart, nameHashLF);
            parseBooksHash(*nameHash, 0);

            end = chrono::system_clock::now();
            dur = end-start;

            cout << "Hash Table, hashed by title, loaded. Loading took: " << dur.count() << " seconds" << endl;

            // load hash by ISBN
            start = chrono::system_clock::now();

            ISBNHash = new hashTable(ISBNHashStart, ISBNHashLF);
            parseBooksHash(*ISBNHash, 1);

            end = chrono::system_clock::now();
            dur = end-start;

            cout << "Hash Table, hashed by ISBN, loaded. Loading took: " << dur.count() << " seconds" << endl;

            // load btree by ISBN
            start = chrono::system_clock::now();

            ISBNBTree = new bTree(ISBNBTreeMinDeg);
            parseBooksB(*ISBNBTree);

            end = chrono::system_clock::now();
            dur = end-start;

            cout << "B-Tree, sorted by ISBN, loaded. Loading took: " << dur.count() << " seconds" << endl;

            // Other load functions go here
        }
        else if (input[0] == "search" || input[0] == "s")
        {
            if (input[1] == "ISBN")
            {
                if (input[2] == "btree")
                {
                    auto start = chrono::system_clock::now();

                    book temp = ISBNBTree->search(input[3]);               

                    auto end = chrono::system_clock::now();
                    chrono::duration<double> dur = end-start;

                    cout << "Search complete. Search took: " << dur.count() << " seconds" << endl;

                    if (temp.getName() == "")
                    {
                        cout << "Provided ISBN was not found" << endl;
                    }
                    else
                    {
                        cout << "Title: " << temp.getName() << endl;
                        cout << "Author: " << temp.getAuthor() << endl;
                        cout << "Year of Publication: " << temp.getYear() << endl;
                    }             
                }
                else if (input[2] == "hash")
                {
                    auto start = chrono::system_clock::now();

                    book temp = ISBNHash->search(input[3]);               

                    auto end = chrono::system_clock::now();
                    chrono::duration<double> dur = end-start;

                    cout << "Search complete. Search took: " << dur.count() << " seconds" << endl;

                    if (temp.getName() == "")
                    {
                        cout << "Provided ISBN was not found" << endl;
                    }
                    else
                    {
                        cout << "Title: " << temp.getName() << endl;
                        cout << "Author: " << temp.getAuthor() << endl;
                        cout << "Year of Publication: " << temp.getYear() << endl;
                    }  
                }
            }
            else if (input[1] == "title")
            {
                auto start = chrono::system_clock::now();

                book temp = nameHash->search(input[2]);               

                auto end = chrono::system_clock::now();
                chrono::duration<double> dur = end-start;

                cout << "Search complete. Search took: " << dur.count() << " seconds" << endl;

                if (temp.getName() == "")
                {
                    cout << "Provided title was not found" << endl;
                }
                else
                {
                    cout << "ISBN: " << temp.getISBN() << endl;
                    cout << "Author: " << temp.getAuthor() << endl;
                    cout << "Year of Publication: " << temp.getYear() << endl;
                }
            }
        }
        else if (input[0] == "titleLF")
        {
            nameHashLF = stof(input[1]);
        }
        else if (input[0] == "ISBNLF")
        {
            ISBNHashLF = stof(input[1]);
        }
        else if (input[0] == "titleStartCap")
        {
            nameHashStart = stoi(input[1]);
        }
        else if (input[0] == "ISBNStartCap")
        {
            ISBNHashStart = stoi(input[1]);
        }
        else if (input[0] == "bTreeMinDeg")
        {
            ISBNBTreeMinDeg = stoi(input[1]);
        }
        else if (input[0] == "titleSearchType")
        {
            nameSearchType = stoi(input[1]);
        }
        else if (input[0] == "ISBNSearchType")
        {
            ISBNSearchType = stoi(input[1]);
        }
        else if (input[0] == "minScore")
        {
            minScore = stoi(input[1]);
        }
        else if (input[0] == "settings")
        {
            cout << "Hash by title max load factor: " << nameHashLF << endl;
            cout << "Hash by ISBN max load factor: " << ISBNHashLF << endl;
            cout << "Hash by title starting capacity: " << nameHashStart << endl;
            cout << "Hash by ISBN starting capacity: " << ISBNHashStart << endl;
            cout << "ISBN B-Tree minimum degree: " << ISBNBTreeMinDeg << endl;
            cout << "Minimum score to recommend a book: " << minScore << endl;
            cout << "Title search type: ";
            if (nameSearchType == 0)
            {
                cout << "Hash Table" << endl;
            }
            else
            {
                cout << "Trie Tree" << endl;
            }
            cout << "ISBN search type: ";
            if (ISBNSearchType == 0)
            {
                cout << "Hash Table" << endl;
            }
            else
            {
                cout << "B-Tree" << endl;
            }
        }
        else if (input[0] == "exit" || input[0] == "e")
        {
            cont = false;
        }
        else
        {
            cout << "ERROR: Invalid Command - Type help for a list of commands" << endl;
        }
    }

    return 0;
}
