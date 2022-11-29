#include "board.h"
#include "piececolor.h"

Board::Board() {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; j++) {
            boardlist[i][j] = new Square(i, j, nullptr);
        }
    }
    for (int colour = 0; colour < 2; ++colour) {
        piecelists[colour] = new PieceList();
    }
    this->intializeBoard();
}

void Board::intializeBoard() {
    for (int colour = 0; colour < 2; ++colour) {
        for (int i = 0; i < 8; ++i) {
            Piece* temp = new Pawn(colour);
            piecelists[colour].addPiece(temp);
            boardlist[colour * 5 + 1][i].setPiece(temp);
        }
        for (int i = 0; i < 2; ++i) {
            Piece* temp = new Rook(colour);
            piecelists[colour].addPiece(temp);
            boardlist[colour * 7][i * 7].setPiece(temp);
            temp = new Knight(colour);
            piecelists[colour].addPiece(temp);
            boardlist[colour * 7][i * 5 + 1].setPiece(temp);
            temp = new Bishop(colour);
            piecelists[colour].addPiece(temp);
            boardlist[colour * 7][i * 3 + 2].setPiece(temp);
        }
        Piece *queen = new Queen(colour);
        Piece *king = new King(colour);
        piecelists[colour].addPiece(queen);
        piecelists[colour].addPiece(king);
        boardlist[colour * 7][3].setPiece(queen);
        boardlist[colour * 7][3].setPiece(king);
    }
}

void Board::resetBoard() {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            delete boardlist[i][j].getPiece();
            boardlist[i][j].setPiece(null);
        }
    }
    this->intializeBoard();
}

PieceList* Board::getWhitePieces() {
    return &piecelists[0];
}

PieceList* Board::getBlackPieces() {
    return &piecelists[1];
}

Square* Board::getCell(int row, int col) {
    return &boardlist[row][col];
}

bool Board::addPiece(int row, int col, Piece* piece) {
    if (boardlist[row][col].getPiece != nullptr) return false;
    boardlist[row][col].setPiece(piece);
    PieceColor colour = piece->getColor();
    piecelists[colour].addPiece(piece);
    return true;
}

void Board::removePiece(int row, int col) {
    Piece* temp = boardlist[row][col].getPiece();
    boardlist[row][col].setPiece(nullptr);
    piecelists[temp->getColor()].removePiece(temp);
}

Board::~Board() {
    for (int i = 0; i < 8; ++i) {
        delete [] boardlist[i];
    }
    delete boardlist;
    for (int i = 0; i < 2; i++) {
        delete piecelists[i];
    }
}
    