#ifndef __KNIGHT_H__
#define __KNIGHT_H__
#include "piece.h"
class Knight: public Piece {
public:
    Knight(Board *b, PieceColor color, Square *pos, PieceType type);
    // bool isMoveValid(int row, int col, PieceColor color, Board *b) override;
    // Square[] validMoves(Board *b) override;
    // Square[] capturingMoves(Board *b) override; 
    // bool canBeCaptured(Board *b) override; 
};

#endif