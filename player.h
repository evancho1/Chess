#ifndef __PLAYER_H__
#define __PLAYER_H__
#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include "bishop.h"
#include "king.h"
#include "knight.h"
#include "pawn.h"
#include "queen.h"
#include "rook.h"

using namespace std;

enum class Type{human, computerLevel1, computerLevel2, computerLevel3, computerLevel4};

class Player {
  double score = 0;
  Type playerType;
  bool turn;
  string colour;
  vector<shared_ptr<Piece>> pieces;

 public:
  Player(string colour);
  ~Player();
  

  //accessors
  bool isComputer() const;
  Type getType() const; //check isComputer first
  double getScore() const;
  string getColour() const;
  bool getTurn() const;
  vector<shared_ptr<Piece>> getPieces() const;

  //mutators
  void setTurn(bool newTurn); //during setup
  void setType(string newType);
  void setScore(double newScore);
  void setColour(string colour);
  void switchTurn();
  void incScore(double n);
  void add(string piece, string pos); // append to vector
  void deletePiece(int index);
  void clear();
  void reset();

};

#endif
