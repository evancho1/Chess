#ifndef __BISHOP_H__
#define __BISHOP_H__
#include <iostream>
#include <vector>
#include "piece.h"
using namespace std;


class Bishop: public Piece {

 public:
  Bishop(string colour, string position, string type);

  //accessor methods
  vector<pair<string, string>> legalMoves(map<string, shared_ptr<Piece>>& board) override; // return moves: <cur_pos, next_pos>

  ~Bishop() override;

};
#endif
