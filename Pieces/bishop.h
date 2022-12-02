#ifndef __BISHOP_H__
#define __BISHOP_H__
#include "piece.h"
class Bishop: public Piece {
public:
    Bishop(Board *b, PieceColor color, Square *pos, PieceType type);
    virtual void calculateMoves() override;
};

#endif