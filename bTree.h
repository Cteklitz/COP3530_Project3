#pragma once
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <cmath>
#include "book.h"

using namespace std;

class Node
{
    private:
        vector<pair<long long,book>> keys;
        int minDeg;
        vector<Node*> children;
        bool isLeaf;

    public:
    Node(int _minDeg, bool _isLeaf)
    {
        minDeg = _minDeg;
        isLeaf = _isLeaf;
    }

    book search(long long in)
    {
        int i = 0;
        while (i < keys.size() && keys[i].first < in)
        {
            i++;
        }

        if (keys[i].first == in)
        {
            return keys[i].second;
        }
        if (isLeaf)
        {
            book temp;
            return temp;
        }

        return children[i]->search(in);
    }

    void insert(pair<long long,book> in)
    {
        if (this->isLeaf)
        {
            bool placed = false;

            if (keys.empty())
            {
                keys.push_back(in);
            }
            else
            {
                for (int i = 0; i < keys.size(); i++) // finds the correct space in the leaf to place the new key, places it at end if it is largest
                {
                    if (in.first < keys[i].first)
                    {
                        keys.insert(keys.begin() + i, in);
                        placed = true;
                        i = keys.size() + 1;
                    }
                }
                if (!placed)
                {
                    keys.push_back(in);
                }
            }
        }
        else
        {
            int j = keys.size() - 1; // initalize j to right most key
            while (j >= 0 && keys[j].first > in.first) // finds the correct child to send new value to
            {
                j--;
            }

            if (children[j + 1]->keys.size() == 2 * minDeg - 1) // checks if the child is full
            {
                split(j + 1, children[j + 1]);

                if (keys[j + 1].first < in.first)
                {
                    j++;
                }
            }

            children[j + 1]->insert(in);
        }
    }

    void split(int i, Node* inNode)
    {
        Node* newNode = new Node(inNode->minDeg, inNode->isLeaf);
        
        for (int j = 0; j < minDeg - 1; j++) // copy last mindeg - 1 keys from in to new
        {
            newNode->keys.insert(newNode->keys.begin() + j, inNode->keys[j + minDeg]);          
        }

        for (int j = 0; j < minDeg - 1; j++) // erase copied keys from in
        {
            inNode->keys.erase(inNode->keys.begin() + j + minDeg);     
        }

        if (!inNode->isLeaf) // copy last mindeg children from in to new
        {
            for (int j = 0; j < minDeg; j++)
            {
                newNode->children.insert(newNode->children.begin() + j, inNode->children[j + minDeg]);
            }
        }

        children.insert(children.begin() + i + 1, newNode);

        keys.insert(keys.begin() + i, inNode->keys[minDeg - 1]); // copy middle key of in to this

        inNode->keys.erase(inNode->keys.begin() + minDeg - 1); // delete copied key
    }
    
friend class bTree;
};

class bTree
{
    private:
    Node *root;
    int minDeg;

    public:
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

        bTree(int _minDeg)
        {
            root = nullptr;
            minDeg = _minDeg;
        }

        book search(string in)
        {
            return root->search(ISBNtoInt(in));
        }

        void insert(pair<long long,book> in)
        {
            if (root == nullptr)
            {
                root = new Node(minDeg, true);
                root->keys.push_back(in);
            }
            else
            {
                if (root->keys.size() == 2 * minDeg - 1) // checks if root is full
                {
                    Node* newNode = new Node(minDeg, false);

                    newNode->children.push_back(root);
                    newNode->split(0, root);

                    int i = 0;
                    if (newNode->keys[0].first < in.first)
                    {
                        i = 1;
                    }

                    newNode->children[i]->insert(in);

                    root = newNode;
                }
                else
                {
                    root->insert(in);
                }
            }
        }

};