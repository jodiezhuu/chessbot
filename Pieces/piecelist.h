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
    std::map <PieceType, int> pieceCount;
public:
    PieceList(PieceColor color);
    std::vector<Piece *> *getPieces();
    int getPieceCount(PieceType type);
    ~PieceList();
    bool verify();
    void addPiece(Piece *piece);
    void removePieces(Piece *piece);
    size_t getLength();
};

#endif