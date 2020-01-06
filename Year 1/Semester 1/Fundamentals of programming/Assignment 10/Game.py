from Board import Board
from Computer import *


class Game:
    def __init__(self, board=None, computerPlayer=None):
        self._board = board
        self._computerPlayer = computerPlayer

    def playerMove(self, x, y):
        '''
        playerMove Function that makes the players move

        Arguments:
            x {int} -- x coord
            y {int} -- y coord
        '''
        self._board.move(x, y, 'X')

    def getBoard(self):
        '''
        getBoard Function that returns the game board

        Returns:
            Board -- game board
        '''
        return self._board

    def computerMove(self):
        '''
        computerMove Function that makes the computer move
        '''
        move = self._computerPlayer.calculateMove(self._board)
        self._board.move(move[0], move[1], '0')

    def setBoard(self, x, y):
        '''
        setBoard Function that sets the dimensions of the board

        Arguments:
            x {int} -- x dimension
            y {int} -- y dimension
        '''
        self._board = Board(x, y)

    def setComputer(self, lvl):
        '''
        setComputer Function that sets the difficulty of computer

        Arguments:
            lvl {string} -- difficulty
        '''
        if lvl == 'Hard':
            self._computerPlayer = SmartestComputer()
        elif lvl == 'Medium':
            self._computerPlayer = RandomComputer()
        elif lvl == 'Easy':
            self._computerPlayer = SimpletonComputer()

    def __str__(self):
        return str(self._board)
