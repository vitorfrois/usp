from math import *

def media_arit():
    N = int(input("Insira número de valores: "))
    soma = 0
    array = [0]*N
    for i in range(N):
        array[i] = float(input("x{}: ".format(i)))
        soma += array[i]
    media = soma/N
    return media, N, array

def dmedio():
    media, N, array = media_arit()
    soma = 0
    for i in range(N):
        soma += fabs(array[i]-media)

    return soma/N

def dpadrao():
    media, N, array = media_arit()
    soma = 0
    for i in range(N):
        soma += pow((array[i]-media), 2.0)
    
    padrao = soma/(N-1)
    return sqrt(padrao)

    