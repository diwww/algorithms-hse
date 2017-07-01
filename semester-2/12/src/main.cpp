// main.cpp -- driver program for "Sum of Its Parts"

#pragma warning(disable:4786)

#include <iostream>
#include <fstream>
#include <cstdlib>

#include "parts.h"

using namespace std;

void loadDefinitions(const char* filename, NameContainer& partContainer)
{
    ifstream inf(filename);
    string part, subpart;
    int quantity;

    while (inf.good())
    {
        inf >> part >> quantity >> subpart;

        if (!inf.good())
            return;

        partContainer.addPart(part, quantity, subpart);
    }
}

void whatisQuery(const string& x, NameContainer& partContainer)
{
    Part* xp = partContainer.lookup(x);
    cout << endl;
    xp->describe();
}

void howmanyQuery(const string& x, const string& y, NameContainer& partContainer)
{
    Part* xp = partContainer.lookup(x);
    Part* yp = partContainer.lookup(y);
    cout << endl << y << " has " << yp->countHowMany(xp) << " " << x << endl;
}

void processQueries(const char* filename, NameContainer& partContainer)
{
    ifstream inf(filename);
    string query, x, y;

    while (inf.good())
    {
        inf >> query >> x;

        if (query == "howmany")
            inf >> y;

        if (!inf.good())
            return;

        if (query == "howmany")
            howmanyQuery(x, y, partContainer);
        else if (query == "whatis")
            whatisQuery(x, partContainer);
        else
        {
            cerr << "*** Illegal query: " << query << endl;
            return;
        }
    }
}

int main(void)
{
    NameContainer partContainer;


    loadDefinitions("/home/maxim/University/HomeWork/Algorithms/2_semester/algo-2sem-12/src/definitions.txt",
                    partContainer);
    processQueries("/home/maxim/University/HomeWork/Algorithms/2_semester/algo-2sem-12/src/queries.txt", partContainer);


    return EXIT_SUCCESS;
}
