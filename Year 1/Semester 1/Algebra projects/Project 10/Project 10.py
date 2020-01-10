from texttable import Texttable
from numpy.polynomial import Polynomial
from copy import deepcopy
import itertools
from functools import cmp_to_key


class Project:
    def __init__(self, fileNameIn, fileNameOut):
        self._fileIn = fileNameIn
        self._fileOut = fileNameOut
        self._loadFile()
        height = deepcopy(self.n)
        width = deepcopy(self.k)
        self.generatorMatrix = []  # represented as a list of column vectors
        self.calculateParity()
        # print(self.generatorMatrix)
        self.parityMatrix = []
        self.parityCheckMatrix()
        # print(self.parityMatrix)
        self.syndromeAndCoset = {}
        self.strings = []
        self.syndromeDict()
        self.chooseBest()
        # print(self.syndromeAndCoset)
        self._saveFile()

    def _loadFile(self):
        f = open(self._fileIn, 'r')
        a = f.readline()
        a = a.strip()
        self.k = int(a)
        a = f.readline()
        a = a.strip()
        self.n = int(a)
        a = f.readline()
        a = a.strip()
        a = a.split(',')
        self.p = []
        for i in a:
            self.p.append(int(i))
        f.close()

    def _saveFile(self):
        f = open(self._fileOut, 'w')
        f.write('Generator Matrix:\n')
        for i in range(self.n):
            for j in range(self.k):
                f.write(str(self.generatorMatrix[j][i]) + ' ')
            f.write('\n')
        f.write('\nParity Check Matrix:\n')
        for i in range(self.n - self.k):
            for j in range(self.n):
                f.write(str(self.parityMatrix[j][i]) + ' ')
            f.write('\n')
        f.write('\nSyndrome and Coset Leaders:\n')
        for i in self.syndromeAndCoset:
            f.write(i + '---->' + self.syndromeAndCoset[i] + '\n')
        f.close()

    def calculateParity(self):
        """
        Function to calculate generator matrix
        """
        p = [0] * deepcopy(self.k)
        for i in range(self.k):
            p[i] = 1
            self.generatorMatrix.append(self.findCol(p))
            p[i] = 0

    def findCol(self, poly):
        """
        Function to do the polynomial division to be added into generator Matrix
        """
        aux = [0] * deepcopy(self.n - self.k)
        aux.append(1)
        poly = Polynomial(poly)
        poly *= aux
        quo, rem = divmod(poly, Polynomial(self.p))
        poly += rem
        poly = list(poly)
        for i in range(len(poly)):
            poly[i] = int(poly[i]) % 2
        while len(poly) < self.n:
            poly.append(0)
        return poly

    def parityCheckMatrix(self):
        """
        Function to calculate the parity check matrix
        """
        p = [0 for k in range(self.n - self.k)]
        for i in range(self.n - self.k):
            p[i] = 1
            self.parityMatrix.append(deepcopy(p))
            p[i] = 0
        for i in range(self.k):
            self.parityMatrix.append(self.generatorMatrix[i][:(self.n - self.k)])

    def syndromeDict(self):
        a = self.n - self.k
        for i in range(2 ** a):
            b = bin(i)[2:]
            l = len(b)
            b = str(0) * (a - l) + b
            self.syndromeAndCoset[b] = '0' * deepcopy(self.n)
        self.syndromeAndCoset[str(0) * a] = str(0) * deepcopy(self.n)
        stringlist = []
        for elem in self.parityMatrix:
            stringlist.append(self.getString(elem))
        for i in self.syndromeAndCoset:
            a = list(i)
            for j in range(len(a)):
                a[j] = int(a[j])

            for j in self.parityMatrix:
                if j == a:
                    self.syndromeAndCoset[i] = self.syndromeAndCoset[i][:self.parityMatrix.index(j)] + '1' + self.syndromeAndCoset[i][self.parityMatrix.index(j) + 1:]
                    self.strings.append((i, 1, [self.parityMatrix.index(j)]))
        print(stringlist)
        self.getTotalXors(stringlist)

    def getString(self, array):
        r = ''
        for i in array:
            r += str(i)
        return r

    def exclusiveOr(self, s1, s2):
        """
        Every linear combination of elements from F2 ^n is xor between them
        """
        r = ''
        for i in range(self.n - self.k):
            r += str((int(s1[i]) + int(s2[i])) % 2)
        return r

    def xorArray(self, arr, stringList):
        res = '0' * (self.n - self.k)
        for i in arr:
            res = self.exclusiveOr(res, stringList[i])
        return res

    def getTotalXors(self, stringList):
        indexArr = [i for i in range(self.n)]
        tupleSet = set()
        for l in range(2, len(indexArr) + 1):
            for permutation in itertools.permutations(indexArr, l):
                permutation = list(permutation)
                permutation.sort()
                tupleSet.add(tuple(permutation))
        permutation = map(lambda e: list(e), tupleSet)
        for e in permutation:
            copyOfE = deepcopy(e)
            e = self.xorArray(e, stringList)
            self.strings.append((e, len(copyOfE), copyOfE))

    def closestElements(self, elem):
        maxi = 0
        for i in range(len(elem[2]) - 1):
            if abs(elem[2][i] - elem[2][i + 1]) > maxi:
                maxi = abs(elem[2][i] - elem[2][i + 1])
        return maxi

    def generateBase2(self, arr):
        res = '0' * deepcopy(self.n)
        for i in arr:
            res = res[:i] + '1' + res[i + 1:]
        return res

    def sortFunction(self, elem1, elem2):
        if elem1[1] < elem2[1]:
            return elem1[1] < elem2[1]
        elif elem1[1] > elem2[1]:
            return False
        else:
            if self.closestElements(elem1) <= self.closestElements(elem2):
                return True
            else:
                return False

    def chooseBest(self):
        self.strings = sorted(self.strings, key=lambda x: (x[1], self.closestElements(x)))
        l = len(self.strings)
        i = 0
        while i < l:
            if self.strings[i][0] in self.syndromeAndCoset.keys() and self.syndromeAndCoset[self.strings[i][0]] == '0' * self.n and self.strings[i][0] != '0' * (self.n - self.k):
                self.syndromeAndCoset[self.strings[i][0]] = self.generateBase2(self.strings[i][2])
                i += 1
            else:
                self.strings.pop(i)
                l -= 1
                continue
        # print(self.strings)


project1 = Project('test1.in', 'test1.out')
project2 = Project('test2.in', 'test2.out')
project3 = Project('test3.in', 'test3.out')
project4 = Project('test4.in', 'test4.out')
project5 = Project('test5.in', 'test5.out')