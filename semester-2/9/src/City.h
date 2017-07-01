#ifndef _CITY_H_
#define _CITY_H_

using namespace std;

class City {

public:

    // name of the city
    string name;

    // bookkeeping info
    bool	visited;
    int total_fee;
    int total_distance;
    string from_city;

    City() : name(""), visited(false), total_fee(0), total_distance(0), from_city("") {}

    City(string const &s): name(s), visited(false), total_fee(0), total_distance(0), from_city("") {}}
;

#endif
