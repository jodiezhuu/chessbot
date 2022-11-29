#ifndef __PIECELIST_H__
#define __PIECELIST_H__
#include "piece.h"
#include "piececolor.h"
#include "piecetype.h"
#include <vector>
#include <map>

class PieceList {
std::vector<Piece *> pieces;
const PieceColor color;
std::map <Piece *, int> pieceCount;
public:
    PieceList(PieceColor color);
    std::vector<Piece *> *getPieces();
    int getPieceCount(Piece *piece);
    ~PieceList();
    bool verify();
    void addPiece(Piece *piece);
    bool removePieces(Piece *piece);
};

#endif