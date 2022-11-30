#ifndef __BOARD_H__
#define __BOARD_H__
#include "game.h"
#include "square.h"
#include <string>

class PieceList;

class Board {
private:
    PieceList* piecelists[2];
    Square* boardlist[8][8];
    void intializeBoard();
public:
    bool addPiece(int row, int col, Piece* piece);
    void removePiece(int row, int col);
    Board();
    void resetBoard();
    PieceList* getWhitePieces();
    PieceList* getBlackPieces();
    Square* getCell(int row, int col);
    ~Board();
};

#endif