#ifndef __ROOK_H__
#define __ROOK_H__
#include <iostream>
#include <vector>
#include "piece.h"
using namespace std;


class Rook: public Piece {
 public:
  Rook(string colour, string position, string type);

  //accessor methods
  vector<pair<string, string>> legalMoves(map<string, shared_ptr<Piece>>& board) override; // return moves: <cur_pos, next_pos>

  ~Rook() override;

};
#endif
