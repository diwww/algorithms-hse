#include <iostream>

using namespace std;

#include "job.h"

job::job (int number_of_pages, string user) {
  this->number_of_pages = number_of_pages;
  this->user = user;
}


job::job () {
  this->number_of_pages = -1;
  this->user = "";
}

string job::getuser() const {
  return user;
}


int job::getnumpages() const {
  return number_of_pages;
}

istream &operator>>(istream &stream, job &j) {
  stream >> j.number_of_pages;
  stream >> j.user;

  return stream;
}


ostream &operator<<(ostream &stream, job &j) {

	int pages = j.number_of_pages;
	
	stream << pages << " page" 
		   << ((pages == 1) ? "" : "s") 
		   << " from " << j.user;
  
  return stream;
}
