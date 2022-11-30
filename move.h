#ifndef __MOVE_H__
#define __MOVE_H__
#include "square.h"
#include "Pieces/piece.h"

class Move {
    public:
        Move(Square* from, Square* to, Piece* piece);
        Square* getFrom();
        Square* getTo();
        Piece* getPiece();
        void setFrom(Square* newfrom);
        void setTo(Square* newto);
        void setPiece(Piece* piece);
    private:
        Square* from;
        Square* to;
        Piece* piece;
};

#endif