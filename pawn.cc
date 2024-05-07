#include "pawn.h"

// Constructor
Pawn::Pawn(string colour, string position, string type): Piece{colour, position, type, 1} {}

// Destructor
Pawn::~Pawn() {}


vector<pair<string, string>> Pawn::legalMoves(map<string, shared_ptr<Piece>>& board) {
    vector<pair<string, string>> moves;
    string position = getPosition();
    string temp = position;
    string temp2 = position;
    string temp3 = position;

    if (getColour() == "white") {
        if (!getHasMoved()) {
            temp[0] = position[0];
            temp[1] = position[1] + 2;
            temp2[0] = position[0];
            temp2[1] = position[1] + 1;
            if (temp[0] >= 'a' && temp[0] <= 'h' && temp[1] >= '1' && temp[1] <= '8'
                && board[temp2] == nullptr
                && (board[temp] == nullptr)) {
                moves.emplace_back(make_pair(position, temp));
            }
        } // double step

        temp[0] = position[0];
        temp[1] = position[1] + 1;
        if (temp[0] >= 'a' && temp[0] <= 'h' && temp[1] >= '1' && temp[1] <= '8'
            && (board[temp] == nullptr)) {
            moves.emplace_back(make_pair(position, temp));
        } // regular move forward

        temp[0] = position[0] - 1;
        temp[1] = position[1] + 1;
        if (temp[0] >= 'a' && temp[0] <= 'h' && temp[1] >= '1' && temp[1] <= '8'
            && (board[temp] != nullptr) && board[temp]->getColour() != getColour()) {
            moves.emplace_back(make_pair(position, temp));
        } // capture forward and left

        temp[0] = position[0] + 1;
        temp[1] = position[1] + 1;
        if (temp[0] >= 'a' && temp[0] <= 'h' && temp[1] >= '1' && temp[1] <= '8'
            && (board[temp] != nullptr) && board[temp]->getColour() != getColour()) {
            moves.emplace_back(make_pair(position, temp));
        } // capture forward and right

        temp[0] = position[0] - 1;
        temp[1] = position[1] + 1;
        temp2[0] = position[0] - 1;
        temp2[1] = position[1];

        if (temp[0] >= 'a' && temp[0] <= 'h' && temp[1] >= '1' && temp[1] <= '8'
            && (board[temp] == nullptr)
            && (board[temp2] != nullptr)
            && (board[temp2]->getColour() != getColour())
            && (board[temp2]->isDoubleStepped())) {
            moves.emplace_back(make_pair(position, temp));
        } // en passant forward and left

        temp[0] = position[0] + 1;
        temp[1] = position[1] + 1;
        temp2[0] = position[0] + 1;
        temp2[1] = position[1];
        if (temp[0] >= 'a' && temp[0] <= 'h' && temp[1] >= '1' && temp[1] <= '8'
            && (board[temp] == nullptr)
            && board[temp2] != nullptr
            && board[temp2]->getColour() != getColour()
            && board[temp2]->isDoubleStepped()) {
            moves.emplace_back(make_pair(position, temp));
        } // en passant forward and right
    }

    if (getColour() == "black") {
        if (!getHasMoved()) {
            temp[0] = position[0];
            temp[1] = position[1] - 2;
            temp2[0] = position[0];
            temp2[1] = position[1] - 1;
            if (temp[0] >= 'a' && temp[0] <= 'h' && temp[1] >= '1' && temp[1] <= '8'
                && board[temp2] == nullptr
                && (board[temp] == nullptr)) {
                moves.emplace_back(make_pair(position, temp));
            }
        } // double step
        temp[0] = position[0];
        temp[1] = position[1] - 1;
        if (temp[0] >= 'a' && temp[0] <= 'h' && temp[1] >= '1' && temp[1] <= '8'
            && (board[temp] == nullptr)) {
            moves.emplace_back(make_pair(position, temp));
        } // regular move forward

        temp[0] = position[0] - 1;
        temp[1] = position[1] - 1;
        if (temp[0] >= 'a' && temp[0] <= 'h' && temp[1] >= '1' && temp[1] <= '8'
            && (board[temp] != nullptr) && board[temp]->getColour() != getColour()) {
            moves.emplace_back(make_pair(position, temp));
        } // capture forward and left
        temp[0] = position[0] + 1;
        temp[1] = position[1] - 1;
        if (temp[0] >= 'a' && temp[0] <= 'h' && temp[1] >= '1' && temp[1] <= '8'
            && (board[temp] != nullptr) && board[temp]->getColour() != getColour()) {
            moves.emplace_back(make_pair(position, temp));
        } // capture forward and right
        temp[0] = position[0] - 1;
        temp[1] = position[1] - 1;
        temp2[0] = position[0] - 1;
        temp2[1] = position[1];
        if (temp[0] >= 'a' && temp[0] <= 'h' && temp[1] >= '1' && temp[1] <= '8'
            && (board[temp] == nullptr)
            && board[temp2] != nullptr
            && board[temp2]->getColour() != getColour()
            && board[temp2]->isDoubleStepped()) {
            moves.emplace_back(make_pair(position, temp));
        } // en passant forward and left
        temp[0] = position[0] + 1;
        temp[1] = position[1] - 1;
        temp2[0] = position[0] + 1;
        temp2[1] = position[1];
        if (temp[0] >= 'a' && temp[0] <= 'h' && temp[1] >= '1' && temp[1] <= '8'
            && (board[temp] == nullptr)
            && board[temp2] != nullptr
            && board[temp2]->getColour() != getColour()
            && board[temp2]->isDoubleStepped()) {
            moves.emplace_back(make_pair(position, temp));
        } // en passant forward and right
    }
    return moves;
}
