#ifndef UNIQUE_BOARD
#define UNIQUE_BOARD

#include <iostream>
#include <string>
#include <vector>

#include "piece.h"
#include "move.h"

class Board {
    public:
        Board(bool visualBoard);

        ~Board();

        int colorTurn();

        std::vector<Move> boardMoves(std::vector<std::string>* activePieces, int color); // can return null pointer to detect checkmate or stalemate

        void move(Piece piece, int toRank, int toFile); // update active pieces after the move is done

        void updateBoard();

        // functions for a visual board

        void runVisualGame();

    private:
        Piece board[8][8];
        std::vector<Move> validMoves;
        std::vector<std::string> activePieces;
        int playerTurn;
};

#endif // UNIQUE_BOARD