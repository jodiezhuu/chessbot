#ifndef __QUEEN_H__
#define __QUEEN_H__
#include "piece.h"
class Queen: public Piece {
public:
    Queen(Board *b, PieceColor color, Square *pos, PieceType type);
    bool isMoveValid(int row, int col) override;
    virtual void calculateValidMoves() override;
    virtual void calculateCapturingMoves() override;
    virtual bool canBeCaptured() override; 
};

#endif