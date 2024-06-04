#ifndef UNIQUE_PIECE
#define UNIQUE_PIECE

struct Piece {
    int color; // the color is either 0 = white or 1 = black or -1 neither
    char name;

    int file; // file of piece
    int rank; // rank of piece

    bool hasMoved; // only important for king + rooks (castling) / pawns (double movement)
    bool pawnDoubleJump; // only important for en passant ---> MAKE SURE TO SET FALSE ONE MOVE AFTER THE DOUBLE JUMP HAS BEEN PERFORMED (en passant must happen immediately)
};

/*
Piece names:

e -> null piece
p -> pawn
n -> knight
b -> bishop
r -> rook
q -> queen
k -> king
*/

#endif // UNIQUE_PIECE