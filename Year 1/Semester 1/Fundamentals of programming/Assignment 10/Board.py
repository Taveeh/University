from texttable import Texttable
from copy import deepcopy


class Board:
    def __init__(self, sizex, sizey):
        """
        Empty - 0
        X - 1
        0 - -1
        B - 2
        """
        if not sizex.isdigit() or not sizey.isdigit():
            raise ValueError('Invalid board size')
        sizey = int(sizey)
        sizex = int(sizex)
        self._sizex = sizex
        self._sizey = sizey
        self._data = [0] * self._sizex * self._sizey
        self._moves = 0
        self._nox = 0
        self._noo = 0
        self._his = []

    def move(self, x, y, symbol):
        """
        x, y, in [0, 1, ..., self._size - 1], symbol in [X, 0]
        """
        '''
        move Function that makes the move of a player
        
        Raises:
            ValueError: Move not inside the table
            ValueError: Symbol does not exist
            ValueError: Cannot place element
        '''
        if x not in range(self._sizex) or y not in range(self._sizey):
            print(x, y)
            raise ValueError('Move not inside the table')
        if symbol not in ['X', '0']:
            raise ValueError('Symbol does not exist')
        if self._data[self._sizey * x + y] != 0:
            raise ValueError('Cannot place element')
        self._his.append((deepcopy(self._data), deepcopy(
            self._moves), deepcopy(self._nox), deepcopy(self._noo)))
        if symbol == 'X':
            self._nox += 1
        else:
            self._noo += 1
        d = {'X': 1, '0': -1}
        loc = self._sizey * x + y
        self._data[loc] = d[symbol]
        self._moves += 1
        dx = [-1, -1, -1, 0, 1, 1, 1, 0]
        dy = [-1, 0, 1, 1, 1, 0, -1, -1]
        for i in range(8):
            if x + dx[i] in range(self._sizex) and y + dy[i] in range(self._sizey) and self._data[self._sizey * (x + dx[i]) + y + dy[i]] == 0:
                self._data[self._sizey * (x + dx[i]) + y + dy[i]] = 2
                self._moves += 1

    def isEnded(self):
        '''
        isEnded Function that verifies if the game has ended

        Returns:
            Bool -- True if game is finished || False otherwise
        '''
        return self._moves == self._sizex * self._sizey

    def get(self, x, y):
        '''
        get Gets element on coordinates x y in board

        Arguments:
            x {int} -- x coord
            y {int} -- y coord

        Returns:
            int -- Element on (x, y)
        '''
        return self._data[self._sizey * x + y]

    def calcNearby(self, x, y):
        '''
        calcNearby Function that returns how many empty squares are nearby

        Arguments:
            x {int} -- x coord
            y {int} -- y coord

        Returns:
            int -- number of empty squares
        '''
        dx = [-1, -1, -1, 0, 1, 1, 1, 0]
        dy = [-1, 0, 1, 1, 1, 0, -1, -1]
        nr = 0
        for i in range(8):
            if x + dx[i] in range(self._sizex) and y + dy[i] in range(self._sizey) and self._data[self._sizey * (x + dx[i]) + y + dy[i]] == 0:
                nr += 1
        return nr

    def evaluate(self):
        '''
        evaluate Function that evaluates the value of a move (computer or human)

        Returns:
            int -- Value of the move
        '''
        if self.isEnded():
            return 999
        if self._sizey * self._sizex - self._moves <= 9:
            if self._nox == self._noo:
                return 10 - (self._sizey * self._sizex - self._moves)
            else:
                return -10 + (self._sizey * self._sizex - self._moves)
        return 998

    def kindaUndo(self):
        '''
        kindaUndo Undo the last move
        '''
        ecva = deepcopy(self._his.pop())
        self._data.clear()
        self._data.extend(ecva[0])
        self._moves = ecva[1]
        self._nox = ecva[2]
        self._noo = ecva[3]

    @property
    def sizeofX(self):
        return self._sizex

    @property
    def sizeofY(self):
        return self._sizey

    def __str__(self):
        '''
        __str__ Prints the game board

        Returns:
            Texttable -- game board
        '''
        table = Texttable()
        d = {1: 'X', -1: '0', 0: ' ', 2: 'B'}
        for i in range(0, self._sizex * self._sizey, self._sizey):
            row = self._data[i:i + self._sizey]
            for j in range(self._sizey):
                row[j] = d[row[j]]
            table.add_row(row)
        return table.draw()
