#ifndef KMP_H
#define KMP_H

#include <vector>
#include <string>

/**
* Here is a template for implementation of Knuth-Morris-Pratt (KMP) algorithm for searching substring occurences in a string.
* It consists of only one function so feel free to add any additional classes, functions etc. in your kmp.cpp file.
* Note that the only file you should submit is kmp.cpp created by yourself and of course you should not alter this file.
*/


/**
* A function to find all occurrences of a substring in source string using KMP algorithm.
*
* Parameters:
*  string& source    - a reference to a string, where positions of substrings are searched.
*  string& substring - a reference to a string, occurrences of which are searched in the source string.
*
* Returns:
*  a pointer to integer values vector which should contain all values of indices of starts of passed substring
*  in the source string. In case of zero such substrings an empty vector should be returned (not a nullptr).
*/
std::vector<int>* find_substrings(std::string& source, std::string& substring);

#endif