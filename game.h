#ifndef __GAME_H__
#define __GAME_H__
#include "piececolor.h"
#include "piecetype.h"
//#include "player.h"
#include "subject.h"
#include <string>

class Board;

class Game: public Subject {
    Board * board;
    bool finished;
    PieceColor turn;
    // Player players[2];
    enum class CheckStatus {InCheckBlack, InCheckWhite, CheckmatedBlack, CheckmatedWhite, None};
    enum class Result {BlackWon, WhiteWon, Draw, Ongoing};
    CheckStatus status;
    Result result;
    int scores[2];
public:
    Game();
    ~Game();
    PieceType getState(int row, int col);
    bool addPiece(std::string type, std::string location);
    bool removePiece(std::string location);
    void render();
};

#endif