#include "dictionary.h"

Dictionary::Dictionary(const std::string& path)
{
    std::ifstream fin;
    fin.open(path);
    if (!fin.good())
        throw std::invalid_argument("File is unavailable.");
    while (!fin.eof() && fin.good())
    {
        std::string word;
        fin >> word;
        this->insert(word);
    }
}
