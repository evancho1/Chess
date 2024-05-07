#ifndef __GRAPHICSDISPLAY_H__
#define __GRAPHICSDISPLAY_H__
#include "observer.h"
#include <memory>
#include <typeinfo>
#include <map>
#include "observer.h"
#include "piece.h"
#include "king.h"
#include "queen.h"
#include "bishop.h"
#include "knight.h"
#include "rook.h"
#include "pawn.h"
#include "window.h"

class GraphicsDisplay: public Observer {
  const int square = 70;
  std::vector<std::vector<char>> theDisplay;
  Xwindow &xw;

 public:
 // in model ctor, create Xwindow(640, 640), pass this in when create display
  GraphicsDisplay(Xwindow &xw);

  void notify(const map<string, shared_ptr<Piece>>& board) override;

  ~GraphicsDisplay();

};

#endif
