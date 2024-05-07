#include "model.h"

Model::Model(Xwindow& xw): whitePlayer(Player{"white"}), blackPlayer(Player{"black"}),
                inGame{false}, td{make_unique<TextDisplay>()} {
    gd = make_unique<GraphicsDisplay>(xw);
    // other white pieces
    board["a1"] = whitePlayer.getPieces()[8];
    board["b1"] = whitePlayer.getPieces()[10];
    board["c1"] = whitePlayer.getPieces()[12];
    board["d1"] = whitePlayer.getPieces()[14];
    board["e1"] = whitePlayer.getPieces()[15];
    board["f1"] = whitePlayer.getPieces()[13];
    board["g1"] = whitePlayer.getPieces()[11];
    board["h1"] = whitePlayer.getPieces()[9];
    // white pawns
    board["a2"] = whitePlayer.getPieces()[0];
    board["b2"] = whitePlayer.getPieces()[1];
    board["c2"] = whitePlayer.getPieces()[2];
    board["d2"] = whitePlayer.getPieces()[3];
    board["e2"] = whitePlayer.getPieces()[4];
    board["f2"] = whitePlayer.getPieces()[5];
    board["g2"] = whitePlayer.getPieces()[6];
    board["h2"] = whitePlayer.getPieces()[7];

    board["a3"] = nullptr;
    board["b3"] = nullptr;
    board["c3"] = nullptr;
    board["d3"] = nullptr;
    board["e3"] = nullptr;
    board["f3"] = nullptr;
    board["g3"] = nullptr;
    board["h3"] = nullptr;

    board["a4"] = nullptr;
    board["b4"] = nullptr;
    board["c4"] = nullptr;
    board["d4"] = nullptr;
    board["e4"] = nullptr;
    board["f4"] = nullptr;
    board["g4"] = nullptr;
    board["h4"] = nullptr;

    board["a5"] = nullptr;
    board["b5"] = nullptr;
    board["c5"] = nullptr;
    board["d5"] = nullptr;
    board["e5"] = nullptr;
    board["f5"] = nullptr;
    board["g5"] = nullptr;
    board["h5"] = nullptr;

    board["a6"] = nullptr;
    board["b6"] = nullptr;
    board["c6"] = nullptr;
    board["d6"] = nullptr;
    board["e6"] = nullptr;
    board["f6"] = nullptr;
    board["g6"] = nullptr;
    board["h6"] = nullptr;

    // black pawns
    board["a7"] = blackPlayer.getPieces()[0];
    board["b7"] = blackPlayer.getPieces()[1];
    board["c7"] = blackPlayer.getPieces()[2];
    board["d7"] = blackPlayer.getPieces()[3];
    board["e7"] = blackPlayer.getPieces()[4];
    board["f7"] = blackPlayer.getPieces()[5];
    board["g7"] = blackPlayer.getPieces()[6];
    board["h7"] = blackPlayer.getPieces()[7];

    // other black getPieces()
    board["a8"] = blackPlayer.getPieces()[8];
    board["b8"] = blackPlayer.getPieces()[10];
    board["c8"] = blackPlayer.getPieces()[12];
    board["d8"] = blackPlayer.getPieces()[14];
    board["e8"] = blackPlayer.getPieces()[15];
    board["f8"] = blackPlayer.getPieces()[13];
    board["g8"] = blackPlayer.getPieces()[11];
    board["h8"] = blackPlayer.getPieces()[9];

    setWhiteTurn(true);
    setBlackTurn(false);
}

