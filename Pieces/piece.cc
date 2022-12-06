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
    // std::cout << "Valid Moves of: " << "[" << pos->getRow() << "," << pos->getCol() << "] " << convertPiece(type) << std::endl;
    // for (auto move : validMoves) {
    //     std::cout << "{" << move->getRow() << "," << move->getCol() << "} ";
    // }
    // std::cout << std::endl;
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

    // std::cout << "Valid Moves before filter: " << "[" << pos->getRow() << "," << pos->getCol() << "] " << convertPiece(type) << ":" << std::endl;
    // for (auto move : validMoves) {
    //     std::cout << "{" << move->getRow() << "," << move->getCol() << "} ";
    // }
    // std::cout << std::endl;

    // Update valid moves vector
    // Makes each valid move, checks if move caues king to be in check, removes move accordingly
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
    // calculate moves that can deliver checks
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

    // std::cout << "Valid Moves after filter: " << "[" << pos->getRow() << "," << pos->getCol() << "] " << convertPiece(type) << ":" << std::endl;
    // for (auto move : validMoves) {
    //     std::cout << "{" << move->getRow() << "," << move->getCol() << "} ";
    // }
    // std::cout << std::endl;

    // std::cout << "Capturing Moves No Check: " << "[" << pos->getRow() << "," << pos->getCol() << "] " << convertPiece(type) << ":" << std::endl;
    // for (auto move : capturingMoves) {
    //     std::cout << "{" << move->getRow() << "," << move->getCol() << "} ";
    // }
    // std::cout << std::endl;

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

    // Update capturing moves vector with check
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
    // std::cout << "Capturing Moves Final" << "[" << pos->getRow() << "," << pos->getCol() << "] of: " << convertPiece(type) << std::endl;
    // for (auto move : capturingMovesWithCheck) {
    //     std::cout << "{" << move->getRow() << "," << move->getCol() << "} ";
    // }
    // std::cout << std::endl;
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

bool Piece::canBeCapturedIgnoreCheck() {
    std::vector<Piece *> *list;
    if (color == PieceColor::White) {
        list = b->getBlackPieces()->getPieces();
    } else {
        list = b->getWhitePieces()->getPieces();
    }

    // if ((int) color == 0) {
    //     std::cout << "White Capturing Moves of: " << convertPiece(type) << std::endl;
    // } else {
    //     std::cout << "Black Capturing Moves of: " << convertPiece(type) << std::endl;
    // }
    for (auto piece : *list) {
        // std::cout << "[" << piece->getPosition()->getRow() << "," << piece->getPosition()->getCol() << "]: " << convertPiece(piece->getPieceType()) << ": ";
        for (auto moves : piece->getCapturingMovesNoCheck()) {
            // std::cout << "(" << moves->getRow() << "," << moves->getCol() << "): " << convertPiece(moves->getPiece()->getPieceType()) << "| ";
            if (moves == pos) {
                // std::cout << std::endl;
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