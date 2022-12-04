#ifndef __KNIGHT_H__
#define __KNIGHT_H__
#include "piece.h"
class Knight: public Piece {
public:
    Knight(Board *b, PieceColor color, Square *pos, PieceType type);
    void calculateAllMoves() override;
};

#endif