void Model::setFlags(const string& pos1, const string& pos2) {
    for (const auto&p: board) {
        if (p.second != nullptr) p.second->setDoubleStepped(false);
    }
    if (board[pos2]->getType() == "Pawn" && abs(pos1[1] - pos2[1]) == 2) {
        board[pos2]->setDoubleStepped(true);
        board[pos2]->setHasMoved(true);
    }
    notifyObservers();
}
void Model::moveHelper(const string& pos1, const string& pos2) {
    removePiece(pos2);
    board[pos2] = board[pos1];
    board[pos1] = nullptr;
    board[pos2]->setPosition(pos2);
    if (board[pos2]->getType() == "Pawn" && pos2[1] == '8') {
        addPiece("Q", pos2);
    }
    else if (board[pos2]->getType() == "Pawn" && pos2[1] == '1') {
        addPiece("q", pos2);
    }
}

//accessors
vector<pair<string, string>> Model::allLegalMoves(const string& colour) {
    vector<pair<string, string>> temp = {};
    vector<pair<string, string>> moves;
    if (colour == "white") {
        for (const auto &p: whitePlayer.getPieces()) {
            moves = p->legalMoves(board);
            temp.insert(temp.end(), moves.begin(), moves.end());
        }
        for (auto it = temp.begin(); it != temp.end(); ) {
            if (simulateMove((*it).first, (*it).second, "white")) temp.erase(it);
            else ++it;
        }
    }
    if (colour == "black") {
        for (const auto &p: blackPlayer.getPieces()) {
            moves = p->legalMoves(board);
            temp.insert(temp.end(), moves.begin(), moves.end());
        }
        for (auto it = temp.begin(); it != temp.end(); ) {
            if (simulateMove((*it).first, (*it).second, "black")) temp.erase(it);
            else ++it;
        }
    }
    return temp;
} // call legalMoves() on all pieces

double Model::getScore(string colour) {
    if (colour == "white") return whitePlayer.getScore();
    else return blackPlayer.getScore();
}

void Model::beginSetup() {
    for (const auto& p: board) board[p.first] = nullptr;
    whitePlayer.clear();
    blackPlayer.clear();
    notifyObservers();
}
// the model setup
void Model::game(const string& whiteType, const string& blackType) {
    whitePlayer.setType(whiteType);
    blackPlayer.setType(blackType);
    inGame = true;
}
void Model::addPiece(const string& piece, const string& pos) {
    removePiece(pos);
    if (piece == "R" || piece == "N" || piece == "B" || piece == "Q" || piece == "K" || piece == "P") {
        whitePlayer.add(piece, pos);
        board[pos] = whitePlayer.getPieces()[whitePlayer.getPieces().size() - 1];
        notifyObservers();
    }
    if (piece == "r" || piece == "n" || piece == "b" || piece == "q" || piece == "k" || piece == "p") {
        blackPlayer.add(piece, pos);
        board[pos] = blackPlayer.getPieces()[blackPlayer.getPieces().size() - 1];
        notifyObservers();
    }

} //to be called within setup()
void Model::removePiece(const string& pos) {
    int index = 0;
    for (const auto& p:whitePlayer.getPieces()) {
        if (board[pos] == p) {
            whitePlayer.deletePiece(index);
            board[pos] = nullptr;
            notifyObservers();
            return;
        }
        ++index;
    }
    index = 0;
    for (const auto& p:blackPlayer.getPieces()) {
        if (board[pos] == p) {
            blackPlayer.deletePiece(index);
            board[pos] = nullptr;
            notifyObservers();
            return;
        }
        ++index;
    }
} // to be called within setup()

