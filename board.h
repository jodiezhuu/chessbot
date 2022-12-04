#ifndef __BOARD_H__
#define __BOARD_H__
#include "game.h"
#include "square.h"
#include "Pieces/piecetype.h"
#include <string>
#include <vector>

class PieceList;

class Board {
private:
    PieceList* piecelists[2];
    Square* boardlist[8][8];
    void intializeBoard();
public:
    bool addPiece(int row, int col, PieceType piece);
    void removePiece(int row, int col);
    void removePiece(Piece *piece);
    Board();
    void resetBoard();
    PieceList* getWhitePieces();
    PieceList* getBlackPieces();
    Square* getCell(int row, int col);
    bool verifyBoard();
    Piece *getWhiteKing();
    Piece *getBlackKing();
    ~Board();
};

#endif