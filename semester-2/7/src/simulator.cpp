#include <iostream>
#include <fstream>

using namespace std;

#include "simulator.h"
#include "event.h"

simulator::simulator(int seconds_per_page) {
  this->seconds_per_page = seconds_per_page;
}

simulator::~simulator() {}

void simulator::loadworkload (string file) {
  ifstream in;

  // Open workload file
  in.open (file.c_str());

  if (!in) {
    cerr << "Couldn't open input file, workload empty" << endl;
    return;
  }

  // Load workload into simulator
  while (1) {
    event e;

    in >> e;
 
    if (in.eof()) 
      break;

    addevent (e);
  }

}

void simulator::addevent(event e) {
  workload.push(e);
}
