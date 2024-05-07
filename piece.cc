#include "piece.h"

// Constructor
Piece::Piece(string colour, string position, string type, int point): colour{colour}, position{position},
    type{type}, hasMoved{false}, justDoubleStepped{false}, point{point} {}

//copy constructor
Piece::Piece(const Piece& other)
: colour{other.colour}, position{other.position}, type{other.type}, 
hasMoved{other.hasMoved}, justDoubleStepped{other.justDoubleStepped}, point{other.point} {}

const int Piece::getPoint() const {
    return point;
}

string Piece::getColour() const {
    return colour;
}

string Piece::getPosition() const {
    return position;
}

string Piece::getType() const {
    return type;
}

bool Piece::getHasMoved() const {
    return hasMoved;
}

bool Piece::isDoubleStepped() const {
    return justDoubleStepped;
}

void Piece::setColour(string colour) {
    this->colour = colour;
}

void Piece::setPosition(string position) {
    this->position = position;
}

void Piece::setType(string type) {
    this->type = type;
}

void Piece::setHasMoved(bool hasMoved) {
    this->hasMoved = hasMoved;
}

void Piece::setDoubleStepped(bool justDoubleStepped) {
    this->justDoubleStepped = justDoubleStepped;
}
