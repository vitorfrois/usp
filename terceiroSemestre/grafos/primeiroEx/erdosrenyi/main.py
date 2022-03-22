import random
from random import random
from array import *
from manim import *

N = int(input())
p = float(input())
if(p > 1 or p < 0):
    print("Insira um valor de p entre 0 e 1")
    exit()

M = [[0]*N for _ in range(N)] #declare the matrix
edges = []

for i in range(N):
    M[i][i] = 0
    for j in range(1+i, N, 1):
        r = random()
        print(r)
        if(r < p):
            M[i][j] = M[j][i] = 1
            edges.append((i,j))
        else:
            M[i][j] = M[j][i] = 0

for i in range(N):
    for j in range(N):
        print(M[i][j], " ", end="")
    print(" ")
    
#possible layouts: "spring","circular","kamada_kawai","planar","random", "shell","spectral","spiral"
class LabeledModifiedGraph(Scene):
    def construct(self):
        t1 = Text("Grafo gerado usando Erdõs-Rényi").move_to(3.5*UP)
        t2 = Text("Esse grafo possui \np =" + str(p) + " e N=" + str(N), font_size=30)
        vertices = []
        for x in range(N):
            vertices.append(x)
        g = Graph(vertices, edges, layout="shell", layout_scale=3, labels=True)
        self.add(g.move_to(LEFT), t1, t2.move_to(4.5*RIGHT))
