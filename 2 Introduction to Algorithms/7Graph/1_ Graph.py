class Queue(object):
    def __init__(self):
        self._item = []


    def isEmpty(self):
        return self._item == []


    def enQueue(self, item):
        self._item.insert(0, item)


    def deQueue(self):
        return self._item.pop()


    def size(self):
        return len(self._item)


    def print_queue(self):
        print(self._item)


class vertex(object):
    def __init__(self, key, adjacent):
        self.key = key
        self.adjacent = adjacent    # adjavent是一个list


class Graph(object):
    def __init__(self):
        self.node = {}  # dict key: 'A' value: 一个vertex类


    def add_vertex(self, key, adjacent=[]):    # 顶点的key，他的邻结点
        A = []
        self.node[key] = vertex(key, A)


    def add_edge(self, u, v):
        if u not in self.node or v not in self.node:
            print('边结点不存在！')
            return False
        for i in self.node[u].adjacent:
            if i == v: # adjacent的每个元素是一个tuple[0]是邻结点的key
                print('不许加重边！')
                return False
        self.node[u].adjacent.append(v)


    def BFS(self, s):
        queue = Queue() # 初始化一个队列
        visited = self.node.copy()
        for key in visited.keys():
            visited[key] = False
        print(s)
        visited[s] = True
        queue.enQueue(s)
        while not queue.isEmpty():
            u = queue.deQueue()
            for v in self.node[u].adjacent:
                if visited[v] == False:
                    print(v)
                    visited[v] = True
                    queue.enQueue(v)


    def DFS(self, s=None):
        visited = self.node.copy()
        for key in visited.keys():
            visited[key] = False
        if s is None:
            for u in self.node.keys():
                if visited[v] == 0:
                    self.Dfs(v, visited)
        else:
            self.Dfs(s, visited)


    def Dfs(self, s, visited):
        print(s)
        visited[s] = True
        for v in self.node[s].adjacent:
            if visited[v] == 0:
                self.Dfs(v, visited)




g = Graph()
g.add_vertex('s')
g.add_vertex('r')
g.add_vertex('v')
g.add_vertex('w')
g.add_vertex('x')
g.add_vertex('t')
g.add_vertex('u')
g.add_vertex('y')
g.add_edge('v','r')
g.add_edge('r','v')
g.add_edge('s','r')
g.add_edge('r','s')
g.add_edge('s','w')
g.add_edge('w','s')
g.add_edge('w','x')
g.add_edge('x','w')
g.add_edge('w','t')
g.add_edge('t','w')
g.add_edge('t','u')
g.add_edge('u','t')
g.add_edge('x','u')
g.add_edge('u','x')
g.add_edge('x','y')
g.add_edge('y','x')
g.add_edge('u','y')
g.add_edge('y','u')
g.BFS('s')
g.DFS('s')
