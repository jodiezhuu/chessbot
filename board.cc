#include "board.h"
#include "piecelist.h"
#include "piececolor.h"
#include "piece.h"
#include "bishop.h"
#include "king.h"
#include "knight.h"
#include "queen.h"
#include "pawn.h"
#include "rook.h"

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

bool Board::addPiece(int row, int col, Piece* piece) {
    if (boardlist[row][col]->getPiece() != nullptr) return false;
    boardlist[row][col]->setPiece(piece);
    int colour = (int) piece->getColor();
    piecelists[colour]->addPiece(piece);
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
    