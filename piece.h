#ifndef __PIECE_H__
#define __PIECE_H__
#include "piececolor.h"
#include "square.h"
class Piece {
    PieceColor color;
    Square pos;
public:
    Piece(PieceColor color, Square pos);
};
#endif