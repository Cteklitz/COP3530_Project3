#pragma once
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <cmath>
#include "book.h"


using namespace std;

class hashTable
{
    private:
        vector<list<pair<string,book>>> container; // uses lists for data collisions
        int size;
        int maxCap;
        float loadFactor;

    public:

        hashTable(int _maxCap, float _loadFactor)
        {
            maxCap = _maxCap;
            loadFactor = _loadFactor;
            size = 0;
            for (int i = 0; i < _maxCap; i++)
            {
                list<pair<string,book>> temp;
                container.push_back(temp);
            }
        }

        long hash(string key)
        {
            long long out = 0;
            for (int i = 0; i < key.length(); i++)
            {
                out += (abs(int(key[i])) * i); // sum(basic [ascii value] * i) hash function
            }

            out = out % maxCap;

            return out;
        }

        void insertbyISBN(book in)
        {
            long _hash = hash(in.getISBN()); // hashes the input isbn          

            pair<string, book> _new;
            _new.first = in.getISBN();
            _new.second = in;

            container[_hash].push_back(_new); // puts the input book into its bucket

            size++;

            if ((size / maxCap) > loadFactor) // doubles the size of the container when the max load factor is reached and rehashes all data
            {
                vector<list<pair<string,book>>> tempContainer; // temp container to hold old data to be rehashed to new container
                tempContainer = container;

                container.clear();
                size = 0;
                maxCap = maxCap * 2;
                for (int i = 0; i < maxCap; i++)
                {
                    list<pair<string,book>> temp;
                    container.push_back(temp);
                }

                for (int i = 0; i < maxCap / 2; i++)
                {
                    if (!tempContainer[i].empty())
                    {
                        for (auto j : tempContainer[i])
                        {
                            this->insertbyISBN(j.second);
                        }
                    }
                }
            }
        }

        void insertbyName(book in) // fucntions same as insertByISBN but using name as key
        {
            long _hash = hash(in.getName());           

            pair<string, book> _new;
            _new.first = in.getName();
            _new.second = in;

            container[_hash].push_back(_new);

            size++;

            if ((size / maxCap) > loadFactor)
            {
                vector<list<pair<string,book>>> tempContainer;
                tempContainer = container;

                container.clear();
                size = 0;
                maxCap = maxCap * 2;
                for (int i = 0; i < maxCap; i++)
                {
                    list<pair<string,book>> temp;
                    container.push_back(temp);
                }

                for (int i = 0; i < maxCap / 2; i++)
                {
                    if (!tempContainer[i].empty())
                    {
                        for (auto j : tempContainer[i])
                        {
                            this->insertbyName(j.second);
                        }
                    }
                }
            }
        }

        book search(string in) // returns the book at the location of the given key
        {
            long _hash = hash(in);

            for (auto i : container[_hash])
            {
                if (i.first == in)
                {
                    return i.second;
                }
            }

            book temp;
            return temp;
        }

};
