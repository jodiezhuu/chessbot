#ifndef __QUEEN_H__
#define __QUEEN_H__
#include "piece.h"
class Queen: public Piece {
public:
    Queen(Board *b, PieceColor color, Square *pos, PieceType type);
    void calculateAllMoves() override;
};

#endif