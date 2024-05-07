#include "rook.h"

// Constructor
Rook::Rook(string colour, string position, string type): Piece{colour, position, type, 5} {}

// Destructor
Rook::~Rook() {}

vector<pair<string, string>> Rook::legalMoves(map<string, shared_ptr<Piece>>& board) {
   vector<pair<string,string>> moves;
   string pos = this->getPosition();
   char col=pos[0];
   char row=pos[1];
   string newpos;
   //up direction

   for (int i=1;row+i<='8';++i) {
    // newpos is a valid square on board
    newpos = string(1,col) + string(1,row+i);
    if (board[newpos]!=nullptr) {
        //a piece is already on this square
        if (board[newpos].get()->getColour()==this->getColour()) {
            //if that piece has the same colour
            break;
        } else {
            moves.emplace_back(make_pair(pos,newpos));
            break;
        }
    } else {
        // no piece occupies that square
        moves.emplace_back(make_pair(pos, newpos));
    }
   }
   //down direction
   for (int i=1;row-i>='1';++i) {
    // newpos is a valid square on board
    newpos = string(1,col) + string(1,row-i);

    if (board[newpos]!=nullptr) {
        //a piece is already on this square
        if (board[newpos].get()->getColour()==this->getColour()) {
            //if that piece has the same colour
            break;
        } else {
            moves.emplace_back(make_pair(pos,newpos));
            break;
        }
    } else {
        // no piece occupies that square
        moves.emplace_back(make_pair(pos, newpos));
    }
   }
   //left direction
   for (int i=1;col-i>='a';++i) {
    // newpos is a valid square on board
    newpos = string(1,col-i) + string(1,row);
    if (board[newpos]!=nullptr) {
        //a piece is already on this square
        if (board[newpos].get()->getColour()==this->getColour()) {
            //if that piece has the same colour
            break;
        } else {
            moves.emplace_back(make_pair(pos,newpos));
            break;
        }
    } else {
        // no piece occupies that square
        moves.emplace_back(make_pair(pos, newpos));
    }
   }
   //right direction
   for (int i=1;col+i<='h';++i) {
    // newpos is a valid square on board
    newpos = string(1,col+i) + string(1,row);
    if (board[newpos]!=nullptr) {
        //a piece is already on this square
        if (board[newpos].get()->getColour()==this->getColour()) {
            //if that piece has the same colour
            break;
        } else {
            moves.emplace_back(make_pair(pos,newpos));
            break;
        }
    } else {
        // no piece occupies that square
        moves.emplace_back(make_pair(pos, newpos));
    }
   }
   return moves;
}
