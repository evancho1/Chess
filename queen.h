#ifndef __QUEEN_H__
#define __QUEEN_H__
#include <iostream>
#include <vector>
#include "piece.h"
using namespace std;


class Queen: public Piece {

 public:
  Queen(string colour, string position, string type);

  //accessor methods
  vector<pair<string, string>> legalMoves(map<string, shared_ptr<Piece>>& board) override; // return moves: <cur_pos, next_pos>

  ~Queen() override;

};
#endif
