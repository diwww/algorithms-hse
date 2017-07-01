#include <iostream>
#include <vector>
#include "kmp.h"

using std::string;
using std::vector;
using std::cin;
using std::cout;
using std::endl;

vector<int> find_all_substrings_starts(string str, string pattern)
{
    unsigned long i = 0;
    vector<int> res;
    while (str.find(pattern, i) <= str.length())
    {
        res.push_back((int) str.find(pattern, i));
        i = str.find(pattern, i) + 1;
    }
    return res;
}


int main()
{
    string str = "abdabdabcabeabcabdabcabc", pattern = "abda";
    vector<int> *k = find_substrings(str, pattern);
    vector<int> good = find_all_substrings_starts(str, pattern);
    vector<int> check;
    for (int i = 0; i < k->size(); ++i)
    {
        int tmp = k->at((unsigned long) i);
        check.push_back(tmp);
    }
    cout << (good == check);
    return 0;
}
