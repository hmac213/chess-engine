#ifndef UNIQUE_MOVE
#define UNIQUE_MOVE

#include <string>

struct Move {
    Piece piece;
    int color;
    char name;
    int startRank;
    int startFile;
    int toRank;
    int toFile;
    int didTake;
    std::string moveString;

    Move(Piece movePiece, int moveToRank, int moveToFile, int moveDidTake) {
        piece = movePiece;
        color = movePiece.color;
        name = movePiece.name;
        startRank = movePiece.rank;
        startFile = movePiece.file;
        toRank = moveToRank;
        toFile = moveToFile;
        didTake = moveDidTake;
        moveString = std::to_string(movePiece.color) + movePiece.name + std::to_string(movePiece.rank) + std::to_string(movePiece.file) + std::to_string(moveToRank) + std::to_string(moveToFile) + std::to_string(moveDidTake);
    }
};

#endif // UNIQUE_PIECE