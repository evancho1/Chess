#ifndef __PIECE_H__
#define __PIECE_H__
#include <iostream>
#include <vector>
#include <memory>
#include <map>
using namespace std;


class Piece {
  string colour;
  string position;
  string type;
  bool hasMoved = false;
  bool justDoubleStepped = false;
  const int point;

 public:

  Piece(string colour, string position, string type, int point);
  Piece(const Piece& other); // copy constructor used in simulateMove()
  virtual ~Piece() = default;

  //accessor methods
  string getColour() const;
  string getPosition() const;
  string getType() const;
  bool getHasMoved() const;
  bool isDoubleStepped() const;
  const int getPoint() const;

  //mutator methods
  void setColour(string colour);
  void setPosition(string position);
  void setType(string type);
  void setHasMoved(bool hasMoved);
  void setDoubleStepped (bool justDoubleStepped);

  // Other methods
  
  virtual vector<pair<string, string>> legalMoves(map<string, shared_ptr<Piece>>& board) = 0; 
  
  
};
#endif
