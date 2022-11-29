#ifndef __BOARD_H__
#define __BOARD_H__
#include "game.h"
#include "piecelist.h"
#include "square"

class Board {
    public:
        Board();
        void resetBoard();
        PieceList[] getPieceLists();
        Square[][] getBoard():
        bool addPiece(int row, int col, Piece* piece);
        void removePiece(int row, int col);
        ~Board();
    private:
        PieceList[] piecelists;
        Square[][] boardlist;
}

#endif