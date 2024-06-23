#include <algorithm>
#include <SDL.h>
#include <SDL_image.h>  

#include "board.h"

Board::Board(bool visualBoard) {
    // initialize all files and ranks

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            board[i][j].file = j;
            board[i][j].rank = i;
        }
    }

    // initialize empty squares
    for (int i = 2; i < 6; ++i) {
        for (int j = 0; j < 8; ++j) {
            board[i][j].color = -1;
            board[i][j].name = 'e';
        }
    }

    // initialize white pawns

    for (int i = 0; i < 8; ++i) {
        board[1][i].color = 0;
        board[1][i].name = 'p';
    }

    // initialize black pawns

    for (int i = 0; i < 8; ++i) {
        board[6][i].color = 1;
        board[6][i].name = 'p';
    }

    // initialize white pieces

    for (int i = 0; i < 8; ++i) {
        board[0][i].color = 0;
    }
    
    board[0][0].name = 'r';
    board[0][7].name = 'r';
    board[0][1].name = 'n';
    board[0][6].name = 'n';
    board[0][2].name = 'b';
    board[0][5].name = 'b';
    board[0][3].name = 'q';
    board[0][4].name = 'k';

    // initialize black pieces

    for (int i = 0; i < 8; ++i) {
        board[7][i].color = 1;
    }

    board[7][0].name = 'r';
    board[7][7].name = 'r';
    board[7][1].name = 'n';
    board[7][6].name = 'n';
    board[7][2].name = 'b';
    board[7][5].name = 'b';
    board[7][3].name = 'q';
    board[7][4].name = 'k';

    // always starts with white's turn

    playerTurn = 0;

    if (visualBoard == true) {
        runVisualGame();
    }
}

