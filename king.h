#ifndef __KING_H__
#define __KING_H__
#include "piececolor.h"
#include "board.h"
#include "square.h"
class King: public Piece {
    PieceColor color;
    Square *pos;
public:
    King(PieceColor color, Square *pos);
    bool isMoveValid(int row, int col, PieceColor color, Board *b) override;
    Square[] checkMoves(Board *b) override;
    Square[] capturingMoves(Board *b) override; 
    bool canBeCaptured(Board *b) override; 
}

#endif