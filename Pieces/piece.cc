#include "piece.h"
#include "piecelist.h"
#include <iostream>

Piece::Piece(Board *b, PieceColor color, Square *pos, PieceType type, bool hasMoved): b{b}, color{color}, pos{pos}, type{type}, hasMoved{hasMoved} {}

Piece::~Piece() {}

bool Piece::inBound(int row, int col) {
    return (0 <= row && row <= 7 && 0 <= col && col <= 7);
}

bool Piece::isMoveValid(int row, int col) {
    calculateAllMoves();
    filterAllMoves();
    for (auto moves : validMoves) {
        if (moves == b->getCell(row, col)) {
            return true;
        }
    }
    return false;
}

void Piece::filterAllMoves() {
    Piece *king;
    if (color == PieceColor::Black) {
        king = b->getBlackKing();
    } else {
        king = b->getWhiteKing();
    }

    // Update valid moves vector
    // Makes each valid move, checks if move caues its king to be in check, removes move accordingly, and undos the move
    std::vector <Square *> newValidMoves;
    for (size_t idx = 0; idx < validMoves.size(); ++idx) {
        auto move = validMoves[idx];
        int fromRow = pos->getRow();
        int fromCol = pos->getCol();
        int toRow = move->getRow();
        int toCol = move->getCol();
        b->getCell(fromRow, fromCol)->setPiece(nullptr);
        Piece *old = b->getCell(toRow, toCol)->getPiece();
        b->getCell(toRow, toCol)->setPiece(this);
        setPosition(toRow, toCol);
        if (!king->canBeCapturedIgnoreCheck()) {
            newValidMoves.push_back(validMoves[idx]);
        }
        b->getCell(fromRow, fromCol)->setPiece(this);
        b->getCell(toRow, toCol)->setPiece(old);
        setPosition(fromRow, fromCol);
    }
    // Calculates moves that can deliver a check by making them, checking if the opposite King is in its valid moves, and unmaking that move
    std::vector <Square *> oldCapturingMoves = capturingMoves;
    deliverChecks.clear();
    for (auto move : newValidMoves) {
        int fromRow = pos->getRow();
        int fromCol = pos->getCol();
        int toRow = move->getRow();
        int toCol = move->getCol();
        b->getCell(fromRow, fromCol)->setPiece(nullptr);
        Piece *old = b->getCell(toRow, toCol)->getPiece();
        b->getCell(toRow, toCol)->setPiece(this);
        setPosition(toRow, toCol);
        calculateAllMoves();
        for (auto move2 : validMoves) {
            if ((color == PieceColor::White && move2->getPiece() != nullptr && move2->getPiece()->getPieceType() == PieceType::BlackKing) || 
            (color == PieceColor::Black && move2->getPiece() != nullptr && move2->getPiece()->getPieceType() == PieceType::WhiteKing)) {
                deliverChecks.push_back(move);
            }
        }
        b->getCell(fromRow, fromCol)->setPiece(this);
        b->getCell(toRow, toCol)->setPiece(old);
        setPosition(fromRow, fromCol);
    }

    validMoves = newValidMoves;
    capturingMoves = oldCapturingMoves;

    // Updates the movesToCapture vector for pawns by making the move, seeing if it causes its king to be in check, 
    // removing it accordingly, and undoing the move
    std::vector<Square *> newMovesToCapture;
    for (size_t idx = 0; idx < movesToCapture.size(); ++idx) {
        auto move = movesToCapture[idx];
        int fromRow = pos->getRow();
        int fromCol = pos->getCol();
        int toRow = move->getRow();
        int toCol = move->getCol();
        b->getCell(fromRow, fromCol)->setPiece(nullptr);
        Piece *old = b->getCell(toRow, toCol)->getPiece();
        b->getCell(toRow, toCol)->setPiece(this);
        setPosition(toRow, toCol);
        if (!king->canBeCapturedIgnoreCheck()) {
            newMovesToCapture.push_back(movesToCapture[idx]);
        }
        b->getCell(fromRow, fromCol)->setPiece(this);
        b->getCell(toRow, toCol)->setPiece(old);
        setPosition(fromRow, fromCol);
    }
    movesToCapture = newMovesToCapture;

    // Updates the capturingMoves vector based off the validMoves vector
    for (size_t i = 0; i < capturingMoves.size(); ++i) {
        for (auto vm = validMoves.begin(); vm != validMoves.end(); ++vm) {
            if (capturingMoves[i] == *vm) { 
                capturingMovesWithCheck.push_back(capturingMoves[i]);
                break;
            }
        }
    }
}

PieceType Piece::getPieceType() const{
    return type;
}

PieceColor Piece::getColor() const{
    return color;
}

Square *Piece::getPosition() const{
    return pos;
}

std::vector <Square *> Piece::getValidMoves() {
    calculateAllMoves();
    filterAllMoves();
    return validMoves;
}

std::vector <Square *> Piece::getCapturingMovesNoCheck() {
    calculateAllMoves();
    return capturingMoves;
}

std::vector <Square *> Piece::getCapturingMoves() {
    calculateAllMoves();
    filterAllMoves();
    return capturingMovesWithCheck;
}

std::vector <Square *> Piece::getDeliverChecks() {
    calculateAllMoves();
    filterAllMoves();
    return deliverChecks;
}

std::vector <Square *> Piece::getMovesToCapture() {
    calculateAllMoves();
    filterAllMoves();
    return movesToCapture;
}

// Checks if piece can be captured by the opposing colour with moves that may or may not caues its king to be in check
bool Piece::canBeCapturedIgnoreCheck() {
    std::vector<Piece *> *list;
    if (color == PieceColor::White) {
        list = b->getBlackPieces()->getPieces();
    } else {
        list = b->getWhitePieces()->getPieces();
    }
    for (auto piece : *list) {
        for (auto moves : piece->getCapturingMovesNoCheck()) {
            if (moves == pos) {
                return true;
            }
        }
    }
    return false;
}

// Checks if piece can be captured by the opposing colour with only valid moves
bool Piece::canBeCaptured() const {
    std::vector<Piece *> *list;
    if (color == PieceColor::White) {
        list = b->getBlackPieces()->getPieces();
    } else {
        list = b->getWhitePieces()->getPieces();
    }
    for (auto piece : *list) {
        for (auto moves : piece->getCapturingMoves()) {
            if (moves == pos) {
                return true;
            }
        }
    }
    return false;
}

bool Piece::getHasMoved() const {
    return hasMoved;
}

void Piece::setPosition(int newrow, int newcol) {
    pos = b->getCell(newrow, newcol);
}

void Piece::setHasMoved(bool val) {
    hasMoved = val;
}

bool Piece::getHasPawnMovedTwo() const {
    return hasPawnMovedTwo;
}

void Piece::setHasPawnMovedTwo(bool b) {
    hasPawnMovedTwo = b;
}

bool Piece::getHasEnPassant() const {
    return hasEnPassant;
}

void Piece::setHasEnPassant(bool b) {
    hasEnPassant = b;
}