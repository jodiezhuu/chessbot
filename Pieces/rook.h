#ifndef __ROOK_H__
#define __ROOK_H__
#include "piece.h"
class Rook: public Piece {
public:
    Rook(Board *b, PieceColor color, Square *pos, PieceType type);
    virtual void calculateAllMoves() override;
};

#endif