#pragma once
#include "book.h"
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

class TrieNode {
public:
    unordered_map<char, TrieNode*> children;
    bool isLeaf;
    book* bookInfo;

    TrieNode() : isLeaf(false), bookInfo(nullptr) {}

    ~TrieNode() {
        for (auto& child : children) {
            delete child.second;
        }
    }
};

class TrieTree {
private:
    TrieNode* root;

public:
    TrieTree() {
        root = new TrieNode();
    }

    ~TrieTree() {
        delete root;
    }

    void insert(book& b) {
        TrieNode* current = root;

        for (char ch : b.getName()) {
            if (current->children.find(ch) == current->children.end()) {
                current->children[ch] = new TrieNode();
            }
            current = current->children[ch];
        }

        current->isLeaf = true;
        current->bookInfo = &b;
    }

    bool search(const string& title) {
        TrieNode* current = root;

        for (char ch : title) {
            if (current->children.find(ch) == current->children.end()) {
                return false; 
            }
            current = current->children[ch];
        }

        return current->isLeaf;
    }

    book search(const string& title) const {
        TrieNode* current = root;

        for (char ch : title) {
            if (current->children.find(ch) == current->children.end()) {
                return book(); 
            }
            current = current->children[ch];
        }
         
        if (current->isLeaf) { 
            return *(current->bookInfo); 
        }
        else {
            return book(); 
        } 
    }
};

