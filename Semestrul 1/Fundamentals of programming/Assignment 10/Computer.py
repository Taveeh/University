import random
from copy import deepcopy


class SimpletonComputer:
    '''
    Computer for easy difficulty

    Returns:
        tuple -- coords of next move
    '''
    @staticmethod
    def calculateMove(board):
        for i in range(board.sizeofX):
            for j in range(board.sizeofY):
                if board.get(i, j) == 0:
                    return (i, j)


class RandomComputer:
    '''
    Computer for medium difficulty

    Returns:
        tuple -- coords of next move
    '''
    @staticmethod
    def calculateMove(board):
        candidates = []
        for i in range(board.sizeofX):
            for j in range(board.sizeofY):
                if board.get(i, j) == 0:
                    candidates.append((i, j))
        return random.choice(candidates)


class SmartestComputer:
    '''
    Computer for hard difficulty
    '''

    def minmax(self, board, depth, isMax, alpha, beta):
        '''
        minmax Function that finds the best value of a move

        Arguments:
            board {Board} -- Game board
            depth {int} -- depth of the tree
            isMax {bool} -- check if is max or min
            alpha {int} -- value of max function
            beta {int} -- value of min function

        Returns:
            int -- value of moveset
        '''
        eva = board.evaluate()
        if eva != 999 and eva != 998:
            return eva
        if board.isEnded():
            return 0
        if beta <= alpha:
            return 0
        if isMax:
            for i in range(board.sizeofX):
                for j in range(board.sizeofY):
                    if board.get(i, j) == 0:
                        board.move(i, j, 'X')
                        alpha = max(alpha, self.minmax(
                            board, depth + 1, not isMax, alpha, beta))
                        board.kindaUndo()
            return alpha
        else:
            for i in range(board.sizeofX):
                for j in range(board.sizeofY):
                    if board.get(i, j) == 0:
                        board.move(i, j, '0')
                        beta = min(beta, self.minmax(
                            board, depth + 1, not isMax, alpha, beta))
                        board.kindaUndo()
            return beta

    def calculateMove(self, board):
        '''
        calculateMove Finds the best move

        Arguments:
            board {Board} -- Game board

        Returns:
            tuple -- Coords of next move
        '''
        bestVal = -1000
        x = -1
        y = -1
        board = deepcopy(board)
        for i in range(board.sizeofX):
            for j in range(board.sizeofY):
                if board.get(i, j) == 0:
                    board.move(i, j, 'X')
                    moveVal = self.minmax(board, 0, False, -1000, 1000)
                    board.kindaUndo()
                    if moveVal > bestVal:
                        x = i
                        y = j
                        bestVal = moveVal
        return (x, y)
