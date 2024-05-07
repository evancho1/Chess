#ifndef __KNIGHT_H__
#define __KNIGHT_H__
#include <iostream>
#include <vector>
#include "piece.h"
using namespace std;


class Knight: public Piece {

 public:
  Knight(string colour, string position, string type);

  //accessor methods
  vector<pair<string, string>> legalMoves(map<string, shared_ptr<Piece>>& board) override; // return moves: <cur_pos, next_pos>

  ~Knight();

};
#endif
