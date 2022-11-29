#include "piecelist.h"
#include "piece.h"
#include "piececolor.h"
#include <vector>
#include <map>

PieceList::PieceList(PieceColor color)
: color{color} {}

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

bool PieceList::removePieces(Piece *piece) {
    int counter = 0;
    if (pieceCount[piece] > 0) {
        for (auto p = pieces.begin(); p != pieces.end(); p++) {
            if (*p == piece) {
                pieces.erase(p);
                return true;
            }
        }
    } return false;
}

PieceList::~PieceList() {
    for (auto p: pieces) {
        delete p;
    }
}
