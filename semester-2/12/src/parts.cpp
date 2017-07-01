#include "parts.h"

int Part::countHowMany(const Part* p)
{
    const Part* temp = p;
    int count = 1;
    while (temp != this && temp->parent != nullptr)
    {
        count *= temp->parent->subparts.at(temp);
        temp = temp->parent;
    }
    if (temp != this)
        throw std::logic_error("The given node is not in the tree.");
    return count;
}

void Part::describe()
{
    std::cout << "Part " << name << " subparts are:" << std::endl;
    for (PartToCount::iterator iter = subparts.begin(); iter != subparts.end(); ++iter)
        std::cout << iter->second << " " << iter->first->name << std::endl;
}

void Part::setCountAt(const Part* subpart, int count)
{
    subparts[subpart] = count;
}

void NameContainer::addPart(const std::string& part, int quantity, const std::string& subpart)
{
    Part* parent = lookup(part);
    Part* child = lookup(subpart);
    child->setParent(parent);
    parent->setCountAt(child, quantity);
}

Part* NameContainer::lookup(const std::string& name)
{
    if (!_nameMap[name])
        _nameMap[name] = new Part(name);

    return _nameMap[name];
}

NameContainer::~NameContainer()
{
    for (StringToPart::iterator iter = _nameMap.begin(); iter != _nameMap.end(); ++iter)
        delete iter->second;
}

void NameContainer::swap(NameContainer& l, NameContainer& r)
{
    std::swap(l._nameMap, r._nameMap);
}

NameContainer::NameContainer(const NameContainer& other)
{
    // It's difficult to copy nodes' parents,
    // that's why copy constructor is protected
}

NameContainer& NameContainer::operator=(const NameContainer& other)
{
    NameContainer temp(other);
    swap(*this, temp);
    return *this;
}
