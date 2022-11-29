#ifndef __PIECE_H__
#define __PIECE_H__
#include "piececolor.h"
#include "square.h"
#include "piecetype.h"
class Piece {
    PieceColor color;
    Square *pos;
    PieceType type;
public:
    Piece(PieceColor color, Square *pos, PieceType type);
};

#endif