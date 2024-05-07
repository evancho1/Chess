#include "player.h"

Player::Player(string colour): colour{colour} {
    if (colour == "white") {
        pieces.emplace_back(make_shared<Pawn>(colour, "a2", "Pawn")); // 0
        pieces.emplace_back(make_shared<Pawn>(colour, "b2", "Pawn"));
        pieces.emplace_back(make_shared<Pawn>(colour, "c2", "Pawn"));
        pieces.emplace_back(make_shared<Pawn>(colour, "d2", "Pawn"));
        pieces.emplace_back(make_shared<Pawn>(colour, "e2", "Pawn"));
        pieces.emplace_back(make_shared<Pawn>(colour, "f2", "Pawn"));
        pieces.emplace_back(make_shared<Pawn>(colour, "g2", "Pawn"));
        pieces.emplace_back(make_shared<Pawn>(colour, "h2", "Pawn")); // 7
        pieces.emplace_back(make_shared<Rook>(colour, "a1", "Rook")); // 8
        pieces.emplace_back(make_shared<Rook>(colour, "h1", "Rook"));
        pieces.emplace_back(make_shared<Knight>(colour, "b1", "Knight")); // 10
        pieces.emplace_back(make_shared<Knight>(colour, "g1", "Knight"));
        pieces.emplace_back(make_shared<Bishop>(colour, "c1", "Bishop")); // 12
        pieces.emplace_back(make_shared<Bishop>(colour, "f1", "Bishop"));
        pieces.emplace_back(make_shared<Queen>(colour, "d1", "Queen")); // 14
        pieces.emplace_back(make_shared<King>(colour, "e1", "King")); // 15
    }
    if (colour == "black") {
        pieces.emplace_back(make_shared<Pawn>(colour, "a7", "Pawn")); // 0
        pieces.emplace_back(make_shared<Pawn>(colour, "b7", "Pawn"));
        pieces.emplace_back(make_shared<Pawn>(colour, "c7", "Pawn"));
        pieces.emplace_back(make_shared<Pawn>(colour, "d7", "Pawn"));
        pieces.emplace_back(make_shared<Pawn>(colour, "e7", "Pawn"));
        pieces.emplace_back(make_shared<Pawn>(colour, "f7", "Pawn"));
        pieces.emplace_back(make_shared<Pawn>(colour, "g7", "Pawn"));
        pieces.emplace_back(make_shared<Pawn>(colour, "h7", "Pawn"));
        pieces.emplace_back(make_shared<Rook>(colour, "a8", "Rook")); // 8
        pieces.emplace_back(make_shared<Rook>(colour, "h8", "Rook"));
        pieces.emplace_back(make_shared<Knight>(colour, "b8", "Knight")); // 10
        pieces.emplace_back(make_shared<Knight>(colour, "g8", "Knight"));
        pieces.emplace_back(make_shared<Bishop>(colour, "c8", "Bishop")); // 12
        pieces.emplace_back(make_shared<Bishop>(colour, "f8", "Bishop"));
        pieces.emplace_back(make_shared<Queen>(colour, "d8", "Queen")); // 14
        pieces.emplace_back(make_shared<King>(colour, "e8", "King")); // 15
    }
}

Player::~Player() {}

//accessors
bool Player::isComputer() const {
    if (playerType == Type::human) return false;
    return true;
}
Type Player::getType() const {
    return playerType;
} //check isComputer first
double Player::getScore() const {
    return score;
}
bool Player::getTurn() const {
    return turn;
}
string Player::getColour() const {
    return colour;
}
vector<shared_ptr<Piece>> Player::getPieces() const {
    return pieces;
}

