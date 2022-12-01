#ifndef __PAWN_H__
#define __PAWN_H__
#include "piece.h"

class Pawn: public Piece {
public:
    Pawn(Board *b, PieceColor color, Square *pos, PieceType type);
    virtual void calculateMoves() override;
};

#endif