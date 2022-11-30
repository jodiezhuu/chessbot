#ifndef __ROOK_H__
#define __ROOK_H__
#include "board.h"
#include "piececolor.h"
#include "square.h"
class Rook: public Piece {
    PieceColor color;
    Square *pos;
public:
    Rook(PieceColor color, Square *pos);
    bool isMoveValid(int row, int col, PieceColor color, Board *b) override;
    Square[] checkMoves(Board *b) override;
    Square[] capturingMoves(Board *b) override; 
    bool canBeCaptured(Board *b) override; 
}


#endif