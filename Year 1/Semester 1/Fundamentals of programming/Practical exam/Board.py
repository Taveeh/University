from texttable import Texttable
import random


class Board:
    def __init__(self):
        self._data = [0] * 64
        self._cheat = False
        self._nr = 3
        # 1 - star
        # 2 - enemy ship
        # -1 - your ship
        # 3 - cannot be star
        self._poz = -1
        self.placeStars()
        self.placeShip()
        self.placeEnemy()

    def placeShip(self):
        candidates = list(range(0, 64))
        c = random.choice(candidates)
        while self._data[c] != 0:
            c = random.choice(candidates)
        self._data[c] = -1
        self._poz = c

    def destroyShip(self, x, y):
        self._data[x * 8 + y] = 0
        self.clearEnemy()

    @property
    def enemies(self):
        return self._nr

    def clearEnemy(self):
        for i in range(64):
            if self._data[i] == 2 or self._data[i] == 4:
                self._data[i] = 0
        self._nr -= 1
        self.placeEnemy()

    def placeEnemy(self):
        nr = 1
        candidates = list(range(0, 64))
        while nr <= self._nr:
            c = random.choice(candidates)
            while self._data[c] != 0:
                c = random.choice(candidates)
            self._data[c] = 2
            nr -= -1
        self.findEnemy()

    def findEnemy(self):
        for i in range(len(self._data)):
            if i - self._poz in [7, 8, 9, 1, -1, -7, -8, -9] and self._data[i] == 2:
                self._data[i] = 4

    def placeStars(self):
        """
        Function that randomizes the place of stars on the map by eliminating the ones that are impossible
        Input: self - board object
        Output:
        """
        candidates = list(range(0, 64))
        nr = 1
        while nr <= 10:
            poz = random.choice(candidates)

            self._data[poz] = 1
            nr -= -1
            candidates.remove(poz)
            if 1 <= poz // 8 <= 6:
                if poz % 8 == 0:
                    for k in [poz + 1, poz + 8, poz + 9, poz - 7, poz - 8]:
                        if k in candidates:
                            candidates.remove(k)
                elif poz % 8 == 7:
                    for k in [poz - 1, poz + 8, poz - 9, poz + 7, poz - 8]:
                        if k in candidates:
                            candidates.remove(k)
                else:
                    for k in [poz + 1, poz + 8, poz + 9, poz - 7, poz - 8, poz - 9, poz + 7, poz - 1]:
                        if k in candidates:
                            candidates.remove(k)
            if poz // 8 == 0:
                if poz % 8 == 0:
                    for k in [poz + 1, poz + 9, poz + 8]:
                        if k in candidates:
                            candidates.remove(k)
                elif poz % 8 == 7:
                    for k in [poz + 8, poz - 1, poz - 7]:
                        if k in candidates:
                            candidates.remove(k)
                else:
                    for k in [poz + 1, poz - 1, poz + 7, poz + 8, poz + 9]:
                        if k in candidates:
                            candidates.remove(k)
            if poz // 8 == 7:
                if poz % 8 == 0:
                    for k in [poz - 8, poz - 7, poz + 1]:
                        if k in candidates:
                            candidates.remove(k)
                elif poz % 8 == 7:
                    for k in [poz - 8, poz - 1, poz - 9]:
                        if k in candidates:
                            candidates.remove(k)
                else:
                    for k in [poz - 8, poz - 1, poz - 9, poz - 7, poz + 1]:
                        if k in candidates:
                            candidates.remove(k)

    @property
    def currentPosition(self):
        return self._poz

    @currentPosition.setter
    def currentPosition(self, val):
        self._poz = val

    def closeToEnemy(self):
        pass

    @property
    def Cheat(self):
        return self._cheat

    @Cheat.setter
    def Cheat(self, val):
        self._cheat = val

    @property
    def allData(self):
        return self._data

    def __str__(self):
        t = Texttable()
        nr = [0, 1, 2, 3, 4, 5, 6, 7, 8]
        t.add_row(nr)
        d = {1: '*', 2: ' ', 0: ' ', -1: 'E', 4: 'B'}
        if self._cheat:
            d[2] = 'B'
        litere = 'ABCDEFGH'
        for i in range(0, 64, 8):
            l = self._data[i: i + 8]
            l.insert(0, litere[i // 8])
            for j in range(1, 9):
                l[j] = d[l[j]]
                # if d[l[j]] == 'B':
                #     poz = i + j
            t.add_row(l)
        return t.draw()


# b = Board()
#
# print(b)
