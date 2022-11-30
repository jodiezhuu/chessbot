#ifndef __GAME_H__
#define __GAME_H__
#include "Pieces/piececolor.h"
#include "Pieces/piecetype.h"
//#include "player.h"
#include "subject.h"
#include <string>

class Board;

class Game: public Subject {
    bool ongoing;
    Board * board;
    PieceColor turn;
    // Player players[2];
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
    bool addPiece(std::string type, std::string location);
    bool removePiece(std::string location);
    void render();
    void setTurn(std::string colour);
    void printScore();
    void resign();
};

#endif