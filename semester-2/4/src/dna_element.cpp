#include "dna_element.h"
#include <string>
#include <map>

const std::string IDS="abcdefghijklmnopqrstuvwxyz";
const std::string BASES = "ACTG";

DNAElement::DNAElement()
{
    number = {};
    id = {};
    base = {};
}

DNAElement::DNAElement(const std::string& description)
{
    readFromString(description);
}

void DNAElement::readFromString(const std::string& description)
{
    // id
    id = description[0];
    if(IDS.find(id)==std::string::npos)
        throw std::invalid_argument("Wrong id format.");
    // number
    size_t delimPos = description.find(':');
    std::string numberStr = description.substr(1, delimPos - 1);
    number = std::stoi(numberStr, nullptr); // throws invalid_argument
    // base
    base = description.substr(delimPos + 1);
    if (base.length() > 1 || BASES.find(base) == std::string::npos)
        throw std::invalid_argument("Wrong base format.");
}
