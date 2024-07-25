import tensorflow as tf

# Policy outputs 4272 probabilities to capture each possible move
# Value provides valuation from 0 to 1


class Model:
    def __init__(self, playing_color):
        self.input_shape = (10, 8, 8)
        self.policy_size = 4272
        self.p_color = playing_color

