#pragma once
#include <iostream>
#include <string>
#include <list>
#include <string>
#include <vector>

using namespace std;

class rating
{
    private:
    long long ISBN;
    int user;
    int score;
    string sISBN;

    public:
    rating(long long _ISBN, int _user, int _score, string _sISBN)
    {
        ISBN = _ISBN;
        user = _user;
        score = _score;
        sISBN = _sISBN;
    }

    long long getISBN()
    {
        return ISBN;
    }
    int getUser()
    {
        return user;
    }
    int getScore()
    {
        return score;
    }
    string getsISBN()
    {
        return sISBN;
    }
};