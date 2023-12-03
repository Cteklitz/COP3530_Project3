
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
        vector<list<pair<string,book>>> container;
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
            long out = 0;
            for (int i = 0; i < key.length(); i++)
            {
                out += (abs(int(key[i])) * i);
            }

            out = out % maxCap;

            return out;
        }

        void insert(book in)
        {
            long _hash = hash(in.getName());           

            pair<string, book> _new;
            _new.first = in.getName();
            _new.second = in;

            container[_hash].push_back(_new);

            size++;

            // todo: implement growth when LF reached
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
                            this->insert(j.second);
                        }
                    }
                }
            }
        }

        book getBook(string _name)
        {
            long _hash = hash(_name);

            for (auto i : container[_hash])
            {
                if (i.first == _name)
                {
                    return i.second;
                }
            }

            book temp;
            return temp;
        }

};