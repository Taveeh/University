from Board import Board
from Computer import *


class Game:
    def __init__(self, board=None, computerPlayer=None):
        self._board = board
        self._computerPlayer = computerPlayer

    def playerMove(self, x, y):
        self._board.move(x, y, 'X')

    def getBoard(self):
        return self._board

    def computerMove(self):
        move = self._computerPlayer.calculateMove(self._board)
        self._board.move(move[0], move[1], '0')

    def setBoard(self, x, y):
        self._board = Board(x, y)

    def setComputer(self, lvl):
        self._computerPlayer = SmartestComputer()

    def __str__(self):
        return str(self._board)