void Model::setWhiteTurn(bool turn) {
    whitePlayer.setTurn(turn);
}
void Model::setBlackTurn(bool turn) {
    blackPlayer.setTurn(turn);
}
void Model::reset() {
    whitePlayer.reset();
    blackPlayer.reset();
    // other white pieces
    board["a1"] = whitePlayer.getPieces()[8];
    board["b1"] = whitePlayer.getPieces()[10];
    board["c1"] = whitePlayer.getPieces()[12];
    board["d1"] = whitePlayer.getPieces()[14];
    board["e1"] = whitePlayer.getPieces()[15];
    board["f1"] = whitePlayer.getPieces()[13];
    board["g1"] = whitePlayer.getPieces()[11];
    board["h1"] = whitePlayer.getPieces()[9];
    // white pawns
    board["a2"] = whitePlayer.getPieces()[0];
    board["b2"] = whitePlayer.getPieces()[1];
    board["c2"] = whitePlayer.getPieces()[2];
    board["d2"] = whitePlayer.getPieces()[3];
    board["e2"] = whitePlayer.getPieces()[4];
    board["f2"] = whitePlayer.getPieces()[5];
    board["g2"] = whitePlayer.getPieces()[6];
    board["h2"] = whitePlayer.getPieces()[7];

    board["a3"] = nullptr;
    board["b3"] = nullptr;
    board["c3"] = nullptr;
    board["d3"] = nullptr;
    board["e3"] = nullptr;
    board["f3"] = nullptr;
    board["g3"] = nullptr;
    board["h3"] = nullptr;

    board["a4"] = nullptr;
    board["b4"] = nullptr;
    board["c4"] = nullptr;
    board["d4"] = nullptr;
    board["e4"] = nullptr;
    board["f4"] = nullptr;
    board["g4"] = nullptr;
    board["h4"] = nullptr;

    board["a5"] = nullptr;
    board["b5"] = nullptr;
    board["c5"] = nullptr;
    board["d5"] = nullptr;
    board["e5"] = nullptr;
    board["f5"] = nullptr;
    board["g5"] = nullptr;
    board["h5"] = nullptr;

    board["a6"] = nullptr;
    board["b6"] = nullptr;
    board["c6"] = nullptr;
    board["d6"] = nullptr;
    board["e6"] = nullptr;
    board["f6"] = nullptr;
    board["g6"] = nullptr;
    board["h6"] = nullptr;

    // black pawns
    board["a7"] = blackPlayer.getPieces()[0];
    board["b7"] = blackPlayer.getPieces()[1];
    board["c7"] = blackPlayer.getPieces()[2];
    board["d7"] = blackPlayer.getPieces()[3];
    board["e7"] = blackPlayer.getPieces()[4];
    board["f7"] = blackPlayer.getPieces()[5];
    board["g7"] = blackPlayer.getPieces()[6];
    board["h7"] = blackPlayer.getPieces()[7];

    // other black getPieces()
    board["a8"] = blackPlayer.getPieces()[8];
    board["b8"] = blackPlayer.getPieces()[10];
    board["c8"] = blackPlayer.getPieces()[12];
    board["d8"] = blackPlayer.getPieces()[14];
    board["e8"] = blackPlayer.getPieces()[15];
    board["f8"] = blackPlayer.getPieces()[13];
    board["g8"] = blackPlayer.getPieces()[11];
    board["h8"] = blackPlayer.getPieces()[9];
    setWhiteTurn(true);
    setBlackTurn(false);
    notifyObservers();
}

// game logic functionalities
bool Model::isInCheck(const string& colour) {
    vector<pair<string, string>> temp = {};
    vector<pair<string, string>> moves;
    if (colour == "white") {
        for (const auto &p: blackPlayer.getPieces()) {
            if (p->getPosition() == "simulate") continue;
            temp = p->legalMoves(board);
            moves.insert(moves.end(), temp.begin(), temp.end());
        }
        for (auto &m: moves) {
            if (board[m.second] != nullptr && board[m.second]->getType() == "King") return true;
        }
    } else {
        for (const auto &p: whitePlayer.getPieces()) {
            if (p->getPosition() == "simulate") continue;
            temp = p->legalMoves(board);
            moves.insert(moves.end(), temp.begin(), temp.end());
        }
        for (auto &m: moves) {
            if (board[m.second] != nullptr && board[m.second]->getType() == "King") return true;
        }
    }
    return false;
}
bool Model::isCheckmated(const string& colour) {
    if (isInCheck(colour)) {
        if (allLegalMoves(colour).empty()) {
            endgame();
            return true;
        }
    }
    return false;
}
bool Model::isStalemate() {
    if (!isInCheck("white") && !isInCheck("black")) {
        if (allLegalMoves("white").empty() || allLegalMoves("black").empty()) {
            whitePlayer.incScore(0.5);
            blackPlayer.incScore(0.5);
            inGame = false;
            reset();
            return true;
        }
    }
    return false;
}
bool Model::isInGame() const {
    return inGame;
}

