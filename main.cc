#include <iostream>
#include <string>
#include "game.h"
#include "textview.h"
#include <time.h>
#include "graphicview.h"

using namespace std;

int main() {
    srand(time(NULL));
    string command;
    Game * gameEngine = new Game{};
    TextView * textOutput = new TextView{gameEngine};
    GraphicView * graphicOutput = new GraphicView{gameEngine};
    gameEngine->notifyObservers();
    while (cin >> command) {
        if (command == "game") {
            graphicOutput->clearMessage();
            if (gameEngine->isOngoing()) {
                cout << "Game has already started" << endl;
                graphicOutput->displayMessage("Game has already started");
            } else {
                try {
                    string playerOneType, playerTwoType;
                    cin >> playerOneType >> playerTwoType;
                    gameEngine->startGame(playerOneType, playerTwoType);
                    gameEngine->applyStatus();
                    gameEngine->notifyObservers();
                } catch (InvalidInput) {
                    cout << "Invalid parameters" << endl;
                    graphicOutput->displayMessage("Invalid parameters");
                }
            }
        } else if (command == "resign") {
            graphicOutput->clearMessage();
            if (gameEngine->isOngoing()) gameEngine->resign();
            else cout << "No game has been started" << endl; graphicOutput->displayMessage("No game has been started");
        } else if (command == "move") {
            graphicOutput->clearMessage();
            if (!gameEngine->isOngoing()) {
                cout << "Must start game before moving" << endl;
                graphicOutput->displayMessage("Must start game before moving");
                continue;
            }
            if ((gameEngine->getTurn() == PieceColor::White && gameEngine->isComputer(PieceColor::White)) || (gameEngine->getTurn() == PieceColor::Black && gameEngine->isComputer(PieceColor::Black))) {
                graphicOutput->clearMessage();
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
                    graphicOutput->clearMessage();
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
                    graphicOutput->displayMessage("Invalid parameters");
                }
            }
            gameEngine->applyStatus();
            int status = gameEngine->getStatus();
            if (status == 0) { // BlackInCheck
                cout << "Black is in check" << endl;
                graphicOutput->displayMessage("Black is in check");
            } else if (status == 1) { // WhiteInCheck
                cout << "White is in check" << endl;
                graphicOutput->displayMessage("White is in check");
            } else if (status == 2) { // BlackCheckmated
                cout << "Checkmate! Black wins!" << endl;
                graphicOutput->displayMessage("Checkmate! Black wins!");
            } else if (status == 3) { // WhiteCheckmated
                cout << "Checkmate! White wins!" << endl;
                graphicOutput->displayMessage("Checkmate! White wins!");
            } else if (status == 4) { // Stalemate
                cout << "Stalemate!" << endl;
                graphicOutput->displayMessage("Stalemate!");
            }
        } else if (command == "setup") {
            graphicOutput->clearMessage();
            cout << endl;
            cout << "Setup:" << endl;
            graphicOutput->displayMessage("Setup:");
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
                        graphicOutput->displayMessage("Invalid parameters");
                    }
                } else if (subCommand == "-") {
                    try{
                        string location;
                        cin >> location;
                        gameEngine->removePiece(location);
                    } catch (InvalidInput) {
                        cout << "Invalid parameters" << endl;
                        graphicOutput->displayMessage("Invalid parameters");
                    }
                } else if (subCommand == "=") {
                    try {
                        string colour;
                        cin >> colour;
                        gameEngine->setTurn(colour);
                    } catch (InvalidInput) {
                        cout << "Invalid colour" << endl;
                        graphicOutput->displayMessage("Invalid colour");
                    }
                } else if (subCommand == "done") {
                    if (gameEngine->verifySetup()) {
                        cout << endl << "Exitting setup" << endl;
                        graphicOutput->displayMessage("Exitting setup");
                        break;
                    } else {
                        cout << "Board conditions are not satisfied" << endl;
                        graphicOutput->displayMessage("Board conditions are not satisfied");
                    }
                }
            }
        }
    }
    gameEngine->printScore();
    // Delete all objects
    delete gameEngine;
    delete textOutput;
    delete graphicOutput;
}