//mutators
void Player::setTurn(bool newTurn) {
    turn = newTurn;
} //during setup
void Player::setType(string newType) {
    if (newType == "human") playerType = Type::human;
    if (newType == "computer1") playerType = Type::computerLevel1;
    if (newType == "computer2") playerType = Type::computerLevel2;
    if (newType == "computer3") playerType = Type::computerLevel3;
    if (newType == "computer4") playerType = Type::computerLevel4;
}
void Player::switchTurn() {
    turn = !turn;
}
void Player::incScore(double n) {
    score += n;
}
void Player::setColour(string colour) {
    this->colour = colour;
}
void Player::add(string piece, string pos) {
    if (piece == "R" || piece == "r") pieces.emplace_back(make_shared<Rook>(colour, pos, "Rook"));
    if (piece == "N" || piece == "n") pieces.emplace_back(make_shared<Knight>(colour, pos, "Knight"));
    if (piece == "B" || piece == "b") pieces.emplace_back(make_shared<Bishop>(colour, pos, "Bishop"));
    if (piece == "Q" || piece == "q") pieces.emplace_back(make_shared<Queen>(colour, pos, "Queen"));
    if (piece == "K" || piece == "k") pieces.emplace_back(make_shared<King>(colour, pos, "King"));
    if (piece == "P" || piece == "p") pieces.emplace_back(make_shared<Pawn>(colour, pos, "Pawn"));
} // append to vector
void Player::deletePiece(int index) {
    pieces.erase(pieces.begin() + index);
}

void Player::clear() {
    pieces.clear();
}
void Player::reset() {
    pieces.clear();
    if (colour == "white") {
        pieces.emplace_back(make_shared<Pawn>(colour, "a2", "Pawn")); // 0
        pieces.emplace_back(make_shared<Pawn>(colour, "b2", "Pawn"));
        pieces.emplace_back(make_shared<Pawn>(colour, "c2", "Pawn"));
        pieces.emplace_back(make_shared<Pawn>(colour, "d2", "Pawn"));
        pieces.emplace_back(make_shared<Pawn>(colour, "e2", "Pawn"));
        pieces.emplace_back(make_shared<Pawn>(colour, "f2", "Pawn"));
        pieces.emplace_back(make_shared<Pawn>(colour, "g2", "Pawn"));
        pieces.emplace_back(make_shared<Pawn>(colour, "h2", "Pawn")); // 7
        pieces.emplace_back(make_shared<Rook>(colour, "a1", "Rook")); // 8
        pieces.emplace_back(make_shared<Rook>(colour, "h1", "Rook"));
        pieces.emplace_back(make_shared<Knight>(colour, "b1", "Knight")); // 10
        pieces.emplace_back(make_shared<Knight>(colour, "g1", "Knight"));
        pieces.emplace_back(make_shared<Bishop>(colour, "c1", "Bishop")); // 12
        pieces.emplace_back(make_shared<Bishop>(colour, "f1", "Bishop"));
        pieces.emplace_back(make_shared<Queen>(colour, "d1", "Queen")); // 14
        pieces.emplace_back(make_shared<King>(colour, "e1", "King")); // 15
    }
    if (colour == "black") {
        pieces.emplace_back(make_shared<Pawn>(colour, "a7", "Pawn")); // 0
        pieces.emplace_back(make_shared<Pawn>(colour, "b7", "Pawn"));
        pieces.emplace_back(make_shared<Pawn>(colour, "c7", "Pawn"));
        pieces.emplace_back(make_shared<Pawn>(colour, "d7", "Pawn"));
        pieces.emplace_back(make_shared<Pawn>(colour, "e7", "Pawn"));
        pieces.emplace_back(make_shared<Pawn>(colour, "f7", "Pawn"));
        pieces.emplace_back(make_shared<Pawn>(colour, "g7", "Pawn"));
        pieces.emplace_back(make_shared<Pawn>(colour, "h7", "Pawn"));
        pieces.emplace_back(make_shared<Rook>(colour, "a8", "Rook")); // 8
        pieces.emplace_back(make_shared<Rook>(colour, "h8", "Rook"));
        pieces.emplace_back(make_shared<Knight>(colour, "b8", "Knight")); // 10
        pieces.emplace_back(make_shared<Knight>(colour, "g8", "Knight"));
        pieces.emplace_back(make_shared<Bishop>(colour, "c8", "Bishop")); // 12
        pieces.emplace_back(make_shared<Bishop>(colour, "f8", "Bishop"));
        pieces.emplace_back(make_shared<Queen>(colour, "d8", "Queen")); // 14
        pieces.emplace_back(make_shared<King>(colour, "e8", "King")); // 15
    }
}
