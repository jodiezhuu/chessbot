#include <iostream>
#include <string>
#include "game.h"
#include "textview.h"
#include <time.h>
//#include "graphicview.h"

using namespace std;

int main() {
    //srand(time(0));
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
                string playerOneType, playerTwoType;
                cin >> playerOneType >> playerTwoType;
                gameEngine->startGame(playerOneType, playerTwoType);
                gameEngine->applyStatus();
            }
        } else if (command == "resign") {
            gameEngine->resign();
        } else if (command == "test") {
            for (int i = 0; i < 100; ++i) {
                cout << i << ": " << rand() % 10 << endl;
            }
        } else if (command == "move") {
            if (!gameEngine->isOngoing()) {
                cout << "Must start the game before moving pieces" << endl;
                continue;
            }
            if ((gameEngine->getTurn() == PieceColor::White && gameEngine->isComputer(PieceColor::White)) || (gameEngine->getTurn() == PieceColor::Black && gameEngine->isComputer(PieceColor::Black))) {
                while(!gameEngine->move());
                if (gameEngine->getTurn() == PieceColor::Black) gameEngine->setTurn("white");
                else gameEngine->setTurn("black");
                gameEngine->notifyObservers();
            } else {
                string from, to;
                cin >> from >> to;
                if (gameEngine->move(from, to)) {
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
            }
            gameEngine->applyStatus();

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
    delete textOutput;
    //delete graphicOutput;
}