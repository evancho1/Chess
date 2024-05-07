#include <iostream>
#include "textdisplay.h"

using namespace std;

TextDisplay::TextDisplay() : theDisplay(10, vector<char>(10, ' ')) {
    // initial configuration
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
}

void TextDisplay::resetDisplay() {
    for (int row=0; row<=7; ++row) {
        for (int col=2; col<10; ++col) {
            if ((row%2==0 && col%2==0) || (row%2!=0 && col%2!=0)) {
                theDisplay[row][col]=' ';
            } else {
                theDisplay[row][col]='_';
            }
        }
    }
}

void TextDisplay::notify(const map<string, shared_ptr<Piece>>& board) {
    resetDisplay(); // make display empty
    for (const auto &block : board) {
        Piece *p = block.second.get();
        if (p == nullptr) {continue;}
        const string location = block.first;
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
        theDisplay[8-(location[1]-'0')][location[0]-'a'+2] = pieceChar;
    }
}

TextDisplay::~TextDisplay() {}

std::ostream &operator<<(std::ostream &out, const TextDisplay &td) {
    for (const auto &row : td.theDisplay) {
        for (char square : row) {
            out << square;
        }
        out << endl;
    }
    return out;
}
