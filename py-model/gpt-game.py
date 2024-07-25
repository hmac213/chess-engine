import pygame
import chess
import random

# Initialize Pygame
pygame.init()

# Set up the display
square_size = 60
board_size = square_size * 8
screen = pygame.display.set_mode((board_size, board_size))
pygame.display.set_caption('Chess')

# Load piece images
piece_images = {}
pieces = ['p', 'r', 'n', 'b', 'q', 'k']
for color in ['0', '1']:
    for piece in pieces:
        filename = f'pieceImages/{color}{piece}.png'
        piece_images[color + piece] = pygame.image.load(filename)

# Function to draw the chessboard
def draw_board(board, valid_moves=[], selected_square=None, dragging_piece=None, dragging_pos=None):
    light_color = pygame.Color(240, 217, 181)  # Light brown
    dark_color = pygame.Color(181, 136, 99)    # Dark brown
    highlight_color = pygame.Color(255, 100, 100, 150)  # Light red, semi-transparent

    for rank in range(8):
        for file in range(8):
            color = light_color if (rank + file) % 2 == 0 else dark_color
            pygame.draw.rect(screen, color, pygame.Rect(file * square_size, rank * square_size, square_size, square_size))

            square = chess.square(file, 7 - rank)
            if square in valid_moves:
                s = pygame.Surface((square_size, square_size), pygame.SRCALPHA)  # per-pixel alpha
                s.fill(highlight_color)
                screen.blit(s, (file * square_size, rank * square_size))

            piece = board.piece_at(square)
            if piece and (square != selected_square or dragging_piece):
                piece_image = piece_images[piece_color_piece_string(piece)]
                screen.blit(piece_image, (file * square_size, rank * square_size))

    if dragging_piece and dragging_pos:
        screen.blit(dragging_piece, dragging_pos)

# Function to convert piece to string based on piece color and type
def piece_color_piece_string(piece):
    color = '0' if piece.color == chess.WHITE else '1'
    piece_type = piece.symbol().lower()
    return color + piece_type

# Function to promote a pawn
def promote_pawn(board, move):
    promotion_piece = chess.QUEEN  # Default to queen for simplicity
    return chess.Move(move.from_square, move.to_square, promotion=promotion_piece)

# Main game loop
def main():
    board = chess.Board()
    selected_square = None
    dragging_piece = None
    dragging_pos = None
    running = True

    while running:
        valid_moves = []
        if selected_square is not None:
            for move in board.legal_moves:
                if move.from_square == selected_square:
                    valid_moves.append(move.to_square)

        draw_board(board, valid_moves, selected_square, dragging_piece, dragging_pos)
        pygame.display.flip()

        if board.turn == chess.BLACK:
            move = random.choice(list(board.legal_moves))
            if board.piece_at(move.from_square).piece_type == chess.PAWN and (chess.square_rank(move.to_square) in [0, 7]):
                move = promote_pawn(board, move)
            board.push(move)

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False
            elif event.type == pygame.MOUSEBUTTONDOWN:
                if event.button == 1:  # Left mouse button
                    x, y = event.pos
                    file = x // square_size
                    rank = 7 - (y // square_size)
                    square = chess.square(file, rank)

                    if dragging_piece:
                        move = chess.Move(selected_square, square)
                        if move in board.legal_moves:
                            if board.piece_at(selected_square).piece_type == chess.PAWN and (chess.square_rank(square) in [0, 7]):
                                move = promote_pawn(board, move)
                            board.push(move)
                        selected_square = None
                        dragging_piece = None
                        dragging_pos = None
                    else:
                        piece = board.piece_at(square)
                        if piece and piece.color == board.turn:
                            selected_square = square
                            dragging_piece = piece_images[piece_color_piece_string(piece)]
                            dragging_pos = (x - square_size // 2, y - square_size // 2)
            elif event.type == pygame.MOUSEBUTTONUP:
                if event.button == 1 and dragging_piece:
                    x, y = event.pos
                    file = x // square_size
                    rank = 7 - (y // square_size)
                    square = chess.square(file, rank)
                    move = chess.Move(selected_square, square)
                    if move in board.legal_moves:
                        if board.piece_at(selected_square).piece_type == chess.PAWN and (chess.square_rank(square) in [0, 7]):
                            move = promote_pawn(board, move)
                        board.push(move)
                    selected_square = None
                    dragging_piece = None
                    dragging_pos = None
            elif event.type == pygame.MOUSEMOTION:
                if dragging_piece:
                    x, y = event.pos
                    dragging_pos = (x - square_size // 2, y - square_size // 2)

        if board.is_game_over():
            print("Game over!")
            print(board.result())
            running = False

    pygame.quit()

if __name__ == "__main__":
    main()
