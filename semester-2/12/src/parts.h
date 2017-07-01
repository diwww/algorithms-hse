#ifndef _PARTS_H_
#define _PARTS_H_

#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <utility>

class Part;

typedef std::map<const Part*, int> PartToCount;
typedef std::map<std::string, Part*> StringToPart;

//**************** Part ****************
class Part
{
public:
    Part(const std::string& n, const Part* p = nullptr) : name(n), parent(p) { }
    void describe();
    int countHowMany(const Part* p);

private:
    PartToCount subparts;
    const std::string name;
    const Part* parent;

public:
    const std::string& getName() const { return name; }
    const Part* getParent() const { return parent; }
    void setCountAt(const Part* subpart, int count);
    void setParent(const Part* parent) { this->parent = parent; }
};


//**************** NameContainer ****************
class NameContainer
{
public:
    NameContainer() { };
    void addPart(const std::string& part, int quantity, const std::string& subpart);
    Part* lookup(const std::string& name);
    ~NameContainer();
private:
    StringToPart _nameMap;

protected:
    void swap(NameContainer& l, NameContainer& r);
    NameContainer(const NameContainer& other);
    NameContainer& operator=(const NameContainer& other);
};

#endif // _PARTS_H_
