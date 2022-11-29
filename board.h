#ifndef __BOARD_H__
#define __BOARD_H__
#include "game.h"
#include "piecelist.h"
#include "square"
#include <string>

class Board {
    public:
        Board();
        void resetBoard();
        PieceList* getWhitePieces();
        PieceList* getBlackPieces();
        Square* getCell(int row, int col);
        bool addPiece(int row, int col, Piece* piece);
        void removePiece(int row, int col);
        ~Board();
    private:
        void intializeBoard();
        PieceList[] piecelists;
        Square[][] boardlist;
}

#endif