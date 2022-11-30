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

Board::Board() {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; j++) {
            boardlist[i][j] = new Square(i, j, nullptr);
        }
    }
    for (int colour = 0; colour < 2; ++colour) {
        piecelists[colour] = new PieceList(colour);
    }
    this->intializeBoard();
}

void Board::intializeBoard() {
    for (int colour = 0; colour < 2; ++colour) {
        for (int i = 0; i < 8; ++i) {
            Piece* temp = new Pawn((PieceColor) colour, boardlist[colour * 5 + 1][i], colour == 1 ? PieceType::WhitePawn : PieceType::BlackPawn);
            piecelists[colour]->addPiece(temp);
            boardlist[colour * 5 + 1][i]->setPiece(temp);
        }
        for (int i = 0; i < 2; ++i) {
            Piece* temp = new Rook((PieceColor) colour, boardlist[colour * 7][i * 7], colour == 1 ? PieceType::WhiteRook : PieceType::BlackRook);
            piecelists[colour]->addPiece(temp);
            boardlist[colour * 7][i * 7]->setPiece(temp);
            temp = new Knight((PieceColor) colour, boardlist[colour * 7][i * 5 + 1], colour == 1 ? PieceType::WhiteKnight : PieceType::BlackKnight);
            piecelists[colour]->addPiece(temp);
            boardlist[colour * 7][i * 5 + 1]->setPiece(temp);
            temp = new Bishop((PieceColor) colour, boardlist[colour * 7][i * 3 + 2], colour == 1 ? PieceType::WhiteBishop : PieceType::BlackBishop);
            piecelists[colour]->addPiece(temp);
            boardlist[colour * 7][i * 3 + 2]->setPiece(temp);
        }
        Piece *queen = new Queen((PieceColor) colour, boardlist[colour * 7][3], colour == 1 ? PieceType::WhiteQueen : PieceType::BlackQueen);
        Piece *king = new King((PieceColor) colour, boardlist[colour * 7][4], colour == 1 ? PieceType::WhiteKing : PieceType::BlackKing);
        piecelists[colour]->addPiece(queen);
        piecelists[colour]->addPiece(king);
        boardlist[colour * 7][3]->setPiece(queen);
        boardlist[colour * 7][4]->setPiece(king);
    }
}

void Board::resetBoard() {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            delete boardlist[i][j]->getPiece();
            boardlist[i][j]->setPiece(nullptr);
        }
    }
    this->intializeBoard();
}

PieceList* Board::getWhitePieces() {
    return piecelists[0];
}

PieceList* Board::getBlackPieces() {
    return piecelists[1];
}

Square* Board::getCell(int row, int col) {
    return boardlist[row][col];
}

bool Board::addPiece(int row, int col, PieceType piece) {
    if (boardlist[row][col]->getPiece() != nullptr) return false;
    Piece *temp;
    switch (piece) {
        case PieceType::WhiteKing: 
            temp = new King(this, PieceColor::White, boardlist[row][col], piece);
            break;
        case PieceType::BlackKing
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
    return true;
}

void Board::removePiece(int row, int col) {
    Piece* temp = boardlist[row][col]->getPiece();
    boardlist[row][col]->setPiece(nullptr);
    piecelists[(int) temp->getColor()]->removePieces(temp);
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
    