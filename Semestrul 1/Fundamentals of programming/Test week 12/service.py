from Domain import *


def distance(x1, y1, x2, y2):
    """
    Manhattan Distance
    input: x1, y1, x2, y2 - coord
    output: manhattan distance between them
    """
    return abs(x1 - x2) + abs(y1 - y2)


class DriverService:
    def __init__(self, repo):
        self._repo = repo

    def __str__(self):
        r = ''
        for i in self._repo.getAll:
            r += str(i)
        return r

    def distanceToAddress(self, x, y):
        """
        Function that calculates the closest driver to the given address
        Input: x, y - coordinates of the address
        Output: closest driver
        """
        d = {}
        l = []
        for i in self._repo.getAll:
            d[i.Name] = distance(x, y, i.X, i.Y)
            l.append(i)
        lista = sorted(l, key=lambda z: d[z.Name])
        return (lista, d)

    def closestDrivers(self):
        """
        Function that returns the pair of drivers that are closest to each other
        """
        l = []
        for i in self._repo.getAll:
            for j in self._repo.getAll[self._repo.getAll.index(i) + 1:]:
                l.append([i, j, distance(i.X, i.Y, j.X, j.Y)])
        l = sorted(l, key=lambda x: x[2])
        return l[0]


class AddressService:
    def __init__(self, repo):
        self._repo = repo

    def __str__(self):
        r = ''
        for i in self._repo.getAll:
            r += str(i)
        return r

    def find(self, addressID):
        """
        Function that finds the address with given ID
        input: addressID
        output: address || False if does not exist
        """
        addressID = int(addressID)
        for i in self._repo.getAll:
            if addressID == i.Id:
                return i
        return False
