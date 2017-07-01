#ifndef JOB_H
#define JOB_H

#include <iostream>
#include <string>

using namespace std;

class job {
  private:
    string user;
    int number_of_pages;

  public:
    job();
    job(int number_of_pages, string user);

    string getuser() const; 
    int getnumpages() const;

    friend istream &operator>>(istream &stream, job &j);
    friend ostream &operator<<(ostream &stream, job &j);
};

#endif
