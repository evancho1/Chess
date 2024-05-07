#ifndef __KING_H__
#define __KING_H__
#include <iostream>
#include <vector>
#include "piece.h"
using namespace std;


class King: public Piece {
    bool noKingNearby(string pos, map<string, shared_ptr<Piece>>& board);
 public:
  King(string colour, string position, string type);

  //accessor methods
  vector<pair<string, string>> legalMoves(map<string, shared_ptr<Piece>>& board) override; // return moves: <cur_pos, next_pos>

  ~King() override;

};
#endif
