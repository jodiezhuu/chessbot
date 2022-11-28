#ifndef __PIECELIST_H__
#define __PIECELIST_H__
#include "piece.h"
#include "piececolor.h"
#include <vector>

class PieceList {
std::vector<Piece *> pieces;
const PieceColor color;
public:
    PieceList(std::vector<Piece *> pieces, PieceColor color);
    std::vector<Piece *> getPieces();
    std::vector<Piece *> addPieces();
    std::vector<Piece *> removePieces();
    ~PieceList();
};

#endif