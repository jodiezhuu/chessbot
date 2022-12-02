#include <iostream>
#include <string>
#include "game.h"
#include "textview.h"

using namespace std;

int main() {
    string command;
    Game * gameEngine = new Game{};
    TextView * textOutput = new TextView{gameEngine};
    gameEngine->notifyObservers();
    while (cin >> command) {
        if (command == "game") {
            string playerOneType, playerTwoType;
            cin >> playerOneType >> playerTwoType;
            gameEngine->startGame(playerOneType, playerTwoType);
        } else if (command == "resign") {
            gameEngine->resign();
        } else if (command == "move") {
            if (!gameEngine->getGameState()) {
                cout << "must start game before moving pieces" << endl;
                continue;
            }
            if ((gameEngine->getTurn() == PieceColor::White && gameEngine->isComputer(PieceColor::White)) || (gameEngine->getTurn() == PieceColor::Black && gameEngine->isComputer(PieceColor::Black))) {
               // gameEngine->move();
            } else {
                string from, to;
                cin >> from >> to;
                if (gameEngine->move(from, to)) {
                    if (gameEngine->getTurn() == PieceColor::Black) gameEngine->setTurn("white");
                    else gameEngine->setTurn("black");
                    gameEngine->notifyObservers();
                }
            }
        } else if (command == "setup") {
            cout << endl;
            cout << "Setup:" << endl;
            gameEngine->notifyObservers();
            string subCommand;
            while (cin >> subCommand) {
                if (subCommand == "+") {
                    string piece, location;
                    cin >> piece >> location;
                    gameEngine->addPiece(piece, location);
                } else if (subCommand == "-") {
                    string location;
                    cin >> location;
                    gameEngine->removePiece(location);
                } else if (subCommand == "=") {
                    string colour;
                    cin >> colour;
                    gameEngine->setTurn(colour);
                } else if (subCommand == "done") {
                    if (gameEngine->verifySetup()) {
                        cout << "Exiting setup" << endl << endl; 
                        break;
                    } else {
                        cout << std::endl;
                        cout << "Board conditions are not satisfied: " << std::endl;
                        cout << "- There must be exactly one king for each colour" << std::endl;
                        cout << "- No pawns can be on the first or last row" << std::endl;
                        cout << "- Neither king can be in check" << std::endl << std::endl;
                    }
                }
            }
        }
    }
    gameEngine->printScore();
    // Delete all objects
    delete gameEngine;
}