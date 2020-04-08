from copy import deepcopy


class OrderedGraphCost:
    def __init__(self, nrV):    
        self._dictIn = {}
        self._dictOut = {}
        self._costDict = {}
        for i in range(nrV):
            self._dictIn[i] = []
            self._dictOut[i] = []

    def addEdge(self, vertexInit, vertexFin, cost=0):
        if not self.isVertex(vertexInit) or not self.isVertex(vertexFin):
            raise ValueError('Invalid Vertex')
        if self.isEdge(vertexInit, vertexFin):
            raise ValueError('Edge already exists')
        self._costDict[(vertexInit, vertexFin)] = cost
        self._dictOut[vertexInit].append(vertexFin)
        self._dictIn[vertexFin].append(vertexInit)

    def setOfVertices(self):
        return iter(self._dictOut.keys())

    def isVertex(self, val):
        if val in self._dictOut.keys():
            return True
        return False

    def isEdge(self, vertexInit, vertexFin):
        if vertexFin in self._dictOut[vertexInit]:
            return True
        return False

    def inDegree(self, x):
        return len(self._dictIn[x])

    def outDegree(self, x):
        return len(self._dictOut[x])

    def inboundEdge(self, x):
        return iter(self._dictIn[x])

    def outboundEdge(self, x):
        return iter(self._dictOut[x])

    def changeCost(self, x, y, val):
        if not self.isEdge(x, y):
            raise ValueError('Edge does not exist')
        self._costDict[(x, y)] = val

    def getCost(self, x, y):
        if not self.isEdge(x, y):
            raise ValueError('Edge does not exist')
        return self._costDict[(x, y)]

    def nrEdges(self):
        return len(self._costDict.keys())

    def removeEdge(self, vertexInit, vertexFin):
        if not self.isEdge(vertexInit, vertexFin):
            raise ValueError('Edge does not exist')
        for elem in self._costDict.keys():
            if vertexFin == elem[1] and vertexInit == elem[0]:
                del self._costDict[elem]
                break
        self._dictIn[vertexFin].remove(vertexInit)
        self._dictOut[vertexInit].remove(vertexFin)

    def nrVertices(self):
        return len(self._dictIn)

    def addVertex(self, val):
        if self.isVertex(val):
            raise ValueError('Vertex already exists')
        self._dictOut[val] = []
        self._dictIn[val] = []

    def removeVertex(self, vertex):
        del self._dictOut[vertex]
        del self._dictIn[vertex]
        length = len(self._costDict)
        array = list(self._costDict.keys())
        i = 0
        while i < length:
            if array[i][1] == vertex or array[i][0] == vertex:
                del self._costDict[array[i]]
                del array[i]
                length -= 1
                continue
            i -= -1
        for i in self._dictIn.keys():
            if vertex in self._dictIn[i]:
                self._dictIn[i].remove(vertex)
        for i in self._dictOut.keys():
            if vertex in self._dictOut[i]:
                self._dictOut[i].remove(vertex)
        newDict = {}
        for i in range(len(self._dictIn.keys()) - 1):
            newDict[i] = []
        for i in self._dictIn:
            x = i
            if (i > vertex):
                x -= 1
            newDict[x] = self._dictIn[i]
            for j in range(len(self._dictIn[i])):
                if self._dictIn[i][j] > vertex:
                    newDict[x][j] -= 1
        self._dictIn = newDict
        newDict = {}
        for i in range(len(self._dictIn.keys()) - 1):
            newDict[i] = []
        for i in self._dictOut:
            x = i
            if i > vertex:
                x -= 1
            newDict[x] = self._dictOut[i]
            for j in range(len(self._dictOut[i])):
                if self._dictOut[i][j] > vertex:
                    newDict[x][j] -= 1
        self._dictOut = newDict
        newDict = {}
        for i in self._costDict.keys():
            x = i[0]
            y = i[1]
            if i[0] > vertex:
                x -= 1
            if i[1] > vertex:
                y -= 1
            newDict[(x, y)] = self._costDict[i]
        self._costDict = newDict
            
    def copyGraph(self):
        return deepcopy(self)

    def __repr__(self):
        return str(self)

    def __str__(self):
        r = ''
        for i in self._costDict.keys():
            r += str(i[0]) + ' ' + str(i[1]) + ' ' + str(self._costDict[i]) + '\n'
        for i in self._dictIn.keys():
            if len(self._dictOut[i]) == 0 and len(self._dictIn[i]) == 0:
                r += str(i) + ' -1\n'
        return r


def readFile():
    f = open('graph1k.txt', 'r')
    a = f.readline()
    a = a.strip()
    a = a.split()
    n = int(a[0])
    m = int(a[1])
    G = OrderedGraphCost(n)
    for i in range(m):
        a = f.readline()
        a = a.strip()
        a = a.split()
        G.addEdge(int(a[0]), int(a[1]), int(a[2]))
    return G












