class IterativeSolution:
    def __init__(self, number):
        self._number = number
        self._array = []
        for i in range(self._number):
            self._array.append(0)
        self._text = ''
        self.parentheses()

    def condition(self, val):
        closedBracket = 0
        openedBracket = 0
        for i in range(val + 1):
            if self._array[i] == 0:
                openedBracket -= -1
            else:
                closedBracket -= -1
        return closedBracket <= openedBracket <= self._number / 2

    def showParentheses(self):
        for i in range(self._number):
            if self._array[i] == 1:
                self._text += ')'
            elif self._array[i] == 0:
                self._text += '('
        self._text += '\n'

    def parentheses(self):
        stack = [(self._array, 0)]
        while len(stack) > 0:
            self._array, val = stack.pop()
            for i in [0, 1]:
                self._array[val] = i
                if self.condition(val):
                    if val == self._number - 1:
                        self.showParentheses()
                    else:
                        stack.append((self._array[:], val + 1))

    def __str__(self):
        return self._text
