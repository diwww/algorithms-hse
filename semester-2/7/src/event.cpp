#include <iostream>

using namespace std;

#include "event.h"

event::event (job j, int wait_until) {
  this->j = j;
  this->wait_until = wait_until;
}


event::event () {
  this->wait_until = -1;
}


job event::getjob() const {
  return j;
}


int event::arrival_time() const {
  return wait_until;
}

istream &operator>>(istream &stream, event &e) {
  stream >> e.wait_until;
  
  stream >> e.j;

  return stream;
}


ostream &operator<<(ostream &stream, event &e) {
  stream << e.wait_until << " " << e.j;

  return stream;
}

