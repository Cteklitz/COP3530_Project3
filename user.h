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
    vector<rating> getRatingsScored(long long in, int _score) // returns a vector of ratings that are >= to _score and not the inputed book
    {
        vector<rating> out;
        
        for (auto i : ratings)
        {
            if (i.getISBN() != in)
            {
                if (i.getScore() >= _score)
                {
                    out.push_back(i);
                }
            }
        }

        return out;
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