bool Model::simulateMove(string pos1, string pos2, const string& colour) {
    //make a deep copy (snapshot) of current board
    board["simulate"] = board[pos2];
    string posTemp;
    if (board["simulate"] != nullptr) {
        posTemp = board["simulate"]->getPosition();
        board["simulate"]->setPosition("simulate");
    }
    board[pos2] = board[pos1];
    board[pos1] = nullptr;
    bool isCheck = isInCheck(colour);
    //restore original board
    board[pos1] = board[pos2];
    board[pos2] = board["simulate"];
    if (board[pos2] != nullptr) board[pos2]->setPosition(pos2);
    board["simulate"] = nullptr;
    return isCheck;
}

bool Model::validSetup() {
    int whiteKing = 0;
    int blackKing = 0;
    for (auto &p: board) {
        if (p.second == nullptr) continue;
        if (p.second->getType() == "King") {
            if (p.second->getColour() == "white") ++whiteKing;
            else ++blackKing;
        }
        // checks if there is a pawn on row 1 or 8
        if (p.second->getPosition()[1] == '1' || p.second->getPosition()[1] == '8') {
            if (p.second->getType() == "Pawn") return false;
        }
    }
    // returns whether there is exactly 1 white and black king and that neither king is in check
    return (whiteKing == 1 && blackKing == 1 && !isInCheck("white") && !isInCheck("black"));
}

void Model::endSetup() {
    for (auto& p: board) {
        if (p.second == nullptr) continue;
        if (p.second->getType() == "Pawn" || p.second->getType() == "King" || p.second->getType() == "Rook") {
            p.second->setHasMoved(true);
        }
    }
}

