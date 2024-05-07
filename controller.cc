#include "controller.h"
#include <sstream>
using namespace std;

Controller::Controller() : m{nullptr} {
}

Controller::~Controller() {
}

void Controller::control(istream &in, ostream &out) {
    Xwindow xw{560, 560};
    m = make_unique<Model>(xw);
    string cmd;
    while (true) {
        if (!(in >> cmd)) {
            // if reaches end or encounters errors
            break;
        }
        if (cmd == "setup" && !(m->isInGame())) {
            //enter setup mode when game is not running
            m->beginSetup();
            while (true) {
                if (!(in >> cmd)) {
                    break;
                }
                if (cmd == "done") {
                    // check whether user can leave setup
                    bool canLeave = m->validSetup();
                    if (canLeave) {
                        m->endSetup();
                        break;
                    } else {
                        out << "Setup is not valid. Still in setup mode." << endl;
                    }
                } else if (cmd == "+") {
                    string piece; 
                    string pos;
                    in >> piece >> pos;
                    m->addPiece(piece,pos);
                    out << *m; // board redisplayed
                } else if (cmd == "-") {
                    string pos;
                    in >> pos;
                    m->removePiece(pos);
                    out << *m; // board redisplayed
                } else if (cmd == "=") {
                    string colour;
                    in >> colour;
                    if (colour == "white") {
                        m->setWhiteTurn(true);
                        m->setBlackTurn(false);
                    } else if (colour == "black") {
                        m->setBlackTurn(true);
                        m->setWhiteTurn(false);
                    } else {
                        out << "Invalid colour." << endl;
                    }
                } else {
                    out << "Setup command not recognized. Please try again." << endl;
                }
            }
        } else if (cmd == "game") {
            // to start a new game + check if player type is permitted
            string type1;
            string type2;
            in >> type1 >> type2;
            if ((type1 == "human" || type1 == "computer1" || type1 == "computer2" 
            || type1 == "computer3" || type1 == "computer4")
            && (type2 == "human" || type2 == "computer1" || type2 == "computer2" 
            || type2 == "computer3" || type2 == "computer4")) {
                m->game(type1, type2);
            } else {
                out << "Invalid player type." << endl;
            }
        } else if (cmd == "resign" && m->isInGame()) {
            // model will determine which player resigns by looking at turn
            string winner = m->endgame();
            if (winner=="white") {
                out << "White wins!" << endl;
            } else {
                out << "Black wins!" << endl;
            }
        } else if (cmd == "move" && m->isInGame()) {
            string line;
            string arg;
            string pos1;
            string pos2;
            string piece;
            bool success;
            getline(in, line);
            istringstream iss = istringstream(line);
            int argcount=0;
            while (iss >> arg) {
                // move is different based on number of arguments
                if (argcount==0) {
                    pos1 = arg;
                } else if (argcount==1) {
                    pos2 = arg;
                } else if (argcount==2) {
                    piece = arg;
                }
                ++argcount;
            }
            if (argcount==3) {
                //pawn promotion
                success = m->move(pos1,pos2,piece);
            } else if (argcount==2) {
                //human move
                success = m->move(pos1,pos2);
            } else if (argcount==0) {
                //computer move
                success = m->move();
            } else {
                out << "Invalid number of arguments provided to move" << endl;
                continue;
            }
            if (!success) {
                out << "Invalid move. Try again." << endl;
                continue;
            }
            out << *m; //board redisplayed
            // additionally output message in the following conditions:
            if (m->isCheckmated("white")) {
                out << "Checkmate! Black wins!" << endl;
            }
            else if (m->isCheckmated("black")) {
                out << "Checkmate! White wins!" << endl;
            } else if (m->isStalemate()) {
                out << "Stalemate!" << endl;
            } else if (m->isInCheck("white")) {
                out << "White is in check." << endl;
            } else if (m->isInCheck("black")) {
                out << "Black is in check." << endl;
            }
        } else {
            out << "Command not recognized. Please try again." << endl;
        }
    }
    out << "Final Score: " << endl << "White: " << m->getScore("white") << endl
        << "Black: " << m->getScore("black") << endl;
}
