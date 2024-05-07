#ifndef __MODEL_H__
#define __MODEL_H__
#include <iostream>
#include <vector>
#include "player.h"
#include "textdisplay.h"
#include "graphicsdisplay.h"
using namespace std;


class Model {
  Player whitePlayer; // indicate the type of player
  Player blackPlayer;
  bool inGame;
  map<string, shared_ptr<Piece>> board = {};
  // the views
  unique_ptr<TextDisplay> td;
  unique_ptr<GraphicsDisplay> gd;

  void setFlags(const string& pos1, const string& pos2);
  void moveHelper(const string& pos1, const string& pos2);
  bool simulateMove(string pos1, string pos2, const string& colour);
 public:
  Model(Xwindow& xw);
  ~Model() = default;
  
  //accessors
  vector<pair<string, string>> allLegalMoves(const string& colour); // call legalMoves() on all pieces
  double getScore(string colour);

  // the model setup
  void beginSetup();
  void game(const string& whiteType, const string& blackType);
  void addPiece(const string& piece, const string& pos); //to be called within setup()
  void removePiece(const string& pos); // to be called within setup()
  void setWhiteTurn(bool turn);
  void setBlackTurn(bool turn);

  void reset();

  // game logic functionalities
  bool isInCheck(const string& colour);
  bool isCheckmated(const string& colour);
  bool isStalemate();
  bool isInGame() const;
  bool validSetup();
  void endSetup();
  bool move(); // first check if isComputer() is true
  bool move(const string& pos1, const string& pos2); // called when both players are human
  bool move(const string& pos1, const string& pos2, const string& piece); // pawn promotion

  void notifyObservers();//call notify(board) on gd, td

  string endgame(); // called when resign/checkmate etc

  friend ostream &operator<<(ostream &out, const Model &m); //out<<*(m.td)
};

#endif