std::vector<Move> Board::boardMoves(std::vector<std::string>* activePieces, int color) {

    /*
    
    Moves are going to be implemented with strings:

    First two characters, PIECE COLOR (1) + PIECE NAME (1)
    Next two characters, RANK FROM (1) + FILE FROM (1)
    Next two characters, RANK TO (1) + FILE TO (1)
    Last Character, Is it a take -> 0 no, 1 yes ----> STILL NEED TO SEE IF NEEDED

    OVERALL: 7 Characters

    example would be: 0p10211 -> white pawn goes from (1,0) to (2,1), while taking

    */

    for (const auto& rank : board) {
        for (const auto& piece : rank) {
            int curRank = piece.rank;
            int curFile = piece.file;

            if (piece.name == 'e') {
                return ;
            }

            /*
            Implementation of searching for valid pawn moves. Things to include:
            - Has not moved -> 1 or 2 space advance, diagonal take
            - Has moved -> 1 space advance, diagonal take
            - Special cases:
                - Promotion: How do we do piece conversion (default: Queen)
                - En Passant: Skip-take on a pawn that has jumped two from default square
            */

            if (piece.name == 'p') {
                // double jumps for unmoved pawns

                if (piece.hasMoved == false) {
                    if (color == 0) {
                        if (board[curRank + 1][curFile].name == 'e' && board[curRank + 2][curFile].name == 'e') {
                            validMoves.push_back(Move(board[curRank][curFile], curRank + 2, curFile, 0));
                        }
                    } else {
                        if (board[curRank - 1][curFile].name == 'e' && board[curRank - 2][curFile].name == 'e') {
                            validMoves.push_back(Move(board[curRank][curFile], curRank - 2, curFile, 0));
                        }
                    }
                }

                // single jumps for any pawn

                if (color == 0) {
                    if (curRank < 7) {
                        if (board[curRank + 1][curFile].name == 'e') {
                            validMoves.push_back(Move(board[curRank][curFile], curRank + 1, curFile, 0));
                        }
                    }
                } else {
                    if (curRank > 0) {
                        if (board[curRank - 1][curFile].name == 'e') {
                            validMoves.push_back(Move(board[curRank][curFile], curRank - 1, curFile, 0));
                        }
                    }
                }

                // takes for any pawn

                if (color == 0) {
                    if (curFile > 0) {
                        if (board[curRank + 1][curFile - 1].color == 1) {
                            validMoves.push_back(Move(board[curRank][curFile], curRank + 1, curFile - 1, 1));
                        }
                    }

                    if (curFile < 7) {
                        if (board[curRank + 1][curFile + 1].color == 1) {
                            validMoves.push_back(Move(board[curRank][curFile], curRank + 1, curFile + 1, 1));
                        }
                    }
                } else {
                    if (curFile > 0) {
                        if (board[curRank - 1][curFile - 1].color == 0) {
                            validMoves.push_back(Move(board[curRank][curFile], curRank - 1, curFile - 1, 1));
                        }
                    }

                    if (curFile < 7) {
                        if (board[curRank - 1][curFile + 1].color == 0) {
                            validMoves.push_back(Move(board[curRank][curFile], curRank - 1, curFile + 1, 1));
                        }
                    }
                }

                // en passant for valid pawns

                if (color == 0) {
                    if (curFile > 0) {
                        if (curRank == 4 && board[curRank][curFile - 1].name == 'p' && board[curRank][curFile - 1].color == 1 && board[curRank][curFile - 1].pawnDoubleJump == true) {
                            validMoves.push_back(Move(board[curRank][curFile], curRank + 1, curFile - 1, 1));
                        }
                    }

                    if (curFile < 7) {
                        if (curRank == 4 && board[curRank][curFile + 1].name == 'p' && board[curRank][curFile + 1].color == 1 && board[curRank][curFile + 1].pawnDoubleJump == true) {
                            validMoves.push_back(Move(board[curRank][curFile], curRank + 1, curFile + 1, 1));
                        }
                    }
                } else {
                    if (curFile > 0) {
                        if (curRank == 3 && board[curRank][curFile - 1].name == 'p' && board[curRank][curFile - 1].color == 1 && board[curRank][curFile - 1].pawnDoubleJump == true) {
                            validMoves.push_back(Move(board[curRank][curFile], curRank - 1, curFile - 1, 1));
                        }
                    }

                    if (curFile < 7) {
                        if (curRank == 3 && board[curRank][curFile + 1].name == 'p' && board[curRank][curFile + 1].color == 1 && board[curRank][curFile + 1].pawnDoubleJump == true) {
                            validMoves.push_back(Move(board[curRank][curFile], curRank - 1, curFile + 1, 1));
                        }
                    }
                }

                // promotion for valid pawns ---> DONT WRITE YET, SHOULD IMPLEMENT IN MOVE() FUNCTION INSTEAD

                if (color == 0) {

                } else {
                    
                }
            }

            if (piece.name == 'n') {
                std::vector<std::pair<int, int>> targetSquares;

                auto addTargetSquare = [&](int rank, int file) {
                    if (rank > -1 && rank < 8 && file > -1 && file < 8) {
                        targetSquares.emplace_back(rank, file);
                    }
                };

                addTargetSquare(curRank + 1, curFile + 2);
                addTargetSquare(curRank + 1, curFile - 2);
                addTargetSquare(curRank - 1, curFile + 2);
                addTargetSquare(curRank - 1, curFile - 2);
                addTargetSquare(curRank + 2, curFile + 1);
                addTargetSquare(curRank + 2, curFile - 1);
                addTargetSquare(curRank - 2, curFile + 1);
                addTargetSquare(curRank - 2, curFile - 1);

                for (const auto& square : targetSquares) {
                    int toRank = square.first;
                    int toFile = square.second;

                    if (board[toRank][toFile].color == -1) {
                        validMoves.push_back(Move(board[curRank][curFile], toRank, toFile, 0));
                    } else if (board[toRank][toFile].color != board[curRank][curFile].color) {
                        validMoves.push_back(Move(board[curRank][curFile], toRank, toFile, 1));
                    }
                }
            }

            if (piece.name == 'b') {
                std::vector<std::pair<int, int>> moveDirections = { {1, 1}, {1, -1}, {-1, 1}, {-1, -1} };

                auto searchTargetSquare = [&](std::pair<int, int> direction, int checkRank, int checkFile) {
                    if (board[checkRank + direction.first][checkFile + direction.second].color == -1) {
                        validMoves.push_back(Move(board[curRank][curFile], checkRank + direction.first, checkFile + direction.second, 0));
                    } else if (board[checkRank + direction.first][checkFile + direction.second].color != board[curRank][curFile].color) {
                        validMoves.push_back(Move(board[curRank][curFile], checkRank + direction.first, checkFile + direction.second, 1));
                    }
                };

                for (const auto& direction : moveDirections) {
                    int checkRank = curRank;
                    int checkFile = curFile;

                    bool keepChecking = true;

                    while (keepChecking) {
                        if (checkRank > 7 || checkRank < 0 || checkFile > 7 || checkFile < 0 || board[checkRank][checkFile].color == board[curRank][curFile].color) {
                            keepChecking = false;
                            break;
                        }

                        searchTargetSquare(direction, checkRank, checkFile);
                        checkRank += direction.first;
                        checkFile += direction.second;
                    }
                }
            }

            if (piece.name == 'r') {
                std::vector<std::pair<int, int>> moveDirections = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };

                auto searchTargetSquare = [&](std::pair<int, int> direction, int checkRank, int checkFile) {
                    if (board[checkRank + direction.first][checkFile + direction.second].color == -1) {
                        validMoves.push_back(Move(board[curRank][curFile], checkRank + direction.first, checkFile + direction.second, 0));
                    } else if (board[checkRank + direction.first][checkFile + direction.second].color != board[curRank][curFile].color) {
                        validMoves.push_back(Move(board[curRank][curFile], checkRank + direction.first, checkFile + direction.second, 1));
                    }
                };

                for (const auto& direction : moveDirections) {
                    int checkRank = curRank;
                    int checkFile = curFile;

                    bool keepChecking = true;

                    while (keepChecking) {
                        if (checkRank > 7 || checkRank < 0 || checkFile > 7 || checkFile < 0 || board[checkRank][checkFile].color == board[curRank][curFile].color) {
                            keepChecking = false;
                            break;
                        }

                        searchTargetSquare(direction, checkRank, checkFile);
                        checkRank += direction.first;
                        checkFile += direction.second;
                    }
                }
            }

            if (piece.name == 'q') {
                std::vector<std::pair<int, int>> moveDirections = { {1, 1}, {1, -1}, {-1, 1}, {-1, -1}, {1, 0}, {-1, 0}, {0, 1}, {0, -1} };

                auto searchTargetSquare = [&](std::pair<int, int> direction, int checkRank, int checkFile) {
                    if (board[checkRank + direction.first][checkFile + direction.second].color == -1) {
                        validMoves.push_back(Move(board[curRank][curFile], checkRank + direction.first, checkFile + direction.second, 0));
                    } else if (board[checkRank + direction.first][checkFile + direction.second].color != board[curRank][curFile].color) {
                        validMoves.push_back(Move(board[curRank][curFile], checkRank + direction.first, checkFile + direction.second, 1));
                    }
                };

                for (const auto& direction : moveDirections) {
                    int checkRank = curRank;
                    int checkFile = curFile;

                    bool keepChecking = true;

                    while (keepChecking) {
                        if (checkRank > 7 || checkRank < 0 || checkFile > 7 || checkFile < 0 || board[checkRank][checkFile].color == board[curRank][curFile].color) {
                            keepChecking = false;
                            break;
                        }

                        searchTargetSquare(direction, checkRank, checkFile);
                        checkRank += direction.first;
                        checkFile += direction.second;
                    }
                }
            }

            if (piece.name == 'k') {

            }
        }
    }

    for (const auto& move : validMoves) {
        
    }

    return validMoves;
}

