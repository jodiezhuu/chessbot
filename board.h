#ifndef __BOARD_H__
#define __BOARD_H__
#include "game.h"
#include "square.h"
#include "Pieces/piecetype.h"
#include <string>
#include <vector>

class PieceList;

class Board {
private:
    PieceList* piecelists[2];
    Square* boardlist[8][8];
    std::vector <Square *> whiteKingMoves[2];
    std::vector <Square *> blackKingMoves[2];
    void intializeBoard();
    void kingMovesHelper(Piece *king, std::vector <Square *> &validmoves, std::vector <Square *> &capturingMoves);
public:
    bool addPiece(int row, int col, PieceType piece);
    void removePiece(int row, int col);
    void removePiece(Piece *piece);
    Board();
    void resetBoard();
    PieceList* getWhitePieces();
    PieceList* getBlackPieces();
    Square* getCell(int row, int col);
    bool verifyBoard();
    // Returns array[2] of Square * vectors, first vector is valid moves, second vector is capturing moves
    std::vector <Square *> *getWhiteKingMoves();
    std::vector <Square *> *getBlackKingMoves();
    Piece *getWhiteKing();
    Piece *getBlackKing();
    ~Board();
};

#endif