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
        for (auto it = pieces.begin(); it != pieces.end(); it++) {
            if (*it == piece) {
                pieces.erase(it);
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
