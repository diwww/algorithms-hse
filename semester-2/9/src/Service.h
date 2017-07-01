#ifndef _SERVICE_H_
#define _SERVICE_H_

#include <string>

using namespace std;

class Service {

public:

    int fee;
    int distance;
    string destination;

    Service(string city, int f, int d) : fee(f),
    distance(d), destination(city) {}
}
;

#endif
