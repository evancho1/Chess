#include "knight.h"

// Constructor
Knight::Knight(string colour, string position, string type) : Piece{colour, position, type ,3} {}

// Destructor
Knight::~Knight() {}

vector<pair<string, string>> Knight::legalMoves(map<string, shared_ptr<Piece>>& board) {
    vector<pair<string, string>> moves;
    string position = getPosition();
    if (position[0] + 2 >= 'a' && position[0] + 2 <= 'h' && position[1] + 1 >= '1' && position[1] + 1 <= '8') {
        string temp = position;
        temp[0] += 2; // a-h
        temp[1] += 1; // 1-8
        if (board[temp] == nullptr || (board[temp] != nullptr && board[temp]->getColour() != getColour())) {
            moves.emplace_back(make_pair(getPosition(), temp));
        }
    }
    if (position[0] + 2 >= 'a' && position[0] + 2 <= 'h' && position[1] - 1 >= '1' && position[1] - 1 <= '8') {
        string temp = position;
        temp[0] += 2; // a-h
        temp[1] -= 1; // 1-8
        if (board[temp] == nullptr || (board[temp] != nullptr && board[temp]->getColour() != getColour())) {
            moves.emplace_back(make_pair(getPosition(), temp));
        }
    }
    if (position[0] + 1 >= 'a' && position[0] + 1 <= 'h' && position[1] + 2 >= '1' && position[1] + 2 <= '8') {
        string temp = position;
        temp[0] += 1; // a-h
        temp[1] += 2; // 1-8
        if (board[temp] == nullptr || (board[temp] != nullptr && board[temp]->getColour() != getColour())) {
            moves.emplace_back(make_pair(getPosition(), temp));
        }
    }
    if (position[0] + 1 >= 'a' && position[0] + 1 <= 'h' && position[1] - 2 >= '1' && position[1] - 2 <= '8') {
        string temp = position;
        temp[0] += 1; // a-h
        temp[1] -= 2; // 1-8
        if (board[temp] == nullptr || (board[temp] != nullptr && board[temp]->getColour() != getColour())) {
            moves.emplace_back(make_pair(getPosition(), temp));
        }
    }
    if (position[0] - 1 >= 'a' && position[0] - 1 <= 'h' && position[1] + 2 >= '1' && position[1] + 2 <= '8') {
        string temp = position;
        temp[0] -= 1; // a-h
        temp[1] += 2; // 1-8
        if (board[temp] == nullptr || (board[temp] != nullptr && board[temp]->getColour() != getColour())) {
            moves.emplace_back(make_pair(getPosition(), temp));
        }
    }
    if (position[0] - 1 >= 'a' && position[0] + 2 <= 'h' && position[1] - 2 >= '1' && position[1] - 2 <= '8') {
        string temp = position;
        temp[0] -= 1; // a-h
        temp[1] -= 2; // 1-8
        if (board[temp] == nullptr || (board[temp] != nullptr && board[temp]->getColour() != getColour())) {
            moves.emplace_back(make_pair(getPosition(), temp));
        }
    }
    if (position[0] - 2 >= 'a' && position[0] - 2 <= 'h' && position[1] + 1 >= '1' && position[1] + 1 <= '8') {
        string temp = position;
        temp[0] -= 2; // a-h
        temp[1] += 1; // 1-8
        if (board[temp] == nullptr || (board[temp] != nullptr && board[temp]->getColour() != getColour())) {
            moves.emplace_back(make_pair(getPosition(), temp));
        }
    }
    if (position[0] - 2 >= 'a' && position[0] - 2 <= 'h' && position[1] - 1 >= '1' && position[1] - 1 <= '8') {
        string temp = position;
        temp[0] -= 2; // a-h
        temp[1] -= 1; // 1-8
        if (board[temp] == nullptr || (board[temp] != nullptr && board[temp]->getColour() != getColour())) {
            moves.emplace_back(make_pair(getPosition(), temp));
        }
    }
    return moves;
}
