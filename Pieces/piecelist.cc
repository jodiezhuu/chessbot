#include "piecelist.h"
#include "piece.h"
#include "piececolor.h"
#include <vector>
#include <map>
#include <iostream>

PieceList::PieceList(PieceColor color): color{color} {}

// returns the number of pieces of a certain piece type
int PieceList::getPieceCount(PieceType type) {
    if (pieceCount.count(type) == 0) return 0;
    return pieceCount[type];
}

// accessor for piece list
std::vector<Piece *> *PieceList::getPieces() {
    return &pieces;
}

// mutator to add to piece list 
void PieceList::addPiece(Piece *p) {
    if (pieceCount.count(p->getPieceType()) == 0) {
        pieceCount[p->getPieceType()] = 1;
    } else {
        pieceCount[p->getPieceType()] += 1;
    }
    pieces.push_back(p);
}

// mutator to remove a piece in piece list
void PieceList::removePieces(Piece *piece) {
    for (auto p = pieces.begin(); p != pieces.end(); ++p) {
        if (*p == piece) {
            pieceCount[piece->getPieceType()] -= 1;
            pieces.erase(p);
            return;
        }
    }
}

// accessor to piece list length
size_t PieceList::getLength() {
    return pieces.size();
}

// destroys piece list vector
PieceList::~PieceList() {
    for (auto p: pieces) {
        delete p;
    }
}
