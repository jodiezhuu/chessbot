#ifndef __PAWN_H__
#define __PAWN_H__
#include "piece.h"

class Pawn: public Piece {
public:
    Pawn(Board *b, PieceColor color, Square *pos, PieceType type);
    bool isMoveValid(int row, int col) override;
    virtual void calculateValidMoves() override;
    virtual void calculateCapturingMoves() override;
    virtual bool canBeCaptured() override; 
};

#endif