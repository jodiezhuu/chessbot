#include "board.h"

Board::Board() {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; j++) {
            boardlist[i][j] = new Square(i, j, nullptr);
        }
    }
    for (int colour = 0; colour < 2; ++colour) {
        piecelists[colour] = new PieceList();
    }
    for (int colour = 0; colour < 2; ++colour) {
        for (int i = 0; i < 8; ++i) {
            Piece* temp = new Pawn();
            piecelists[colour].addPiece(temp);
            boardlist[colour * 6 + 1][i].setPiece(temp);
        }
        for (int i = 0; i < 2; ++i) {
            Piece* temp = new Rook();
            piecelists[colour].addPiece(temp);
            boardlist[colour * 7][i * 7].setPiece(temp);
            temp = new Knight();
            piecelists[colour].addPiece(temp);
            boardlist[colour * 7][i * 5 + 1].setPiece(temp);
            temp = new Bishop();
            piecelists[colour].addPiece(temp);
            boardlist[colour * 7][i * 3 + 2].setPiece(temp);
        }
        Piece *queen = new Queen();
        Piece *king = new King();
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

    for (int colour = 0; colour < 2; ++colour) {
        for (int i = 0; i < piecelists[colour].getList().size(); ++i) {
            piecelists[colour].getList().pop_back()
        }

        for (int i = 0; i < 8; ++i) {
            Piece* temp = new Pawn();
            piecelists[colour].addPiece(temp);
            boardlist[colour * 6 + 1][i].setPiece(temp);
        }
        for (int i = 0; i < 2; ++i) {
            Piece* temp = new Rook();
            piecelists[colour].addPiece(temp);
            boardlist[colour * 7][i * 7].setPiece(temp);
            temp = new Knight();
            piecelists[colour].addPiece(temp);
            boardlist[colour * 7][i * 5 + 1].setPiece(temp);
            temp = new Bishop();
            piecelists[colour].addPiece(temp);
            boardlist[colour * 7][i * 3 + 2].setPiece(temp);
        }
        Piece *queen = new Queen();
        Piece *king = new King();
        piecelists[colour].addPiece(queen);
        piecelists[colour].addPiece(king);
        boardlist[colour * 7][3].setPiece(queen);
        boardlist[colour * 7][3].setPiece(king);
    }
}

PieceList[] Board::getPieceLists() {
    return piecelists;
}

Square[][] Board::getBoard() {
    return boardlist;
}

bool Board::addPiece(int row, int col, Piece* piece) {
    if (boardlist[row][col].getPiece != nullptr) return false;
    boardlist[row][col].setPiece(piece);
    return true;
}

void Board::removePiece(int row, int col) {
    boardlist[row][col].setPiece(nullptr);
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
    