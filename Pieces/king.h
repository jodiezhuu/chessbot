#ifndef __KING_H__
#define __KING_H__
#include "piece.h"
class King: public Piece {
    // bool moveInCheck(int row, int col);
public:
    King(Board *b, PieceColor color, Square *pos, PieceType type);
    void calculateAllMoves() override;
};

#endif