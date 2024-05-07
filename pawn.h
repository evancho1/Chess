#ifndef __PAWN_H__
#define __PAWN_H__
#include <iostream>
#include <vector>
#include "piece.h"
using namespace std;


class Pawn: public Piece {
 public:
  Pawn(string colour, string position, string type);

  //accessor methods
  vector<pair<string, string>> legalMoves(map<string, shared_ptr<Piece>>& board) override; // return moves: <cur_pos, next_pos>

  ~Pawn() override;

};
#endif
