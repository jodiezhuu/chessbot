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

// board constructor
Board::Board() {
    // create the 8x8 Square* array
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; j++) {
            boardlist[i][j] = new Square(i, j, nullptr);
        }
    }
    // create the array of PieceLists
    for (int colour = 0; colour < 2; ++colour) {
        piecelists[colour] = new PieceList((PieceColor) colour);
    }
    // intialize the board with default piece placements
    this->intializeBoard();
}

void Board::intializeBoard() {
    //for each colour
    for (int colour = 0; colour < 2; ++colour) {

        // add Pawns in correct location on board and add to piecelist
        for (int i = 0; i < 8; ++i) {
            Piece* temp = new Pawn(this, (PieceColor) colour, boardlist[colour * 5 + 1][i], colour == 1 ? PieceType::WhitePawn : PieceType::BlackPawn);
            piecelists[colour]->addPiece(temp);
            boardlist[colour * 5 + 1][i]->setPiece(temp);
        }

        // add rooks, knights, and bishops in correct position to board and piecelist
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

        // add queen and king in correct position to board and piecelist
        Piece *queen = new Queen(this, (PieceColor) colour, boardlist[colour * 7][3], colour == 1 ? PieceType::WhiteQueen : PieceType::BlackQueen);
        Piece *king = new King(this, (PieceColor) colour, boardlist[colour * 7][4], colour == 1 ? PieceType::WhiteKing : PieceType::BlackKing);
        piecelists[colour]->addPiece(queen);
        piecelists[colour]->addPiece(king);
        boardlist[colour * 7][3]->setPiece(queen);
        boardlist[colour * 7][4]->setPiece(king);
    }
}

// reset board function
void Board::resetBoard() {
    // loops through the entire boardlist (8x8 Square* array) to remove all pieces from the board and piecelists
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            Piece * piece= boardlist[i][j]->getPiece();
            if (piece == nullptr) continue;
            boardlist[i][j]->setPiece(nullptr);
            piecelists[(int) piece->getColor()]->removePieces(piece);
            delete piece;
        }
    }
    // initalizes board back to default position
    this->intializeBoard();
}

// accessor for the white piecelist
PieceList* Board::getWhitePieces() {
    return piecelists[1];
}

// accessor for the black piecelist
PieceList* Board::getBlackPieces() {
    return piecelists[0];
}

// accessor for cell on the board at the provided row and column
Square* Board::getCell(int row, int col) {
    if (0 <= row && row <= 7 && 0 <= col && col <= 7) {
        return boardlist[row][col];
    }
    return nullptr;
}

// adds a piece to board, returns true if successful, false otherwise
bool Board::addPiece(int row, int col, PieceType piece) {
    // if there is already a piece at the square return false
    if (boardlist[row][col]->getPiece() != nullptr) return false;
    Piece *temp;
    // create a new Piece with the right piecetype
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

    // add the piece to the board and piecelists
    boardlist[row][col]->setPiece(temp);
    int colour = (int) temp->getColor();
    piecelists[colour]->addPiece(temp);
    return true;
}

// removes a piece from the board at the given position
void Board::removePiece(int row, int col) {
    Piece* temp = boardlist[row][col]->getPiece();
    // if there is no piece at the given position return
    if (temp == nullptr) return;
    boardlist[row][col]->setPiece(nullptr);
    piecelists[(int) temp->getColor()]->removePieces(temp);
    delete temp;
}

// removes a given piece from the board
void Board::removePiece(Piece * piece) {
    piecelists[(int) piece->getColor()]->removePieces(piece);
    delete piece;
}

// destructor for Board objects
Board::~Board() {
    // loop through boardlist and delete each Square*
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            delete boardlist[row][col];
        }
    }

    // loop through piecelist and delete each Piece*
    for (int i = 0; i < 2; i++) {
        delete piecelists[i];
    }
}
    
// returns a boolean of whether the state of the board is valid
bool Board::verifyBoard() {
    // no pawns on first or last row of the board
    for (int col = 0; col <= 7; ++col) {
        Piece *piece1 = boardlist[0][col]->getPiece();
        Piece *piece2 = boardlist[7][col]->getPiece();
        if (piece1 != nullptr && (piece1->getPieceType() == PieceType::BlackPawn || piece1->getPieceType() == PieceType::WhitePawn)) {
            return false;
        }
        if (piece2 != nullptr && (piece2->getPieceType() == PieceType::BlackPawn || piece2->getPieceType() == PieceType::WhitePawn)) {
            return false;
        }
    }
    // only one white king and one black king
    if (piecelists[0]->getPieceCount(PieceType::BlackKing) != 1 || piecelists[1]->getPieceCount(PieceType::WhiteKing) != 1) {
        return false;
    }
    // neither king is in check
    if (getBlackKing()->canBeCaptured()) {
        return false;
    }
    if (getWhiteKing()->canBeCaptured()) {
        return false;
    }
    return true;
}

// accessor for white king
Piece *Board::getWhiteKing() {
    for (auto piece : *(piecelists[1]->getPieces())) {
        if (piece->getPieceType() == PieceType::WhiteKing) return piece;
    }
    return nullptr;
}

// accessor for black king
Piece *Board::getBlackKing() {
    for (auto piece : *(piecelists[0]->getPieces())) {
        if (piece->getPieceType() == PieceType::BlackKing) return piece;
    }
    return nullptr;
}