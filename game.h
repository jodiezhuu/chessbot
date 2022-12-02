#ifndef __GAME_H__
#define __GAME_H__
#include "Pieces/piececolor.h"
#include "Pieces/piecetype.h"
#include "player.h"
#include "subject.h"
#include <string>

class Board;
class Player;

class Game: public Subject {
    bool ongoing;
    Board * board;
    PieceColor turn;
    Player *players[2];
    enum class CheckStatus {InCheckBlack, InCheckWhite, CheckmatedBlack, CheckmatedWhite, None};
    enum class Result {BlackWon, WhiteWon, Draw, Ongoing};
    CheckStatus status;
    Result result;
    float scores[2];
    PieceType convertChar(char c);
    void reset();
public:
    Game();
    ~Game();
    PieceType getState(int row, int col);
    PieceColor getTurn();
    bool getGameState() const;
    bool move(std::string from, std::string to);
    bool move();
    bool isComputer(PieceColor color);
    void startGame(std::string playerOneType, std::string playerTwoType);
    bool addPiece(std::string type, std::string location);
    void removePiece(std::string location);
    void render();
    void setTurn(std::string colour);
    void printScore();
    void resign();
    bool verifySetup();
};

#endif