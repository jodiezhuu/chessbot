#ifndef __GAME_H__
#define __GAME_H__
#include "piececolor.h"
#include "piecetype.h"
#include "board.h"
//#include "player.h"
#include "subject.h"
#include <string>

class Game: public Subject {
    // Board * board;
    bool finished;
    PieceColor turn;
    // Player players[2];
    enum CheckStatus = {InCheckBlack = 0, InCheckWhite, CheckmatedBlack, CheckmatedWhite, None};
    enum Result = {BlackWon = 0, WhiteWon, Draw, Ongoing};
    CheckStatus status;
    Result result;
    int scores[2];
public:
    Game();
    ~Game();
    PieceType getState(int row, int col);
    void render();
    bool addPiece(std::string type, std::string location);
    bool removePiece(std::string location);
};

#endif