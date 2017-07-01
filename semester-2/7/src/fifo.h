#ifndef PRINTERSIMULATION_FIFO_H
#define PRINTERSIMULATION_FIFO_H

#include <fstream>
#include "simulator.h"

class fifo : public simulator
{
public:
    fifo(int seconds_per_page) : simulator(seconds_per_page) { };

    void simulate(string file);

    ~fifo() { };

protected:
    ofstream out;
    queue<event> printQueue;
    int genTimer = 0; // general timer, counts the whole time
    int printTimer = 0; // timer for print operation
    int latency = 0;
    void info(bool);
};


#endif //PRINTERSIMULATION_FIFO_H
