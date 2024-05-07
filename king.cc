#include "king.h"

// Constructor
King::King(string colour, string position, string type): Piece{colour, position, type,0} {}

// Destructor
King::~King() {}

bool King::noKingNearby(string pos, map<string, shared_ptr<Piece>>& board) {
    string temp = pos;

    temp[0] = pos[0] - 1;
    temp[1] = pos[1] - 1;
    if (temp[0] >= 'a' && temp[0] <= 'h' && temp[1] >= '1' && temp[1] <= '8') {
        if (board[temp] != nullptr && board[temp]->getColour() != getColour()
            && board[temp]->getType() == "King") return false;
    }

    temp[0] = pos[0] - 1;
    temp[1] = pos[1];
    if (temp[0] >= 'a' && temp[0] <= 'h' && temp[1] >= '1' && temp[1] <= '8') {
        if (board[temp] != nullptr && board[temp]->getColour() != getColour()
            && board[temp]->getType() == "King") return false;
    }

    temp[0] = pos[0] - 1;
    temp[1] = pos[1] + 1;
    if (temp[0] >= 'a' && temp[0] <= 'h' && temp[1] >= '1' && temp[1] <= '8') {
        if (board[temp] != nullptr && board[temp]->getColour() != getColour()
            && board[temp]->getType() == "King") return false;
    }

    temp[0] = pos[0];
    temp[1] = pos[1] + 1;
    if (temp[0] >= 'a' && temp[0] <= 'h' && temp[1] >= '1' && temp[1] <= '8') {
        if (board[temp] != nullptr && board[temp]->getColour() != getColour()
            && board[temp]->getType() == "King") return false;
    }

    temp[0] = pos[0] + 1;
    temp[1] = pos[1] + 1;
    if (temp[0] >= 'a' && temp[0] <= 'h' && temp[1] >= '1' && temp[1] <= '8') {
        if (board[temp] != nullptr && board[temp]->getColour() != getColour()
            && board[temp]->getType() == "King") return false;
    }

    temp[0] = pos[0] + 1;
    temp[1] = pos[1];
    if (temp[0] >= 'a' && temp[0] <= 'h' && temp[1] >= '1' && temp[1] <= '8') {
        if (board[temp] != nullptr && board[temp]->getColour() != getColour()
            && board[temp]->getType() == "King") return false;
    }

    temp[0] = pos[0] + 1;
    temp[1] = pos[1] - 1;
    if (temp[0] >= 'a' && temp[0] <= 'h' && temp[1] >= '1' && temp[1] <= '8') {
        if (board[temp] != nullptr && board[temp]->getColour() != getColour()
            && board[temp]->getType() == "King") return false;
    }

    temp[0] = pos[0];
    temp[1] = pos[1] - 1;
    if (temp[0] >= 'a' && temp[0] <= 'h' && temp[1] >= '1' && temp[1] <= '8') {
        if (board[temp] != nullptr && board[temp]->getColour() != getColour()
            && board[temp]->getType() == "King") return false;
    }

    return true;
}

vector<pair<string, string>> King::legalMoves(map<string, shared_ptr<Piece>>& board) {
    vector<pair<string, string>> moves;
    string position = getPosition();
    string temp = position;
    string temp2 = position;
    string temp3 = position;
    string temp4 = position;

    temp[0] = position[0] - 1;
    temp[1] = position[1] - 1;
    if (temp[0] >= 'a' && temp[0] <= 'h' && temp[1] >= '1' && temp[1] <= '8') {
        if (board[temp] == nullptr || (board[temp] != nullptr && board[temp]->getColour() != getColour())) {
            if (noKingNearby(temp, board)) moves.emplace_back(make_pair(getPosition(), temp));
        }
    }

    temp[0] = position[0];
    temp[1] = position[1] - 1;
    if (temp[0] >= 'a' && temp[0] <= 'h' && temp[1] >= '1' && temp[1] <= '8') {
        if (board[temp] == nullptr || ((board[temp] != nullptr && board[temp]->getColour() != getColour()))) {
            if (noKingNearby(temp, board)) moves.emplace_back(make_pair(getPosition(), temp));
        }
    }

    temp[0] = position[0] + 1;
    temp[1] = position[1] - 1;
    if (temp[0] >= 'a' && temp[0] <= 'h' && temp[1] >= '1' && temp[1] <= '8') {
        if (board[temp] == nullptr || (board[temp] != nullptr && board[temp]->getColour() != getColour())) {
            if (noKingNearby(temp, board)) moves.emplace_back(make_pair(getPosition(), temp));
        }
    }

    temp[0] = position[0] + 1;
    temp[1] = position[1];
    if (temp[0] >= 'a' && temp[0] <= 'h' && temp[1] >= '1' && temp[1] <= '8') {
        if (board[temp] == nullptr || (board[temp] != nullptr && board[temp]->getColour() != getColour())) {
            if (noKingNearby(temp, board)) moves.emplace_back(make_pair(getPosition(), temp));
        }
    }

    temp[0] = position[0] + 1;
    temp[1] = position[1] + 1;
    if (temp[0] >= 'a' && temp[0] <= 'h' && temp[1] >= '1' && temp[1] <= '8') {
        if (board[temp] == nullptr || (board[temp] != nullptr && board[temp]->getColour() != getColour())) {
            if (noKingNearby(temp, board)) moves.emplace_back(make_pair(getPosition(), temp));
        }
    }

    temp[0] = position[0];
    temp[1] = position[1] + 1;
    if (temp[0] >= 'a' && temp[0] <= 'h' && temp[1] >= '1' && temp[1] <= '8') {
        if (board[temp] == nullptr || (board[temp] != nullptr && board[temp]->getColour() != getColour())) {
            if (noKingNearby(temp, board)) moves.emplace_back(make_pair(getPosition(), temp));
        }
    }

    temp[0] = position[0] - 1;
    temp[1] = position[1] + 1;
    if (temp[0] >= 'a' && temp[0] <= 'h' && temp[1] >= '1' && temp[1] <= '8') {
        if (board[temp] == nullptr || (board[temp] != nullptr && board[temp]->getColour() != getColour())) {
            if (noKingNearby(temp, board)) moves.emplace_back(make_pair(getPosition(), temp));
        }
    }

    temp[0] = position[0] - 1;
    temp[1] = position[1];
    if (temp[0] >= 'a' && temp[0] <= 'h' && temp[1] >= '1' && temp[1] <= '8') {
        if (board[temp] == nullptr || (board[temp] != nullptr && board[temp]->getColour() != getColour())) {
            if (noKingNearby(temp, board)) moves.emplace_back(make_pair(getPosition(), temp));
        }
    }

    // castling

    if (!getHasMoved()) {
        temp[0] = position[0] + 3;
        temp[1] = position[1];
        temp2[0] = position[0] + 1;
        temp3[0] = position[0] + 2;
        if (board[temp] != nullptr && board[temp]->getType() == "Rook" && !board[temp]->getHasMoved()
            && board[temp2] == nullptr
            && board[temp3] == nullptr) {
            moves.emplace_back(make_pair(getPosition(), temp3));
        } // king side castling

        temp[0] = position[0] - 4;
        temp[1] = position[1];
        temp2[0] = position[0] - 1;
        temp3[0] = position[0] - 2;
        temp4[0] = position[0] - 3;
        if (board[temp] != nullptr && board[temp]->getType() == "Rook" && !board[temp]->getHasMoved()
            && board[temp2] == nullptr
            && board[temp3] == nullptr
            && board[temp4] == nullptr) {
            moves.emplace_back(make_pair(getPosition(), temp3));
        } // queen side castling
    }
    return moves;
}
