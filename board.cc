#include "board.h"
#include "Pieces/piecelist.h"
#include "Pieces/piececolor.h"
#include "Pieces/piecetype.h"
#include "Pieces/piece.h"
#include "Pieces/bishop.h"
#include "Pieces/king.h"
#include "Pieces/knight.h"
#include "Pieces/queen.h"
#include "Pieces/pawn.h"
#include "Pieces/rook.h"
#include <iostream>

Board::Board() {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; j++) {
            boardlist[i][j] = new Square(i, j, nullptr);
        }
    }
    for (int colour = 0; colour < 2; ++colour) {
        piecelists[colour] = new PieceList((PieceColor) colour);
    }
    this->intializeBoard();
}

void Board::intializeBoard() {
    for (int colour = 0; colour < 2; ++colour) {
        for (int i = 0; i < 8; ++i) {
            Piece* temp = new Pawn(this, (PieceColor) colour, boardlist[colour * 5 + 1][i], colour == 1 ? PieceType::WhitePawn : PieceType::BlackPawn);
            piecelists[colour]->addPiece(temp);
            boardlist[colour * 5 + 1][i]->setPiece(temp);
        }
        for (int i = 0; i < 2; ++i) {
            Piece* temp = new Rook(this, (PieceColor) colour, boardlist[colour * 7][i * 7], colour == 1 ? PieceType::WhiteRook : PieceType::BlackRook);
            piecelists[colour]->addPiece(temp);
            boardlist[colour * 7][i * 7]->setPiece(temp);
            temp = new Knight(this, (PieceColor) colour, boardlist[colour * 7][i * 5 + 1], colour == 1 ? PieceType::WhiteKnight : PieceType::BlackKnight);
            piecelists[colour]->addPiece(temp);
            boardlist[colour * 7][i * 5 + 1]->setPiece(temp);
            temp = new Bishop(this, (PieceColor) colour, boardlist[colour * 7][i * 3 + 2], colour == 1 ? PieceType::WhiteBishop : PieceType::BlackBishop);
            piecelists[colour]->addPiece(temp);
            boardlist[colour * 7][i * 3 + 2]->setPiece(temp);
        }
        Piece *queen = new Queen(this, (PieceColor) colour, boardlist[colour * 7][3], colour == 1 ? PieceType::WhiteQueen : PieceType::BlackQueen);
        Piece *king = new King(this, (PieceColor) colour, boardlist[colour * 7][4], colour == 1 ? PieceType::WhiteKing : PieceType::BlackKing);
        piecelists[colour]->addPiece(queen);
        piecelists[colour]->addPiece(king);
        boardlist[colour * 7][3]->setPiece(queen);
        boardlist[colour * 7][4]->setPiece(king);
    }
    std::cout << "black: " << piecelists[0]->getLength() << " white: " << piecelists[1]->getLength() << std::endl;
}

void Board::resetBoard() {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            Piece * piece= boardlist[i][j]->getPiece();
            if (piece == nullptr) continue;
            boardlist[i][j]->setPiece(nullptr);
            piecelists[(int) piece->getColor()]->removePieces(piece);
            delete piece;
        }
    }
    this->intializeBoard();
}

PieceList* Board::getWhitePieces() {
    return piecelists[1];
}

PieceList* Board::getBlackPieces() {
    return piecelists[0];
}

Square* Board::getCell(int row, int col) {
    return boardlist[row][col];
}

