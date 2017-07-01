#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <queue>
#include <string>

using namespace std; 

#include "event.h"

class simulator {

  protected:
    int seconds_per_page;
    queue<event> workload;

    virtual void addevent(event e);
    virtual void loadworkload(string file);

  public:
    simulator(int seconds_per_page);
    virtual void simulate(string file) = 0;  // abstract
    virtual ~simulator();
};

#endif
