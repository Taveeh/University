from texttable import Texttable


class Board:
    def __init__(self):
        # 0 = empty square
        # 1 = hit
        # -1 = miss

        self._data = [0] * 64

    def move(self, x, y):
        pass
