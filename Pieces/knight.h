#ifndef __KNIGHT_H__
#define __KNIGHT_H__
#include "piece.h"
class Knight: public Piece {
public:
    Knight(Board *b, PieceColor color, Square *pos, PieceType type);
    bool isMoveValid(int row, int col) override;
    virtual void calculateValidMoves() override;
    virtual void calculateCapturingMoves() override;
    virtual bool canBeCaptured() override;  
};

#endif