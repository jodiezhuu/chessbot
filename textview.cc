#include "textview.h"

TextView::TextView(Game *game): game{game} {
    game->attach(this);
}

TextView::~TextView() {
    game->detach(this);
}

char TextView::convertPiece(PieceType type) {
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

void TextView::notify() {
    int rowDisplay = 8;

    out << "   ";
    for (int col = 0; col < 8; ++col) {
        out << '-';
    }
    for (int row = 0; row < 8; ++row) {
        out << rowDisplay-- << " |";
        for (int col = 0; col < 8; ++col) {
            out << game->getState(row, col) << "|";
        }
    }
    out << "-----------";
    out << "           ";
    out << "   abcdefgh";
}