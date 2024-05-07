#include "graphicsdisplay.h"

GraphicsDisplay::GraphicsDisplay(Xwindow &xw) 
: theDisplay(10, vector<char>(10, ' ')), xw{xw} {
    //initial configuration
    theDisplay[0] = {'8', ' ', 'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'};
    theDisplay[1] = {'7', ' ', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'};
    theDisplay[2] = {'6', ' ', ' ', '_', ' ', '_', ' ', '_', ' ', '_'};
    theDisplay[3] = {'5', ' ', '_', ' ', '_', ' ', '_', ' ', '_', ' '};
    theDisplay[4] = {'4', ' ', ' ', '_', ' ', '_', ' ', '_', ' ', '_'};
    theDisplay[5] = {'3', ' ', '_', ' ', '_', ' ', '_', ' ', '_', ' '};
    theDisplay[6] = {'2', ' ', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'};
    theDisplay[7] = {'1', ' ', 'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'};
    theDisplay[8] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
    theDisplay[9] = {' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
    
    for (int row=0; row<8; ++row) {
        for (int col=0; col<8; ++col) {
            //intial empty board
            if ((row%2==0 && col%2==0) || (row%2!=0 && col%2!=0)) {
                xw.fillRectangle(col*square,row*square,square,square,0);
            } else {
                xw.fillRectangle(col*square,row*square,square,square,1);
            }
            // add pieces
            if (theDisplay[row][col+2]!=' ' && theDisplay[row][col+2]!='_') {
                if (theDisplay[row][col+2]>='a') {
                    // distinguish two players with colour green and red
                    xw.drawString(col*square+35, row*square+40,
                    string(1,theDisplay[row][col+2]), 2);
                } else {
                    xw.drawString(col*square+35, row*square+40,
                    string(1,theDisplay[row][col+2]), 3);
                }
                
            }
        }
    }
}

void GraphicsDisplay::notify(const map<string, shared_ptr<Piece>>& board) {
    for (int row=0; row<8; ++row) {
        for (int col=0; col<8; ++col) {
            char letterCol = 'a' + col;
            char numRow = '0'+(8-row);
            // position on board
            string pos = string(1,letterCol) + string(1,numRow);
            auto it = board.find(pos);
            if (it != board.end() && it->second.get()!=nullptr) {
                // if board has a piece in that position
                Piece *p = it->second.get();
                char pieceChar = ' ';
                bool whitePiece = (p->getColour()=="white");
                // determine the character based on piece type and player
                if (p->getType() == "King") {
                    pieceChar = whitePiece ? 'K' : 'k';
                } else if (p->getType() == "Queen") {
                    pieceChar = whitePiece ? 'Q' : 'q';
                } else if (p->getType() == "Bishop") {
                    pieceChar = whitePiece ? 'B' : 'b';
                } else if (p->getType() == "Knight") {
                    pieceChar = whitePiece ? 'N' : 'n';
                } else if (p->getType() == "Rook") {
                    pieceChar = whitePiece ? 'R' : 'r';
                } else {
                    pieceChar = whitePiece ? 'P' : 'p';
                }
                //compare board current char with what we have in display
                if (theDisplay[row][col+2]!=pieceChar) {
                    theDisplay[row][col+2] = pieceChar;
                    //change that square by drawing another square on top of it
                    if ((row%2==0 && col%2==0) || (row%2!=0 && col%2!=0)) {
                        xw.fillRectangle(col*square,row*square,square,square,0);
                    } else {
                        xw.fillRectangle(col*square,row*square,square,square,1);
                    }
                    if (theDisplay[row][col+2]>'Z') {
                        // distinguish two players with colour green and red
                        xw.drawString(col*square+35, row*square+40,
                        string(1,theDisplay[row][col+2]), 2);
                    } else {
                        xw.drawString(col*square+35, row*square+40,
                        string(1,theDisplay[row][col+2]), 3);
                    }
                }
            } else if (theDisplay[row][col+2]!=' ' && theDisplay[row][col+2]!='_') {
                // display should set to empty square
                if ((row%2==0 && col%2==0) || (row%2!=0 && col%2!=0)) {
                    theDisplay[row][col+2]=' ';
                    xw.fillRectangle(col*square,row*square,square,square,0);
                } else {
                    theDisplay[row][col+2]='_';
                    xw.fillRectangle(col*square,row*square,square,square,1);
                }
            }
        }
    }
}

GraphicsDisplay::~GraphicsDisplay() {}
