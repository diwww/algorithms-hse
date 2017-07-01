#ifndef EVENT_H
#define EVENT_H

#include <iostream>

using namespace std;

#include "job.h"

class event {
  private:
    job j;  
    int wait_until;

  public:
    event();
    event(job j, int wait_until);

    job getjob() const;
    int arrival_time() const;

    friend istream &operator>>(istream &stream, event &e);
    friend ostream &operator<<(ostream &stream, event &e);
};

#endif
