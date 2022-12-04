#include "piece.h"
#include "piecelist.h"
#include <iostream>

Piece::Piece(Board *b, PieceColor color, Square *pos, PieceType type, bool hasMoved): b{b}, color{color}, pos{pos}, type{type}, hasMoved{hasMoved} {}

Piece::~Piece() {}

char Piece::convertPiece(PieceType type) {
    if (type == PieceType::BlackBishop) {
        return 'b';
    } else if (type == PieceType::BlackKing) {
        return 'k';
    } else if (type == PieceType::BlackKnight) {
        return 'n';
    } else if (type == PieceType::BlackPawn) {
        return 'p';
    } else if (type == PieceType::BlackQueen) {
        return 'q';
    } else if (type == PieceType::BlackRook) {
        return 'r';
    } else if (type == PieceType::Empty) {
        return ' ';
    } else if (type == PieceType::WhiteBishop) {
        return 'B';
    } else if (type == PieceType::WhiteKing) {
        return 'K';
    } else if (type == PieceType::WhiteKnight) {
        return 'N';
    } else if (type == PieceType::WhitePawn) {
        return 'P';
    } else if (type == PieceType::WhiteQueen) {
        return 'Q';
    } else if (type == PieceType::WhiteRook) {
        return 'R';
    }
}

bool Piece::inBound(int row, int col) {
    return (0 <= row && row <= 7 && 0 <= col && col <= 7);
}

bool Piece::isMoveValid(int row, int col) {
    calculateAllMoves();
    filterAllMoves();
    std::cout << "Valid Moves of: " << "[" << pos->getRow() << "," << pos->getCol() << "] " << convertPiece(type) << std::endl;
    for (auto move : validMoves) {
        std::cout << "{" << move->getRow() << "," << move->getCol() << "} ";
    }
    std::cout << std::endl;
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
    // Makes each valid move, checks if move caues king to be in check, removes move accordingly
    int toRemove = 0;
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
        if (king->canBeCapturedIgnoreCheck()) {
            validMoves[idx] = validMoves.back();
            toRemove++;
        }
        b->getCell(fromRow, fromCol)->setPiece(this);
        b->getCell(toRow, toCol)->setPiece(old);
        setPosition(fromRow, fromCol);
    }
    for (int j = 0; j < toRemove; ++j) {
        validMoves.pop_back();
    }

    // Update capturing moves vector with check
    for (size_t i = 0; i < capturingMoves.size(); ++i) {
        bool inValid = true;
        for (auto vm = validMoves.begin(); vm != validMoves.end(); ++vm) {
            if (capturingMoves[i] == *vm) inValid = false;
        }
        if (!inValid) {
            capturingMovesWithCheck.push_back(capturingMoves[i]);
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

bool Piece::canBeCapturedIgnoreCheck() {
    std::vector<Piece *> *list;
    if (color == PieceColor::White) {
        list = b->getBlackPieces()->getPieces();
    } else {
        list = b->getWhitePieces()->getPieces();
    }

    // if ((int) color == 0) {
    //     std::cout << "White Capturing Moves: " << std::endl;
    // } else {
    //     std::cout << "Black Capturing Moves: " << std::endl;
    // }
    for (auto piece : *list) {
        // std::cout << "[" << piece->getPosition()->getRow() << "," << piece->getPosition()->getCol() << "]: " << (int) piece->getPieceType() << ": ";
        for (auto moves : piece->getCapturingMovesNoCheck()) {
            // std::cout << "(" << moves->getRow() << "," << moves->getCol() << ") ";
            if (moves == pos) {
                return true;
            }
        }
        // std::cout << std::endl;
    }
    return false;
}

bool Piece::canBeCaptured() const {
    std::vector<Piece *> *list;
    if (color == PieceColor::White) {
        list = b->getBlackPieces()->getPieces();
    } else {
        list = b->getWhitePieces()->getPieces();
    }

    // if ((int) color == 0) {
    //     std::cout << "White Capturing Moves: " << std::endl;
    // } else {
    //     std::cout << "Black Capturing Moves: " << std::endl;
    // }
    for (auto piece : *list) {
        // std::cout << "[" << piece->getPosition()->getRow() << "," << piece->getPosition()->getCol() << "]: " << (int) piece->getPieceType() << ": ";
        for (auto moves : piece->getCapturingMoves()) {
            // std::cout << "(" << moves->getRow() << "," << moves->getCol() << ") ";
            if (moves == pos) {
                return true;
            }
        }
        // std::cout << std::endl;
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