#ifndef __PIECE_H__
#define __PIECE_H__
#include "piececolor.h"
#include "square.h"
#include "piecetype.h"
#include "board.h"
class Piece {
    PieceColor color;
    Square *pos;
    PieceType type;
public:
    Piece(PieceColor color, Square *pos, PieceType type);
    PieceType getPieceType();
    PieceColor getColor();
    Square *getPosition();
};

#endif