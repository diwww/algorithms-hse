// Name: Surovtsev Maxim
// Group: BSE151
// Used books: Introduction to Algorithms by Thomas H. Cormen

#include "kmp.h"

// Prefix function
int *pref(std::string temp)
{
    int *p = new int[temp.length()];
    p[0] = 0;
    int k = 0;

    for (int i = 1; i < temp.length(); ++i)
    {
        while (k > 0 && temp[i] != temp[k])
            k = p[k - 1];
        if (temp[i] == temp[k])
            k++;
        p[i] = k;
    }

    return p;
}

std::vector<int> *find_substrings(std::string &source, std::string &substring)
{
    int *p = pref(substring); // Prefix function array
    int match_count = 0;
    std::vector<int> *indices = new std::vector<int>();

    for (int i = 0; i < source.length(); ++i)
    {
        while (match_count > 0 && substring[match_count] != source[i])
            match_count = p[match_count - 1];
        if (substring[match_count] == source[i])
            match_count++;
        // If substring exists in source
        if (match_count == substring.length())
        {
            indices->push_back(i - (int) substring.length() + 1);
            match_count = p[match_count - 1];
        }
    }

    delete[] p;
    return indices;
}