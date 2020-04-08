from copy import deepcopy


class OrderedGraphCost:
    '''
     Function that creates a weighted ordered graph with nrV nodes and no edges
    '''
    def __init__(self, nrV):    
        self._dictIn = {}
        self._dictOut = {}
        self._costDict = {}
        for i in range(nrV):
            self._dictIn[i] = []
            self._dictOut[i] = []

    '''
     addEdge - adds an edge to the graph between 2 nodes
    
    Raises:
        ValueError: Invalid vertex
        ValueError: Edge already exists
    '''
    def addEdge(self, vertexInit, vertexFin, cost=0):
        if not self.isVertex(vertexInit) or not self.isVertex(vertexFin):
            raise ValueError('Invalid Vertex')
        if self.isEdge(vertexInit, vertexFin):
            raise ValueError('Edge already exists')
        self._costDict[(vertexInit, vertexFin)] = cost
        self._dictOut[vertexInit].append(vertexFin)
        self._dictIn[vertexFin].append(vertexInit)

    '''
     Function that returns an iterable with the set of vertices
    
    Returns:
        iterator 
    '''
    def setOfVertices(self):
        return iter(self._dictOut.keys())

    '''
     Function that verifies if a value is a vertex
    
    Returns:
        true - if val is a vertex
        false - otherwise
    '''
    def isVertex(self, val):
        if val in self._dictOut.keys():
            return True
        return False

    '''
     Function that verifies if there is an edge between 2 nodes

    Returns:
        true - if there is an edge
        false - otherwise
    '''
    def isEdge(self, vertexInit, vertexFin):
        if vertexFin in self._dictOut[vertexInit]:
            return True
        return False
    '''
    inDegree Returns the indegree of a vertex

    Returns:
        int
    '''
    def inDegree(self, x):
        return len(self._dictIn[x])
    '''
    outDegree Returns the outdegree of an edge

    Returns:
        int
    '''
    def outDegree(self, x):
        return len(self._dictOut[x])

    '''
     Returns an interable containing the inbound egdes of a vertex
    
    Returns:
        iterable
    '''
    def inboundEdge(self, x):
        return iter(self._dictIn[x])

    '''
    Returns an interable containing the outbound egdes of a vertex
    
    Returns:
        iterable
    '''
    def outboundEdge(self, x):
        return iter(self._dictOut[x])

    '''
     Changes the cost of an edge
    
    Raises:
        ValueError: Edge does not exist
    '''
    def changeCost(self, x, y, val):
        if not self.isEdge(x, y):
            raise ValueError('Edge does not exist')
        self._costDict[(x, y)] = val
    '''
    getCost Gets the cost of an edge
    
    Raises:
        ValueError: Edge does not exist
    
    Returns:
        int - cost of given edge
    '''
    def getCost(self, x, y):
        if not self.isEdge(x, y):
            raise ValueError('Edge does not exist')
        return self._costDict[(x, y)]
    '''
    nrEdges Gets the number of edges of a graph
       
    Returns:
        int -- number of edges
    '''
    def nrEdges(self):
        return len(self._costDict.keys())
    '''
    removeEdge Removes an edge 
    
    Raises:
        ValueError: [description]
        ValueError: [description]
    
    Returns:
        [type] -- [description]
    '''
    def removeEdge(self, vertexInit, vertexFin):
        if not self.isEdge(vertexInit, vertexFin):
            raise ValueError('Edge does not exist')
        for elem in self._costDict.keys():
            if vertexFin == elem[1] and vertexInit == elem[0]:
                del self._costDict[elem]
                break
        self._dictIn[vertexFin].remove(vertexInit)
        self._dictOut[vertexInit].remove(vertexFin)

    
    '''
     Returns the number of vertices
    
    Returns:
        int -- number of vertices
    '''
    def nrVertices(self):
        return len(self._dictIn)

    '''
     Adds a vertex to the graph
    
    Raises:
        ValueError: Vertex already exists
    
    '''
    def addVertex(self, val):
        if self.isVertex(val):
            raise ValueError('Vertex already exists')
        self._dictOut[val] = []
        self._dictIn[val] = []

    '''
     Breath - first search in the graph
    '''
    def BFSShortestPath(self, s, d):
        visited = [False] * len(self._dictOut.keys())
        queue = [s]
        visited[s] = True
        dist = [9999999] * len(self._dictOut.keys())
        pred = [-1] * len(self._dictOut.keys())
        dist[s] = 0
        while queue:
            x = queue.pop(0)
            for i in self._dictOut[x]:
                if not visited[i]:
                    queue.append(i)
                    dist[i] = dist[x] + 1
                    visited[i] = True
                    pred[i] = x
                    if (i == d):
                        return (True, pred, dist)
        return (False, pred, dist)
        
    '''
     Depth first search in the graph
    
    Returns:
        [type] -- [description]
    '''
    def DFS(self, v, visited, l):
        visited[v] = True
        l.append(v)
        for i in self._dictOut[v]:
            if not visited[i]:
                self.DFS(i, visited, l)
    '''
     Function that puts on the stack the adjacent vertices of v
    '''
    def fillOrder(self, v, visited, stack):
        visited[v] = True
        for i in self._dictIn[v]:
            if not visited[i]:
                self.fillOrder(i, visited, stack)
        stack.append(v)

    '''
     Function that gets the transpose of the graph
    
    Returns:
        OrderedGraphCost -- transposed graph
    '''
    def reverseGraph(self):
        g = OrderedGraphCost(len(self._dictOut.keys()))
        for i in self._dictOut.keys():
            for j in self._dictOut[i]:
                g.addEdge(j, i, self.getCost(i, j))
        return g

    '''
     Function that gets the strongly connected components of a graph
    
    Returns:
        list -- components
    '''
    def getStronglyConnectedComponents(self):
        stack = []
        visited = [False] * len(self._dictOut.keys())
        for i in range(len(self._dictOut.keys())):
            if not visited[i]:
                self.fillOrder(i, visited, stack)

        gr = self.reverseGraph()
        visited = [False] * len(self._dictOut.keys())
        components = []
        while stack:
            i = stack.pop(0)
            if not visited[i]:
                l = []
                gr.DFS(i, visited, l)
                components.append(l)
        return components

    '''
     Function that removes a vertex from the graph
    
    '''
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
            if i > vertex:
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
    
    '''
     Function that copies a graph
    
    Returns:
        OrderedGraphCost -- copy of graph
    '''
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

'''
 Function that reads graph from a file
'''
def readFile():
    f = open('graph.txt', 'r')
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












