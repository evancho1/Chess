#ifndef __TEXTDISPLAY_H__
#define __TEXTDISPLAY_H__
#include <iostream>
#include <vector>
#include <memory>
#include <typeinfo>
#include <map>
#include "observer.h"
#include "king.h"
#include "queen.h"
#include "bishop.h"
#include "knight.h"
#include "rook.h"
#include "pawn.h"

class TextDisplay: public Observer {
  std::vector<std::vector<char>> theDisplay;
  void resetDisplay();

 public:
  TextDisplay();

  void notify(const map<string, shared_ptr<Piece>>& board) override;

  ~TextDisplay();

  friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};

#endif
