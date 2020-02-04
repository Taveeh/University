class GameException(Exception):
    def __init__(self, message):
        super().__init__(message)


class Game:
    def __init__(self, board):
        self._board = board

    def cheat(self):
        self._board.Cheat = not self._board.Cheat

    def fire(self, x, y):
        litere = {'A': 0, 'B': 1, 'C': 2, 'D': 3, 'E': 4, 'F': 5, 'G': 6, 'H': 7}
        if x not in litere.keys():
            raise ValueError('Invalid coord1')
        if not y.isdigit():
            raise ValueError("Invalid coord2")
        y = int(y)
        if y > 9 or y < 0:
            raise ValueError('Invalid coord3')
        y = y - 1
        x = litere[x]
        cx = self._board.currentPosition // 8
        cy = self._board.currentPosition % 8
        if abs(x - cx) > 1 or abs(y - cy) > 1:
            raise ValueError('Invalid fire')
        if self._board.allData[x * 8 + y] == 4:
            self._board.clearEnemy()
            if self._board.enemies == 0:
                raise GameException('Game won')

    def warp(self, x, y):
        litere = {'A': 0, 'B': 1, 'C': 2, 'D': 3, 'E': 4, 'F': 5, 'G': 6, 'H': 7}
        if x not in litere.keys():
            raise ValueError('Invalid coord1')
        if not y.isdigit():
            raise ValueError("Invalid coord2")
        y = int(y)
        if y > 9 or y < 0:
            raise ValueError('Invalid coord3')
        y = y - 1
        x = litere[x]
        cx = self._board.currentPosition // 8
        cy = self._board.currentPosition % 8
        print(cx, cy, x, y)
        if abs(cx - x) != abs(cy - y) and cx - x != 0 and cy - y != 0:
            raise ValueError('Invalid coord4')
        cvx = False
        cvy = False
        if cx - x == 0:
            if cy > y:
                y, cy = cy, y
                cvy = True
            for el in range(cy, y + 1):
                if self._board.allData[x * 8 + el] == 1:
                    raise ValueError('Star in way')

        elif cy - y == 0:
            if cx > x:
                x, cx = cx, x
                cvx = True
            for el in range(cx, x + 1):
                if self._board.allData[el * 8 + y] == 1:
                    raise ValueError('Star in way')
        else:
            if x < cx and y > cy:
                while x != cx and y != cy:
                    cx -= 1
                    cy += 1
                    if self._board.allData[cx * 8 + y] == 1:
                        raise ValueError('Star in way')
            if x < cx and y < cy:
                while x != cx and y != cy:
                    cx -= 1
                    cy -= 1
                    if self._board.allData[cx * 8 + y] == 1:
                        raise ValueError('Star in way')
            if x > cx and y > cy:
                while x != cx and y != cy:
                    cx += 1
                    cy += 1
                    if self._board.allData[cx * 8 + y] == 1:
                        raise ValueError('Star in way')

            if x > cx and y < cy:
                while x != cx and y != cy:
                    cx += 1
                    cy -= 1
                    if self._board.allData[cx * 8 + y] == 1:
                        raise ValueError('Star in way')
        self._board.allData[self._board.currentPosition] = 0
        if cvx:
            x, cx = cx, x
        if cvy:
            y, cy = cy, y
        self._board.currentPosition = x * 8 + y
        if self._board.allData[self._board.currentPosition] == 2 or self._board.allData[self._board.currentPosition] == 4:
            raise TypeError('Game over')
        self._board.allData[self._board.currentPosition] = -1
        self._board.findEnemy()

    def __str__(self):
        return str(self._board)

