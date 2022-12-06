#include <iostream>
#include <string>
#include "game.h"
#include "textview.h"
#include <time.h>
//#include "graphicview.h"

using namespace std;

int main() {
    srand(time(0));
    string command;
    Game * gameEngine = new Game{};
    TextView * textOutput = new TextView{gameEngine};
    //GraphicView * graphicOutput = new GraphicView{gameEngine};
    gameEngine->notifyObservers();
    while (cin >> command) {
        if (command == "game") {
            if (gameEngine->isOngoing()) {
                cout << "Game has already started" << endl;
            } else {
                try {
                    string playerOneType, playerTwoType;
                    cin >> playerOneType >> playerTwoType;
                    gameEngine->startGame(playerOneType, playerTwoType);
                    gameEngine->applyStatus();
                    gameEngine->notifyObservers();
                } catch (InvalidInput) {
                    cout << "Invalid parameters" << endl;
                }
            }
        } else if (command == "resign") {
            if (gameEngine->isOngoing()) gameEngine->resign();
            else cout << "No game has been started" << endl;
        } else if (command == "move") {
            if (!gameEngine->isOngoing()) {
                cout << "Must start the game before moving pieces" << endl;
                continue;
            }
            if ((gameEngine->getTurn() == PieceColor::White && gameEngine->isComputer(PieceColor::White)) || (gameEngine->getTurn() == PieceColor::Black && gameEngine->isComputer(PieceColor::Black))) {
                std::string to = gameEngine->getComputerToMove();
                if (gameEngine->isPawnUpgrading(to)) {
                    PieceType upgradedPiece = {gameEngine->getTurn() == PieceColor::White ? gameEngine->convertChar('Q') : gameEngine->convertChar('q')};
                    gameEngine->upgradePawn(upgradedPiece, to);
                }
                if (gameEngine->getTurn() == PieceColor::Black) gameEngine->setTurn("white");
                else gameEngine->setTurn("black");
                gameEngine->notifyObservers();
            } else {
                try {
                    string from, to;
                    cin >> from >> to;
                    if (gameEngine->move(from, to)) {
                        gameEngine->pawnMoveTwo(from, to);
                        if (gameEngine->isPawnUpgrading(to)) {
                            string c;
                            cin >> c;
                            PieceType upgradedPiece = gameEngine->convertChar(c[0]);
                            gameEngine->upgradePawn(upgradedPiece, to);
                        }
                        if (gameEngine->getTurn() == PieceColor::Black) gameEngine->setTurn("white");
                        else gameEngine->setTurn("black");
                        gameEngine->notifyObservers();
                    }
                } catch (InvalidInput) {
                    cout << "Invalid parameters" << std::endl;
                }
            }
            gameEngine->applyStatus();

        } else if (command == "setup") {
            cout << endl;
            cout << "Setup:" << endl;
            gameEngine->notifyObservers();
            string subCommand;
            while (cin >> subCommand) {
                if (subCommand == "+") {
                    try{
                        string piece, location;
                        cin >> piece >> location;
                        gameEngine->addPiece(piece, location);
                    } catch (InvalidInput) {
                        cout << "Invalid parameters" << endl; 
                    }
                } else if (subCommand == "-") {
                    try{
                        string location;
                        cin >> location;
                        gameEngine->removePiece(location);
                    } catch (InvalidInput) {
                        cout << "Invalid parameters" << endl;
                    }
                } else if (subCommand == "=") {
                    try {
                        string colour;
                        cin >> colour;
                        gameEngine->setTurn(colour);
                    } catch (InvalidInput) {
                        cout << "Invalid colour" << endl;
                    }
                } else if (subCommand == "done") {
                    if (gameEngine->verifySetup()) {
                        cout << endl << "Exiting setup" << endl;
                        break;
                    } else {
                        cout << "Board conditions are not satisfied" << endl;
                    }
                }
            }
        }
    }
    gameEngine->printScore();
    // Delete all objects
    delete gameEngine;
    delete textOutput;
    //delete graphicOutput;
}