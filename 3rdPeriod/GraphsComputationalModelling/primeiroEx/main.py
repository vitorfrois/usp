import random
from random import random
from array import *

class main():
    def __init__(self):
        pass
    def erdosrenyi():
        N = int(input("Insira N: "))
        p = float(input("Insira p: "))
        if(p > 1 or p < 0):
            print("Insira um valor de p entre 0 e 1")
            exit()

        M = [([0]*N) for i in range(N)] #declare the matrix
        for i in range(N):
            M[i][i] = 0
            for j in range(1+i, N, 1):
                # print("couple = ", i, "and ", j)
                r = random()
                # print(r)
                if(r < p):
                    M[i][j] = M[j][i] = 1
                else:
                    M[i][j] = M[j][i] = 0

        for i in range(N):
            for j in range(N):
                print(M[i][j], " ", end="")
            print(" ")

main.erdosrenyi()