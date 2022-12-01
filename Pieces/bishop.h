#ifndef __BISHOP_H__
#define __BISHOP_H__
#include "piece.h"
class Bishop: public Piece {
public:
    Bishop(Board *b, PieceColor color, Square *pos, PieceType type);
    bool isMoveValid(int row, int col) override;
    virtual void calculateValidMoves() override;
    virtual void calculateCapturingMoves() override;
    virtual bool canBeCaptured() override; 
};

#endif