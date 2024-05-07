#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__
#include <iostream>
#include <vector>
#include "model.h"
using namespace std;


class Controller {
  unique_ptr<Model> m;

 public:
  Controller(); 
  ~Controller();
  
  // takes input, interpret commands, modify m 
  // prints the board with two views
  void control(istream &in, ostream &out);

};

#endif