bool Model::move() {
    if (whitePlayer.getTurn()) {
        if (whitePlayer.getType() == Type::computerLevel1) {
            string pos1 = allLegalMoves("white")[0].first;
            string pos2 = allLegalMoves("white")[0].second;
            moveHelper(pos1, pos2);
            setFlags(pos1, pos2);
            setWhiteTurn(false);
            setBlackTurn(true);
            notifyObservers();
            return true;
        }
        else if (whitePlayer.getType() == Type::computerLevel2) {
            vector<pair<string,string>> alm = allLegalMoves("white");
            bool successMove = false;
            for (pair<string,string>& move : alm) {
                string pos1=move.first;
                string pos2=move.second;
                //check if it is a capturing move
                if (board[pos2]!=nullptr) {
                    // since same colour piece should not be in legalmoves, this is opponent
                    moveHelper(pos1,pos2);
                    setFlags(pos1, pos2);
                    successMove= true;
                    break;
                } else {
                    // check if it is check move
                    bool checkMove = simulateMove(pos1,pos2,"black");
                    if (checkMove) {
                        moveHelper(pos1,pos2);
                        setFlags(pos1, pos2);
                        successMove=true;
                        break;
                    }
                }
            }
            if (!successMove) {
                string pos1 = alm[0].first;
                string pos2 = alm[0].second;
                moveHelper(pos1, pos2);
                setFlags(pos1,pos2);
            }
            setWhiteTurn(false);
            setBlackTurn(true);
            notifyObservers();
            return true;
        } else if (whitePlayer.getType() == Type::computerLevel3) {
            vector<pair<string,string>> almw = allLegalMoves("white");
            vector<pair<string,string>> almb = allLegalMoves("black");
            bool successMove = false;
            vector<string> needHelpPos; //store the threatened pieces
            for (pair<string,string>& move : almb) {
                //find a threatened white piece
                string pos2=move.second;
                if (board[pos2]!=nullptr) {
                    //since it is in black's legalmoves, it must be a white piece
                    needHelpPos.emplace_back(pos2);
                }
            }
            if (!needHelpPos.empty()) {
                //if there is need to avoid capture
                for (pair<string,string>& move : almw) {
                    string pos1=move.first;
                    string pos2=move.second;
                    for (const string& pos : needHelpPos) {
                        if (pos==pos1) {
                            bool underThreat = false;
                            //check if current move can escape the capture
                            for (pair<string,string>& oppmove : almb) {
                                if (pos2==oppmove.second) {
                                    //still capturable
                                    underThreat = true;
                                    break;
                                }
                            }
                            if (!underThreat) {
                                // if current move can avoid capture
                                moveHelper(pos1,pos2);
                                setFlags(pos1,pos2);
                                successMove=true;
                            }
                            break;
                        }
                    }
                    if (successMove) {
                        break;
                    }
                }
            }
            if (!successMove) {
                //if cannot avoid any capture or no capture to avoid
                for (pair<string,string>& move : almw) {
                    string pos1=move.first;
                    string pos2=move.second;
                    //check if it is a capturing move
                    if (board[pos2]!=nullptr) {
                        // since same colour piece should not be in legalmoves, this is opponent
                        moveHelper(pos1,pos2);
                        setFlags(pos1, pos2);
                        successMove= true;
                        break;
                    } else {
                        // check if it is check move
                        bool checkMove = simulateMove(pos1,pos2,"black");
                        if (checkMove) {
                            moveHelper(pos1,pos2);
                            setFlags(pos1, pos2);
                            successMove=true;
                            break;
                        }
                    }
                }
            }
            if (!successMove) {
                string pos1 = almw[0].first;
                string pos2 = almw[0].second;
                moveHelper(pos1, pos2);
                setFlags(pos1,pos2);
            }
            setWhiteTurn(false);
            setBlackTurn(true);
            notifyObservers();
            return true;
        }
        else if (whitePlayer.getType() == Type::computerLevel4) {
            vector<pair<string,string>> almw = allLegalMoves("white");
            vector<pair<string,string>> almb = allLegalMoves("black");
            bool successMove = false;
            vector<string> needHelpPos; //store the threatened pieces
            // check for captures
            int topPoint = 0;
            pair<string, string> topPointMove;
            for (pair<string,string>& move : almw) {
                string pos1=move.first;
                string pos2=move.second;
                if (board[pos2] != nullptr && board[pos2].get()->getPoint()>topPoint) {
                    //if move captures opponent and is better than the current capture
                    topPoint = board[pos2].get()->getPoint();
                    topPointMove.second = pos2;
                    topPointMove.first = pos1;
                    successMove = true;
                }
            }
            if (successMove) {
                // capture the highest point
                moveHelper(topPointMove.first,topPointMove.second);
                setFlags(topPointMove.first,topPointMove.second);
            } else {
                //attempt avoiding capture
                for (pair<string,string>& move : almb) {
                    //find a threatened white piece
                    string pos2=move.second;
                    if (board[pos2]!=nullptr) {
                        //since it is in black's legalmoves, it must be a white piece
                        needHelpPos.emplace_back(pos2);
                    }
                }
                if (!needHelpPos.empty()) {
                    //if there is need to avoid capture
                    for (pair<string,string>& move : almw) {
                        string pos1=move.first;
                        string pos2=move.second;
                        for (const string& pos : needHelpPos) {
                            if (pos==pos1) {
                                bool underThreat = false;
                                //check if current move can escape the capture
                                for (pair<string,string>& oppmove : almb) {
                                    if (pos2==oppmove.second) {
                                        //still capturable
                                        underThreat = true;
                                        break;
                                    }
                                }
                                if (!underThreat) {
                                    // if current move can avoid capture
                                    moveHelper(pos1,pos2);
                                    setFlags(pos1,pos2);
                                    successMove=true;
                                }
                                break;
                            }
                        }
                        if (successMove) {
                            break;
                        }
                    }
                }
            }
            if (!successMove) {
                // try check move
                for (pair<string,string>& move : almw) {
                    string pos1=move.first;
                    string pos2=move.second;
                    bool checkMove = simulateMove(pos1,pos2,"black");
                    if (checkMove) {
                        moveHelper(pos1,pos2);
                        setFlags(pos1, pos2);
                        successMove=true;
                        break;
                    }
                }
            }
            if (!successMove) {
                string pos1 = almw[0].first;
                string pos2 = almw[0].second;
                moveHelper(pos1, pos2);
                setFlags(pos1,pos2);
            }
            setWhiteTurn(false);
            setBlackTurn(true);
            notifyObservers();
            return true;
        }
    } else {
        if (blackPlayer.getType() == Type::computerLevel1) {
            string pos1 = allLegalMoves("black")[0].first;
            string pos2 = allLegalMoves("black")[0].second;
            moveHelper(pos1, pos2);
            setFlags(pos1, pos2);
            setWhiteTurn(true);
            setBlackTurn(false);
            notifyObservers();
            return true;
        } else if (blackPlayer.getType() == Type::computerLevel2) {
            vector<pair<string,string>> alm = allLegalMoves("black");
            bool successMove = false;
            for (pair<string,string>& move : alm) {
                string pos1=move.first;
                string pos2=move.second;
                //check if it is a capturing move
                if (board[pos2]!=nullptr) {
                    // since same colour piece should not be in legalmoves, this is opponent
                    moveHelper(pos1,pos2);
                    setFlags(pos1, pos2);
                    successMove= true;
                    break;
                } else {
                    // check if it is check move
                    bool checkMove = simulateMove(pos1,pos2,"black");
                    if (checkMove) {
                        moveHelper(pos1,pos2);
                        setFlags(pos1, pos2);
                        successMove=true;
                        break;
                    }
                }
            }
            if (!successMove) {
                string pos1 = alm[0].first;
                string pos2 = alm[0].second;
                moveHelper(pos1, pos2);
                setFlags(pos1, pos2);
            }
            setWhiteTurn(true);
            setBlackTurn(false);
            notifyObservers();
            return true;
        } else if (blackPlayer.getType() == Type::computerLevel3) {
            vector<pair<string,string>> almw = allLegalMoves("white");
            vector<pair<string,string>> almb = allLegalMoves("black");
            bool successMove = false;
            vector<string> needHelpPos; //store the threatened pieces
            for (pair<string,string>& move : almw) {
                //find a threatened black piece
                string pos2=move.second;
                if (board[pos2]!=nullptr) {
                    //since it is in white's legalmoves, it must be a black piece
                    needHelpPos.emplace_back(pos2);
                }
            }
            if (!needHelpPos.empty()) {
                //if there is need to avoid capture
                for (pair<string,string>& move : almb) {
                    string pos1=move.first;
                    string pos2=move.second;
                    for (const string& pos : needHelpPos) {
                        if (pos==pos1) {
                            bool underThreat = false;
                            //check if current move can escape the capture
                            for (pair<string,string>& oppmove : almw) {
                                if (pos2==oppmove.second) {
                                    //still capturable
                                    underThreat = true;
                                    break;
                                }
                            }
                            if (!underThreat) {
                                // if current move can avoid capture
                                moveHelper(pos1,pos2);
                                setFlags(pos1,pos2);
                                successMove=true;
                            }
                            break;
                        }
                    }
                    if (successMove) {
                        break;
                    }
                }
            }
            if (!successMove) {
                //if cannot avoid any capture or no capture to avoid
                for (pair<string,string>& move : almb) {
                    string pos1=move.first;
                    string pos2=move.second;
                    //check if it is a capturing move
                    if (board[pos2]!=nullptr) {
                        // since same colour piece should not be in legalmoves, this is opponent
                        moveHelper(pos1,pos2);
                        setFlags(pos1, pos2);
                        successMove= true;
                        break;
                    } else {
                        // check if it is check move
                        bool checkMove = simulateMove(pos1,pos2,"white");
                        if (checkMove) {
                            moveHelper(pos1,pos2);
                            successMove=true;
                            break;
                        }
                    }
                }
            }
            if (!successMove) {
                string pos1 = almb[0].first;
                string pos2 = almb[0].second;
                moveHelper(pos1, pos2);
                setFlags(pos1,pos2);
            }
            setWhiteTurn(true);
            setBlackTurn(false);
            notifyObservers();
            return true;
        } else if (blackPlayer.getType() == Type::computerLevel4) {
            vector<pair<string,string>> almw = allLegalMoves("white");
            vector<pair<string,string>> almb = allLegalMoves("black");
            bool successMove = false;
            vector<string> needHelpPos; //store the threatened pieces
            // check for captures
            int topPoint = 0;
            pair<string, string> topPointMove;
            for (pair<string,string>& move : almb) {
                string pos1=move.first;
                string pos2=move.second;
                if (board[pos2] != nullptr && board[pos2].get()->getPoint()>topPoint) {
                    //if move captures opponent and is better than the current capture
                    topPoint = board[pos2].get()->getPoint();
                    topPointMove.second = pos2;
                    topPointMove.first = pos1;
                    successMove = true;
                }
            }
            if (successMove) {
                // capture the highest point
                moveHelper(topPointMove.first,topPointMove.second);
                setFlags(topPointMove.first,topPointMove.second);
            } else {
                //attempt avoiding capture
                for (pair<string,string>& move : almw) {
                    //find a threatened black piece
                    string pos2=move.second;
                    if (board[pos2]!=nullptr) {
                        //since it is in white's legalmoves, it must be a black piece
                        needHelpPos.emplace_back(pos2);
                    }
                }
                if (!needHelpPos.empty()) {
                    //if there is need to avoid capture
                    for (pair<string,string>& move : almb) {
                        string pos1=move.first;
                        string pos2=move.second;
                        for (const string& pos : needHelpPos) {
                            if (pos==pos1) {
                                bool underThreat = false;
                                //check if current move can escape the capture
                                for (pair<string,string>& oppmove : almw) {
                                    if (pos2==oppmove.second) {
                                        //still capturable
                                        underThreat = true;
                                        break;
                                    }
                                }
                                if (!underThreat) {
                                    // if current move can avoid capture
                                    moveHelper(pos1,pos2);
                                    setFlags(pos1,pos2);
                                    successMove=true;
                                }
                                break;
                            }
                        }
                        if (successMove) {
                            break;
                        }
                    }
                }
            }
            if (!successMove) {
                // try check move
                for (pair<string,string>& move : almb) {
                    string pos1=move.first;
                    string pos2=move.second;
                    bool checkMove = simulateMove(pos1,pos2,"white");
                    if (checkMove) {
                        moveHelper(pos1,pos2);
                        setFlags(pos1, pos2);
                        successMove=true;
                        break;
                    }
                }
            }
            if (!successMove) {
                string pos1 = almb[0].first;
                string pos2 = almb[0].second;
                moveHelper(pos1, pos2);
                setFlags(pos1,pos2);
            }
            setWhiteTurn(true);
            setBlackTurn(false);
            notifyObservers();
            return true;
        }
    }
    return false;
}

