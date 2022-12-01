#include "piecelist.h"
#include "piece.h"
#include "piececolor.h"
#include <vector>
#include <map>
#include <iostream>

PieceList::PieceList(PieceColor color): color{color} {}

int PieceList::getPieceCount(Piece *piece) {
    return pieceCount[piece];
}

std::vector<Piece *> *PieceList::getPieces() {
    return &pieces;
}

void PieceList::addPiece(Piece *p) {
    pieceCount[p] += 1;
    pieces.emplace_back(p);
}

void PieceList::removePieces(Piece *piece) {
    if (pieceCount[piece] > 0) {
        for (auto p = pieces.begin(); p != pieces.end(); ++p) {
            if (*p == piece) {
                pieceCount[*p] -= 1;
                pieces.erase(p);
                return;
            }
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
