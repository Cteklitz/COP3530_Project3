#pragma once
#include <iostream>
#include <string>
#include <list>
#include <vector>

class rating
{
    private:
    long long ISBN;
    int user;
    int score;

    public:
    rating(long long _ISBN, int _user, int _score)
    {
        ISBN = _ISBN;
        user = _user;
        score = _score;
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
};