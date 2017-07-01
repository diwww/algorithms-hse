////////////////////////////////////////////////////////////////////////////////
// Module Name:  dna_repairer.h/cpp
// Authors:      Leonid Dworzanski, Sergey Shershakov
// Version:      0.2.0
// Date:         06.02.2017
// Copyright (c) The Team of "Algorithms and Data Structures" 2014–2017.
//
// This is a part of the course "Algorithms and Data Structures" 
// provided by  the School of Software Engineering of the Faculty 
// of Computer Science at the Higher School of Economics.
////////////////////////////////////////////////////////////////////////////////


#include "dna_repairer.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>

using namespace std;        // допустимо писать в глобальном пространстве только в cpp-файлах!


// Когда мы вычленили кусочки цепочек ДНК из общей массы, они гарантированно
// будут цельными. Например, a1:C a2:G a3:T.
// В map ключом служит не id, а id + number
// первого элемента цельной цепочки.
// Тогда в нашем случае dnaMap["a1"] == a1:C a2:G a3:T.
void addToMap(DNARepairer::Id2DnaMap& dnaMap, DNARepairer::NodeDNA* it1, DNARepairer::NodeDNA* it2)
{
    string key = it1->next->value.id + std::to_string(it1->next->value.number);
    if (dnaMap[key] == nullptr)
        dnaMap[key] = new DNARepairer::DNAChain;

    dnaMap[key]->moveNodesAfter(dnaMap[key]->getPreHead(), it1, it2);
}

void mapToStorage(const DNARepairer::Id2DnaMap& dnaMap, DNARepairer::ListOfDNAChains& storage)
{
    char id = '\0';
    storage = DNARepairer::ListOfDNAChains();
    DNARepairer::NodeDNAChain* t = storage.getPreHead();
    for (pair<string, DNARepairer::DNAChain*> i : dnaMap)
    {
        if (i.first[0] != id)
        {
            id = i.first[0];
            t = storage.insertNewElement(*i.second, t);
        }
        else
            t->value.moveNodesToEnd(i.second->getPreHead(), i.second->getLast());

        delete i.second;
    }
}

void DNARepairer::repairDNA()
{
    Id2DnaMap dnaMap;
    NodeDNAChain* itOutter = _dnaStorage.getPreHead();

    // Inspect every DNA chain
    while (itOutter->next != nullptr)
    {
        itOutter = itOutter->next;

        NodeDNA* it1 = itOutter->value.getPreHead(); // pre-first element of a chain
        NodeDNA* it2 = it1;
        // Go through DNA chain
        while (it2->next != nullptr)
        {
            // Если текущий элемент не является _preHead
            // И
            // (Если следующий элемент имеет другой id
            // ИЛИ
            // Если number следующего элемента не
            // больше на 1, чем number текущего)
            //
            // То есть тех случаях, когда цепочка не является цельной,
            // мы добавляем накопленную цепочку в map.
            bool condition = it2 != it1 &&
                             (it2->next->value.id != it1->next->value.id ||
                              it2->next->value.number != it2->value.number + 1);
            if (condition)
            {
                addToMap(dnaMap, it1, it2);
                it2 = it1;
            }
            else
                it2 = it2->next;
        }
        addToMap(dnaMap, it1, it2);
    }
    mapToStorage(dnaMap, _dnaStorage);
}

void DNARepairer::printDNAStorage()
{
    NodeDNAChain* itOutter = _dnaStorage.getPreHead();
    while (itOutter->next != nullptr)
    {
        itOutter = itOutter->next;
        NodeDNA* itInner = itOutter->value.getPreHead();

        while (itInner->next != nullptr)
        {
            itInner = itInner->next;
            cout << itInner->value.id << itInner->value.number
                 << ":" << itInner->value.base << " ";
        }

        cout << endl;
    }
}

void DNARepairer::readFile(const string& filename)
{
    ifstream fin(filename);

    if (!fin)
        throw std::runtime_error("Could not open file.");

    NodeDNAChain* it = _dnaStorage.getPreHead();
    string line;
    while (getline(fin, line))
    {
        NodeDNAChain* pNewNode = new NodeDNAChain;

        istringstream istr(line);

        string strTmp;
        while (istr >> strTmp)
        {
            DNAElement tmpDNAElement(strTmp);
            pNewNode->value.addElementToEnd(tmpDNAElement);
        }
        it->next = pNewNode;
        it = it->next;
    }
}

DNARepairer::ListOfDNAChains& DNARepairer::getDNAStorage()
{
    return _dnaStorage;
}