bool Model::move(const string& pos1, const string& pos2) {
    bool valid = false;
    if (whitePlayer.getTurn()) {
        if (!whitePlayer.isComputer()) {
            for (const auto& m:allLegalMoves("white")) {
                cout << m.first << " " << m.second << endl;
                if (pos1 == m.first && pos2 == m.second) {
                    string temp = pos2;
                    temp[1] = pos2[1] - 1;
                    if (board[pos1]->getType() == "Pawn" && board[temp] != nullptr
                        && board[temp]->isDoubleStepped()) {
                        removePiece(temp);
                    }
                    moveHelper(pos1, pos2);
                    if (pos1 == "e1" && pos2 == "g1" && board[pos2]->getType() == "King") {
                        moveHelper("h1", "f1");
                    } // king side castling
                    else if (pos1 == "e1" && pos2 == "c1" && board[pos2]->getType() == "King") {
                        moveHelper("a1", "d1");
                    } // queen side castling
                    valid = true;
                    break;
                }

            }

        }
    }
    if (blackPlayer.getTurn()) {
        if (!blackPlayer.isComputer()) {
            for (const auto& m:allLegalMoves("black")) {
                cout << m.first << " " << m.second << endl;
                if (pos1 == m.first && pos2 == m.second) {
                    string temp = pos2;
                    temp[1] = pos2[1] + 1;
                    if (board[pos1]->getType() == "Pawn" && board[temp] != nullptr
                        && board[temp]->isDoubleStepped()) {
                        removePiece(temp);
                    }
                    moveHelper(pos1, pos2);
                    if (pos1 == "e8" && pos2 == "g8" && board[pos2]->getType() == "King") {
                        moveHelper("h8", "f8");
                    } // king side castling
                    else if (pos1 == "e8" && pos2 == "c8" && board[pos2]->getType() == "King") {
                        moveHelper("a8", "d8");
                    } // queen side castling

                    valid = true;
                    break;
                }
            }
        }
    }
    if (valid) {
        setWhiteTurn(!whitePlayer.getTurn());
        setBlackTurn(!blackPlayer.getTurn());
        setFlags(pos1, pos2);
        notifyObservers();
    }
    return valid;
} // called when player is human
bool Model::move(const string& pos1, const string& pos2, const string& piece) {
    if (whitePlayer.getTurn()) {
        if (!whitePlayer.isComputer()) {
            if (pos2[1] == '8' && board[pos1]->getType() == "Pawn") { // checks if tile is in last row
                for (const auto& m: allLegalMoves("white")) {
                    if (pos1 == m.first && pos2 == m.second) {
                        if (piece == "Q" || piece == "R" || piece == "N" || piece == "B") {
                            removePiece(pos1);
                            addPiece(piece, pos2);
                            setWhiteTurn(false);
                            setBlackTurn(true);
                            board[pos2]->setPosition(pos2);
                            board[pos2]->setHasMoved(true);
                            setFlags(pos1, pos2);
                            notifyObservers();
                            return true;
                        }
                    }
                }
            }

        }
    }
    if (blackPlayer.getTurn()) {
        if (!blackPlayer.isComputer()) {
            if (pos2[1] == '1' && board[pos1]->getType() == "Pawn") { // checks if tile is in last row
                for (const auto& m: allLegalMoves("black")) {
                    if (pos1 == m.first && pos2 == m.second) {
                        if (piece == "q" || piece == "r" || piece == "n" || piece == "b") {
                            removePiece(pos1);
                            addPiece(piece, pos2);
                            setWhiteTurn(true);
                            setBlackTurn(false);
                            board[pos2]->setPosition(pos2);
                            board[pos2]->setHasMoved(true);
                            setFlags(pos1, pos2);
                            notifyObservers();
                            return true;
                        }
                    }
                }
            }

        }
    }
    return false;
} // pawn promotion


void Model::notifyObservers() {
    td->notify(board);
    gd->notify(board);
}//call notify(board) on gd, td

string Model::endgame() {
    inGame = false;
    reset();
    if (whitePlayer.getTurn()) {
        blackPlayer.incScore(1);
        return "black";
    }
    else {
        whitePlayer.incScore(1);
        return "white";
    }

} // called when resign/checkmate etc

ostream &operator<<(ostream &out, const Model &m) {
    out << *(m.td);
    return out;
} //out<<*(m.td)