#ifndef _OBSERVER_H_
#define _OBSERVER_H_
#include "piece.h"
#include <string>
#include <memory>
using namespace std;

class Observer {
 public:
  virtual void notify(const map<string, shared_ptr<Piece>>& board) = 0;  // c is the Cell that called the notify method
  virtual ~Observer() = default;
};
#endif
