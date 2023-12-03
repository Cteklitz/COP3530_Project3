
#pragma once
#include <iostream>
#include <string>
#include <list>
#include <vector>


using namespace std;

class book
{
    private:
        string name;
        string ISBN;
        int year;
        string author;

    public:
        book()
        {
            name = "";
            ISBN = "";
            author = "";
            year = 0;
        }
        book(string _name, string _ISBN, string _author, int _year)
        {
            name = _name;
            ISBN = _ISBN;
            author = _author;
            year = _year;
        }

        void setName(string in)
        {
            name = in;
        }
        void setISBN(string in)
        {
            ISBN = in;
        }
        void setAuthor(string in)
        {
            author = in;
        }
        void setYear(int in)
        {
            year = in;
        }

        string getName()
        {
            return name;
        }
        string getISBN()
        {
            return ISBN;
        }
        string getAuthor()
        {
            return author;
        }
        int getYear()
        {
            return year;
        }

};