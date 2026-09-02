"""Detect an all-one row or column while a board arrives as a stream.

Question:
    Values for an N by N binary board arrive in row-major order. After each
    value, report whether a row or column has become entirely 1.

Row and column counters make each update constant time.

Complexity: O(1) time per value and O(N^2) space.
"""


class StreamingTicTacToe:
    def __init__(self, size):
        if size <= 0:
            raise ValueError("board size must be positive")
        self.size = size
        self.board = [[0] * size for _ in range(size)]
        self.row_ones = [0] * size
        self.column_ones = [0] * size
        self.input_count = 0

    def process_input(self, value):
        """Store one 0/1 value and return whether it completes a row/column."""
        if value not in (0, 1):
            raise ValueError("stream values must be 0 or 1")
        if self.input_count == self.size * self.size:
            raise IndexError("the board is already full")

        row, column = divmod(self.input_count, self.size)
        self.input_count += 1
        self.board[row][column] = value
        self.row_ones[row] += value
        self.column_ones[column] += value
        return self.row_ones[row] == self.size or self.column_ones[column] == self.size

    def print_board(self):
        for row in self.board:
            print(row)


def _run_tests():
    game = StreamingTicTacToe(3)
    results = [game.process_input(value) for value in [0, 0, 1, 0, 0, 1, 0, 0, 1]]
    assert results == [False] * 8 + [True]

    row_game = StreamingTicTacToe(2)
    assert not row_game.process_input(1)
    assert row_game.process_input(1)


if __name__ == "__main__":
    _run_tests()
    print("All tests passed.")
