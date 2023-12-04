#pragma once
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include "rating.h"
#include "book.h"

class user
{
    private:
    vector<rating> ratings;
    int id;

    public:
    user(int _id)
    {
        id = _id;
    }

    void addRating(rating in)
    {
        ratings.push_back(in);
    }

    vector<rating> getRatings()
    {
        return ratings;
    }
    int getId()
    {
        return id;
    }
    bool checkISBN(long long in) // checks if a user has reviewed a certain book
    {
        for (auto i : ratings)
        {
            if (i.getISBN() == in)
            {
                return true;
            }
        }
        return false;
    }
    bool checkISBNScore(long long in, int _score) // checks if a user has reviewed a certain book and if they have given it a score >= _score
    {
        for (auto i : ratings)
        {
            if (i.getISBN() == in)
            {
                if (i.getScore() >= _score)
                {
                    return true;
                }
            }
        }
        return false;
    }
};
