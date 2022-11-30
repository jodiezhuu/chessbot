#ifndef __PAWN_H__
#define __PAWN_H__
#include "piece.h"

class Pawn: public Piece {
public:
    Pawn(PieceColor color, Square *pos, PieceType type);
    // bool isMoveValid(int row, int col, PieceColor color, Board *b) override;
    // Square[] checkMoves(Board *b) override;
    // Square[] capturingMoves(Board *b) override; 
    // bool canBeCaptured(Board *b) override; 
};

#endif