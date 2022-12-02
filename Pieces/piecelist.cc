#include "piecelist.h"
#include "piece.h"
#include "piececolor.h"
#include <vector>
#include <map>
#include <iostream>

PieceList::PieceList(PieceColor color): color{color} {}

int PieceList::getPieceCount(PieceType type) {
    if (pieceCount.count(type) == 0) return 0;
    return pieceCount[type];
}

std::vector<Piece *> *PieceList::getPieces() {
    return &pieces;
}

void PieceList::addPiece(Piece *p) {
    if (pieceCount.count(p->getPieceType()) == 0) {
        pieceCount[p->getPieceType()] = 1;
    } else {
        pieceCount[p->getPieceType()] += 1;
    }
    pieces.push_back(p);
}

void PieceList::removePieces(Piece *piece) {
    for (auto p = pieces.begin(); p != pieces.end(); ++p) {
        if (*p == piece) {
            pieceCount[(*p)->getPieceType()] -= 1;
            pieces.erase(p);
            return;
        }
    }
}

size_t PieceList::getLength() {
    return pieces.size();
}

PieceList::~PieceList() {
    for (auto p: pieces) {
        delete p;
    }
}
