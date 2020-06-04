from matplotlib.pyplot import plot,show,scatter,savefig,xlim,ylim
from math import hypot
# UnionFind
class UnionFind():
    def __init__(self, n):
        self.nodes=[-1] * n  # nodes[x]: 負なら、絶対値が木の要素数

    def get_root(self, x):
        # nodes[x]が負ならxが根
        if self.nodes[x] < 0:
            return x
        # 根に直接つなぎ直しつつ、親を再帰的に探す
        else:
            self.nodes[x]=self.get_root(self.nodes[x])
            return self.nodes[x]

    def unite(self, x, y):
        root_x=self.get_root(x)
        root_y=self.get_root(y)
        #根が同じなら変わらない
        if root_x == root_y:
            return False
        if root_x != root_y:
            # 大きい木の方につないだほうが計算量が減る
            if self.nodes[root_x] < self.nodes[root_y]:
                big_root=root_x
                small_root=root_y
            else:
                small_root=root_x
                big_root=root_y
            self.nodes[big_root] += self.nodes[small_root]
            self.nodes[small_root]=big_root
        return True


def read_points(input_file):
    points = []
    with open(input_file, "r") as f:
        lines = f.readlines()
        N = int(lines[0])
        for xy in lines[1:]:
            x,y = map(int,xy.split())
            points.append((x,y))
        matrix = [[hypot(x1-x2, y1-y2) for x1,y1 in points] for x2,y2 in points]
        # print(*matrix,sep="\n")
    return matrix, points

def get_initial_tour_DMST(edges:list, N:int):
    edges.sort(key = lambda x:x[2])
    uf=UnionFind(N)
    get_root, unite, nodes=uf.get_root, uf.unite, uf.nodes

    edge = [[] for _ in range(N)] #edge[i]:iから伸びてる辺
    for u,v,_ in edges:
        if(uf.unite(u,v)):
            edge[u].append(v)
            edge[v].append(u)
    
    tour = []
    dfs(0,edge,tour)
    return tour

#オイラーツアーを取得
def dfs(cur:int, edge:list, res:list, visited = set()):
    res.append(cur)
    visited.add(cur)
    for to in edge[cur]:
        if(to in visited): continue
        dfs(to, edge, res, visited)
        res.append(cur)

#描画
def plot_graph(points:list, tour:list, file_name:str):
    X,Y = zip(*points)
    scatter(X,Y)
    MAX_cord = max(*X,*Y)
    xlim(-1,MAX_cord+1)
    ylim(-1,MAX_cord+1)

    X2 = [X[i] for i in tour]
    Y2 = [Y[i] for i in tour]
    plot(X2,Y2)

    # show()
    savefig(file_name)

# def remove_edge(tour:list):
#     last = 0
#     visited = {0}
#     result = []
#     for cur in tour[1:]:
#         result[]

#     tour[:] = result

def main():
    matrix, points = read_points("./in.txt")
    N = len(matrix)
    edges = [(u,v,matrix[u][v]) for u in range(N) for v in range(N)]

    #----初期解生成----
    tour = get_initial_tour_DMST(edges,N)
    
    # sol_edge = [(tour[i-1],tour[i]) for i,_ in enumerate(tour)]
    plot_graph(points, tour, "spaning_tree.png")

    # sol_edge = remove_edge(tour)
    plot_graph(points, tour, "initial_solution.png")

    #----局所探索----

if __name__ == "__main__":
    main()