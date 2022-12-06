#include "graphicview.h"
#include <string>

// constructor displays empty 8x8 board by default
GraphicView::GraphicView(Game *game): game {game}, window{575, 650} {
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            pieceBoard[row][col] = PieceType::Empty;
        }
    }
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            if ((row + col) % 2 == 0) {
                window.fillRectangle(row * 62, col * 62, 62, 62, 8);
            } else {                
                window.fillRectangle(row * 62, col * 62, 62, 62, 9);
            }
        }
    }
    int rowCount = 8;
    for (int row = 40; row < 475; row += 62) {
        window.drawBiggerString(510, row, std::to_string(rowCount));
        rowCount--;
        if (rowCount == 0) break;
    }
    window.drawBiggerString(20, 530, "a     b     c     d     e     f     g     h");
    game->attach(this);
}

GraphicView::~GraphicView() {
    game->detach(this);
}

// draws a circle with piecetype symbol on the piece
void GraphicView::drawPiece(PieceType type, int x, int y) {
    if (type == PieceType::BlackBishop) {
        window.drawCircle(x, y, 40, 1);
        window.drawString(x, y, "b", 0);
    } else if (type == PieceType::BlackKing) {
        window.drawCircle(x, y, 40, 1);
        window.drawString(x, y, "k", 0);
    } else if (type == PieceType::BlackKnight) {
        window.drawCircle(x, y, 40, 1);
        window.drawString(x, y, "n", 0);
    } else if (type == PieceType::BlackPawn) {
        window.drawCircle(x, y, 40, 1);
        window.drawString(x, y, "p", 0);
    } else if (type == PieceType::BlackQueen) {
        window.drawCircle(x, y, 40, 1);
        window.drawString(x, y, "q", 0);
    } else if (type == PieceType::BlackRook) {
        window.drawCircle(x, y, 40, 1);
        window.drawString(x, y, "r", 0);
    } else if (type == PieceType::Empty) {
        if ((x + y) % 2 == 0) {
            window.fillRectangle(x * 62, y * 62, 62, 62, 8);
        } else {               
            window.fillRectangle(x * 62, y * 62, 62, 62, 9);
        }
    } else if (type == PieceType::WhiteBishop) {
        window.drawCircle(x, y, 40, 0);
        window.drawString(x, y, "B", 1);
    } else if (type == PieceType::WhiteKing) {
        window.drawCircle(x, y, 40, 0);
        window.drawString(x, y, "K", 1);
    } else if (type == PieceType::WhiteKnight) {
        window.drawCircle(x, y, 40, 0);
        window.drawString(x, y, "N", 1);
    } else if (type == PieceType::WhitePawn) {
        window.drawCircle(x, y, 40, 0);
        window.drawString(x, y, "P", 1);
    } else if (type == PieceType::WhiteQueen) {
        window.drawCircle(x, y, 40, 0);
        window.drawString(x, y, "Q", 1);
    } else if (type == PieceType::WhiteRook) {
        window.drawCircle(x, y, 40, 0);
        window.drawString(x, y, "R", 1);
    }
}

// draws message in display based on inputted string
void GraphicView::displayMessage(std::string s) {
    window.fillRectangle(0, 540, 575, 175, 0);
    window.drawBiggerString(10, 590, s);
}

// clears message in display
void GraphicView::clearMessage() {
    window.fillRectangle(0, 540, 575, 175, 0);
}

// renders and updates board based on moved pieces
void GraphicView::notify() {
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            if (pieceBoard[row][col] != game->getState(row, col)) {
                if (game->getState(row, col) == PieceType::Empty) {
                    drawPiece(game->getState(row, col), col, row);
                    pieceBoard[row][col] = game->getState(row, col);
                } else {
                    drawPiece(game->getState(row, col), col * 62 + 30, row * 62 + 30);
                    pieceBoard[row][col] = game->getState(row, col);
                }
            }
        }
    }
}