from OrderedGraph import OrderedGraphCost, readFile
import random


class UI:
    def __init__(self, graph):
        self._graph = graph

    @staticmethod
    def printMenu():
        print('Graph Operations')
        print('1. Get the number of vertices')
        print('2. The set of vertices')
        print('3. Check if there is an edge between 2 vertices')
        print('4. In degree of a vertex')
        print('5. Out degree of a vertex')
        print('6. The outboun®d edges of a vertex')
        print('7. The inbound edges of a vertex')
        print('8. Get the cost of an edge')
        print('9. Modify the cost of an edge')
        print('10. Add edge')
        print('11. Remove edge')
        print('12. Add vertex')
        print('13. Remove vertex')
        print('14. Save graph to file')
        print('0. Exit')

    def nrVert(self):
        print(self._graph.nrVertices())

    def setVert(self):
        r = []
        for i in self._graph.setOfVertices():
            r.append(int(i))
        print(r)

    def checkEdge(self):
        x = int(input('Vertex 1: '))
        y = int(input('Vertex 2: '))
        print(self._graph.isEdge(x, y))

    def inDeg(self):
        x = int(input('Vertex: '))
        print(self._graph.inDegree(x))

    def outDeg(self):
        x = int(input('Vertex: '))
        print(self._graph.outDegree(x))

    def outEdges(self):
        x = int(input('Vertex: '))
        r = ''
        for i in self._graph.outboundEdge(x):
            r += str(i) + ' '
        print(r)

    def inEdges(self):
        x = int(input('Vertex: '))
        r = ''
        for i in self._graph.inboundEdge(x):
            r += str(i) + ' '
        print(r)

    def edgeCost(self):
        x = int(input('Vertex 1: '))
        y = int(input('Vertex 2: '))
        print(self._graph.getCost(x, y))

    def changeEdge(self):
        x = int(input('Vertex 1: '))
        y = int(input('Vertex 2: '))
        val = int(input('Value: '))
        self._graph.changeCost(x, y, val)

    def addEdge(self):
        x = int(input('Vertex 1: '))
        y = int(input('Vertex 2: '))
        val = int(input('Cost: '))
        self._graph.addEdge(x, y, val)

    def removeEdge(self):
        x = int(input('Vertex 1: '))
        y = int(input('Vertex 2: '))
        self._graph.removeEdge(x, y)

    def addVertex(self):
        x = int(input('Vertex: '))
        self._graph.addVertex(x)

    def removeVertex(self):
        x = int(input('Vertex: '))
        self._graph.removeVertex(x)

    def copyGraph(self):
        file = input('File name: ')
        f = open(file, 'w')
        g = self._graph.copyGraph()
        f.write(str(g.nrVertices()) + ' ' + str(g.nrEdges()) + '\n')
        f.write(str(g))

    def start(self):
        d = {
            '1': self.nrVert,
            '2': self.setVert,
            '3': self.checkEdge,
            '4': self.inDeg,
            '5': self.outDeg,
            '6': self.outEdges,
            '7': self.inEdges,
            '8': self.edgeCost,
            '9': self.changeEdge,
            '10': self.addEdge,
            '11': self.removeEdge,
            '12': self.addVertex,
            '13': self.removeVertex,
            '14': self.copyGraph
        }
        while True:
            self.printMenu()
            cmd = input('Command: ')
            if cmd == '0':
                return 0
            elif cmd in d.keys():
                d[cmd]()
                print(str(self._graph))
            else:
                print('Invalid command')


def generateGraph():
    nrV = int(input('Nr Vertices: '))
    nrE = int(input('Nr Edges: '))
    aux = []
    G = OrderedGraphCost(nrV)
    for i in G.setOfVertices():
        aux.append(int(i))
    i = 0
    while i < nrE:
        tpl = (random.choice(aux), random.choice(aux), random.choice(list(range(-100, 100))))
        if G.isEdge(tpl[0], tpl[1]):
            continue
        G.addEdge(tpl[0], tpl[1], tpl[2])

        i -= -1
    return G


def main():
    print('Read graph from memory or generate? 1 - read, 2 - generate')
    cmd = input('Choice: ')
    if cmd == '2':
        g = generateGraph()
    elif cmd == '1':
        g = readFile()
    else:
        print('Invalid')
        return
    u = UI(g)
    u.start()


main()