// still need to handle pawn promotion, checks, castling

void Board::move(Piece piece, int toRank, int toFile) {
    std::string moveString = std::to_string(piece.color) + piece.name + std::to_string(piece.rank) + std::to_string(piece.file) + std::to_string(toRank) + std::to_string(toFile);
    if (playerTurn == piece.color) {
        if (std::find(validMoves.begin(), validMoves.end(), moveString + '0') != validMoves.end() || std::find(validMoves.begin(), validMoves.end(), moveString + '1') != validMoves.end()) {
            board[piece.rank][piece.file].color = -1;
            board[piece.rank][piece.file].name = 'e';
            board[piece.rank][piece.file].hasMoved = false;
            board[piece.rank][piece.file].pawnDoubleJump = false;

            board[toRank][toFile] = piece;

            if (playerTurn == 0) {
                playerTurn = 1;
            } else {
                playerTurn = 0;
            }

            return;
        }
    }

    // IMPLEMENT LOGIC FOR WHAT TO DO IF A MOVE IS NOT VALID. Likely will only need this for human input on the graphical board.

}

// void Board::updateBoard() {

// }

// running a graphical game

void Board::runVisualGame() {
    int imgFlags = IMG_INIT_PNG;

    const int SCREEN_WIDTH = 1100;
    const int SCREEN_HEIGHT = 800;
    const int SQUARE_SIZE = 100;
    const int PIECE_SIZE = 60;

    SDL_Window* window;
    SDL_Renderer* render;
    SDL_Surface* surface;
    SDL_Texture* pieceTextures[8][8];
    
    std::vector<std::string> imgPaths = { "0p", "0n", "0b", "0r", "0q", "0k", "1p", "1n", "1b", "1r", "1q", "1k" };

    if (SDL_Init(SDL_INIT_EVERYTHING != 0)) {
        std::cout << "There has been an error: " << SDL_GetError() << std::endl;
        return;
    } else {
        window = SDL_CreateWindow("Chess", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        surface = SDL_GetWindowSurface(window);

        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                Uint32 squareColor;
                int squareX;
                int squareY;
                if ((i + j) % 2 == 0) {
                    squareColor = SDL_MapRGB(surface->format, 240, 217, 181); // light
                } else {
                    squareColor = SDL_MapRGB(surface->format, 181, 136, 99); // dark
                }

                squareX = 150 + 100 * j;
                squareY = SCREEN_HEIGHT - 100 * (i + 1);

                SDL_Rect squareRect = { squareX, squareY, 100, 100};

                SDL_FillRect(surface, &squareRect, squareColor);
            }
        }

        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                if (board[i][j].color != -1) {
                    SDL_Surface* loadedSurface = IMG_Load(("./pieceImages/" + std::to_string(board[i][j].color) + board[i][j].name + ".png").c_str());
                    // pieceTextures[i][j] = 
                    // pieceTextures[i][j] = "./pieceImages/" + std::to_string(board[i][j].color) + board[i][j].name + ".png";
                } else {
                    pieceTextures[i][j] = nullptr;
                }
            }
        }

        SDL_UpdateWindowSurface(window);
    }

    SDL_DestroyWindow(window);

    SDL_Quit();

    return;
}