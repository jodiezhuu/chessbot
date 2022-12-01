#ifndef __KING_H__
#define __KING_H__
#include "piece.h"
class King: public Piece {
private:
    bool moveInCheck(int row, int col);
public:
    King(Board *b, PieceColor color, Square *pos, PieceType type);
    bool isMoveValid(int row, int col) override;
    void calculateValidMoves() override;
    void calculateCapturingMoves() override;
    bool canBeCaptured() override;
};

#endif