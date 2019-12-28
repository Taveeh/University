import random
from copy import deepcopy


class RandomComputer:
    @staticmethod
    def calculateMove(board):
        candidates = []
        for i in range(board.sizeofX):
            for j in range(board.sizeofY):
                if board.get(i, j) == 0:
                    candidates.append((i, j))
        return random.choice(candidates)


class SmartestComputer:
    def minmax(self, board, depth, isMax):
        eva = board.evaluate()
        if eva == -10 or eva == 10:
            return eva
        if board.isEnded():
            return 0
        if isMax:
            best = -1000
            for i in range(board.sizeofX):
                for j in range(board.sizeofY):
                    if board.get(i, j) == 0:
                        board.move(i, j, 'X')
                        best = max(best, self.minmax(board, depth + 1, not isMax))
                        board.kindaUndo()
            return best
        else:
            best = 1000
            for i in range(board.sizeofX):
                for j in range(board.sizeofY):
                    if board.get(i, j) == 0:
                        board.move(i, j, '0')
                        best = min(best, self.minmax(board, depth + 1, not isMax))
                        board.kindaUndo()
            return best

    def calculateMove(self, board):
        bestVal = -1000
        x = -1
        y = -1
        board = deepcopy(board)
        for i in range(board.sizeofX):
            for j in range(board.sizeofY):
                if board.get(i, j) == 0:
                    board.move(i, j, 'X')
                    moveVal = self.minmax(board, 0, False)
                    board.kindaUndo()
                    if moveVal > bestVal:
                        x = i
                        y = j
                        bestVal = moveVal
        return (x, y)
