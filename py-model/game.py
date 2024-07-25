import chess
from model import Model

class Game:
    def __init__(self, pw, pb, use_gui = False):
        self.board = chess.Board()
        self.pw = pw
        self.pb = pb
        self.state = True

    def move(self):
        if self.board.turn:
            self.pw.move()
        elif not self.board.turn and self.state:
            self.pb.move()

    def launch_gui(self):
        # only run if the graphical interface is requested