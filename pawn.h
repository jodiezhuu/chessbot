#ifndef __PAWN_H__
#define __PAWN_H__
#include "piece.h"
#include "piececolor.h"
#include "square.h"
#include "board.h"

class Pawn: public Piece {
    PieceColor color;
    Square *pos;
public:
    Pawn(PieceColor color, Square *pos);
    bool isMoveValid(int row, int col, PieceColor color, Board *b) override;
    Square[] checkMoves(Board *b) override;
    Square[] capturingMoves(Board *b) override; 
    bool canBeCaptured(Board *b) override; 
}
#endif