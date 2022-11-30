#ifndef __PAWN_H__
#define __PAWN_H__
#include "piece.h"

class Pawn: public Piece {
    int moveNum = 0;
public:
    Pawn(Board *b, PieceColor color, Square *pos, PieceType type);
    bool isMoveValid(int row, int col) override;
    virtual Square ** validMoves() override;
    virtual Square ** capturingMoves() override; 
    virtual bool canBeCaptured() override; 
};

#endif