bool Board::addPiece(int row, int col, PieceType piece) {
    std::cout << "adding piece in board" << std::endl;
    if (boardlist[row][col]->getPiece() != nullptr) return false;
    Piece *temp;
    switch (piece) {
        case PieceType::WhiteKing: 
            temp = new King(this, PieceColor::White, boardlist[row][col], piece);
            break;
        case PieceType::BlackKing:
            temp = new King(this, PieceColor::Black, boardlist[row][col], piece);
            break;
        case PieceType::WhiteQueen:
            temp = new Queen(this, PieceColor::White, boardlist[row][col], piece);
            break;
        case PieceType::BlackQueen:
            temp = new Queen(this, PieceColor::Black, boardlist[row][col], piece);
            break;
        case PieceType::WhiteRook:
            temp = new Rook(this, PieceColor::White, boardlist[row][col], piece);
            break;
        case PieceType::BlackRook:
            temp = new Rook(this, PieceColor::Black, boardlist[row][col], piece);
            break;
        case PieceType::WhiteKnight:
            temp = new Knight(this, PieceColor::White, boardlist[row][col], piece);
            break;
        case PieceType::BlackKnight:
            temp = new Knight(this, PieceColor::Black, boardlist[row][col], piece);
            break;
        case PieceType::WhiteBishop:
            temp = new Bishop(this, PieceColor::White, boardlist[row][col], piece);
            break;
        case PieceType::BlackBishop:
            temp = new Bishop(this, PieceColor::Black, boardlist[row][col], piece);
            break;
        case PieceType::WhitePawn:
            temp = new Pawn(this, PieceColor::White, boardlist[row][col], piece);
            break;
        case PieceType::BlackPawn:
            temp = new Pawn(this, PieceColor::Black, boardlist[row][col], piece);
            break;
        default:
            return false;
    }
    boardlist[row][col]->setPiece(temp);
    int colour = (int) temp->getColor();
    piecelists[colour]->addPiece(temp);
    std::cout << "black: " << piecelists[0]->getLength() << " white: " << piecelists[1]->getLength() << std::endl;
    return true;
}

void Board::removePiece(int row, int col) {
    Piece* temp = boardlist[row][col]->getPiece();
    if (temp == nullptr) return;
    boardlist[row][col]->setPiece(nullptr);
    piecelists[(int) temp->getColor()]->removePieces(temp);
    std::cout << (int) temp->getPieceType() << " and " << (int) temp->getColor() << std::endl;
    delete temp;
    std::cout << "black: " << piecelists[0]->getLength() << " white: " << piecelists[1]->getLength() << std::endl;
}

void Board::removePiece(Piece * piece) {
    piecelists[(int) piece->getColor()]->removePieces(piece);
    delete piece;
    std::cout << "black: " << piecelists[0]->getLength() << " white: " << piecelists[1]->getLength() << std::endl;
}

Board::~Board() {
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            delete boardlist[row][col];
        }
    }
    for (int i = 0; i < 2; i++) {
        delete piecelists[i];
    }
}
    

bool Board::verifyBoard() {
    // no pawns on first or last row of the board
    for (int col = 0; col <= 7; ++col) {
        Piece *piece1 = boardlist[0][col]->getPiece();
        Piece *piece2 = boardlist[7][col]->getPiece();
        if (piece1 != nullptr && (piece1->getPieceType() == PieceType::BlackPawn || piece1->getPieceType() == PieceType::WhitePawn)) {
            std::cout << "pawn found on top row" << std::endl;
            return false;
        }
        if (piece2 != nullptr && (piece2->getPieceType() == PieceType::BlackPawn || piece2->getPieceType() == PieceType::WhitePawn)) {
            std::cout << "pawn found on bottom row" << std::endl;
            return false;
        }
    }
    // only one white king and one black king
    if (piecelists[0]->getPieceCount(PieceType::BlackKing) != 1 || piecelists[1]->getPieceCount(PieceType::WhiteKing) != 1) {
        std::cout << "black king: " << piecelists[0]->getPieceCount(PieceType::BlackKing) << std::endl;
        std::cout << "white king: " << piecelists[1]->getPieceCount(PieceType::WhiteKing) << std::endl;
        std::cout << "not exactly one king each" << std::endl;
        return false;
    }
    // neither king is in check
    if (getBlackKing()->canBeCaptured()) {
        std::cout << "black king is in check" << std::endl;
        return false;
    }
    if (getWhiteKing()->canBeCaptured()) {
        std::cout << "white king is in check" << std::endl;
        return false;
    }
    std::cout << "ALL GOOD :)" << std::endl;
    return true;
}

Piece *Board::getWhiteKing() {
    for (auto piece : *(piecelists[1]->getPieces())) {
        if (piece->getPieceType() == PieceType::WhiteKing) return piece;
    }
    return nullptr;
}

Piece *Board::getBlackKing() {
    for (auto piece : *(piecelists[0]->getPieces())) {
        if (piece->getPieceType() == PieceType::BlackKing) return piece;
    }
    return nullptr;
}