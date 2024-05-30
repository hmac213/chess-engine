#ifndef UNIQUE_PIECE
#define UNIQUE_PIECE

#include <string>

struct Piece {
    int color; // the color is either 0 = white or 1 = black or -1 neither
    std::string name; // "XXX" where each X is 0 or 1 represents the pieces (6 types). 000 is an empty square

    int file; // file of piece
    int rank; // rank of piece

    bool hasMoved; // only important for king + rooks (castling) / pawns (double movement / en passant)
};

/*
Piece names:

000 -> null piece
001 -> pawn
010 -> knight
011 -> bishop
100 -> rook
101 -> queen
110 -> king
*/

#endif // UNIQUE_PIECE