#ifndef __KING_H__
#define __KING_H__
#include "piece.h"
class King: public Piece {
public:
    King(Board *b, PieceColor color, Square *pos, PieceType type);
    bool isMoveValid(int row, int col) override;
    virtual void calculateValidMoves() override;
    virtual void calculateCapturingMoves() override;
    virtual bool canBeCaptured() override; 
};

#endif