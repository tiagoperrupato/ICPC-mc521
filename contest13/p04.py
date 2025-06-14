from collections import deque

class Edge:
    """
    Estrutura para representar uma aresta na rede de fluxo.
    'to': Nó de destino.
    'rev': Índice da aresta reversa na lista de adjacência do nó de destino.
    'cap': Capacidade residual da aresta.
    """
    def __init__(self, to, rev, cap):
        self.to = to
        self.rev = rev
        self.cap = cap

class Dinic:
    """
    Implementação do algoritmo de Dinic para fluxo máximo.
    """
    def __init__(self, n):
        self.n = n
        self.graph = [[] for _ in range(n + 1)]
        self.level = [-1] * (n + 1)
        self.iter = [0] * (n + 1)

    def add_edge(self, u, v, cap):
        """Adiciona uma aresta direcionada e sua aresta reversa."""
        self.graph[u].append(Edge(v, len(self.graph[v]), cap))
        self.graph[v].append(Edge(u, len(self.graph[u]) - 1, 0))

    def bfs(self, s):
        """Constrói o grafo de níveis com uma BFS."""
        self.level = [-1] * (self.n + 1)
        q = deque([s])
        self.level[s] = 0
        while q:
            u = q.popleft()
            for edge in self.graph[u]:
                if edge.cap > 0 and self.level[edge.to] < 0:
                    self.level[edge.to] = self.level[u] + 1
                    q.append(edge.to)
    
    def dfs(self, u, t, f):
        """Encontra um fluxo aumentante com uma DFS no grafo de níveis."""
        if u == t:
            return f
        while self.iter[u] < len(self.graph[u]):
            edge = self.graph[u][self.iter[u]]
            if edge.cap > 0 and self.level[u] < self.level[edge.to]:
                d = self.dfs(edge.to, t, min(f, edge.cap))
                if d > 0:
                    edge.cap -= d
                    self.graph[edge.to][edge.rev].cap += d
                    return d
            self.iter[u] += 1
        return 0

    def max_flow(self, s, t):
        """Calcula o fluxo máximo de s para t."""
        flow = 0
        inf = float('inf')
        while True:
            self.bfs(s)
            if self.level[t] < 0:
                return flow
            self.iter = [0] * (self.n + 1)
            f = self.dfs(s, t, inf)
            while f > 0:
                flow += f
                f = self.dfs(s, t, inf)

def main():
    """Função principal para ler a entrada e executar o algoritmo."""
    n, m = map(int, input().split())
    
    original_edges = []
    dinic = Dinic(n)

    for _ in range(m):
        u, v = map(int, input().split())
        original_edges.append((u, v))
        dinic.add_edge(u, v, 1)
        dinic.add_edge(v, u, 1)

    s, t = 1, n
    flow = dinic.max_flow(s, t)
    print(flow)

    visited = [False] * (n + 1)
    q = deque([s])
    visited[s] = True
    while q:
        u = q.popleft()
        for edge in dinic.graph[u]:
            if edge.cap > 0 and not visited[edge.to]:
                visited[edge.to] = True
                q.append(edge.to)

    for u, v in original_edges:
        if visited[u] and not visited[v]:
            print(u, v)
        elif not visited[u] and visited[v]:
            print(v, u)

if __name__ == "__main__":
    main()
