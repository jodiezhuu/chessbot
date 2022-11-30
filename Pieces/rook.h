#ifndef __ROOK_H__
#define __ROOK_H__
#include "piece.h"
class Rook: public Piece {
public:
    Rook(Board *b, PieceColor color, Square *pos, PieceType type);
    bool isMoveValid(int row, int col) override;
    virtual void calculateValidMoves() override;
    virtual void calculateCapturingMoves() override;
    virtual bool canBeCaptured() override; 
};

#endif