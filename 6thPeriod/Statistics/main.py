# Trabalho 1 de Estatística
# Vítor Amorim Fróis 
# Gabriel Perão
# Thaís Ribeiro

import numpy as np
from random import random, uniform
import math 
from tqdm import tqdm

center = np.array([0, 0, 0, 1])
ITERATIONS = int(1e7)

def generate_random_sphere_point(model : int):
    if model == 1: 
        phi = random() * math.pi
        theta = random() * math.pi * 2
        x = math.sin(phi) * math.cos(theta)
        y = math.sin(phi) * math.sin(theta)
        z = math.cos(phi)


    elif model == 2:
        while(True):
            x = uniform(-1, 1)
            y = uniform(-1, 1)
            z = uniform(-1, 1)
        
            # if point inside sphere, break
            if x**2 + y**2 + z**2 <= 1: break
    
    point = np.array([x, y, z, 1])

    return point

class Tetrahedron:
    coordinates: list

    def __init__(self, model):
        self.model = model
        self.generate_tetrahedron()

    def generate_tetrahedron(self):
        v1 = generate_random_sphere_point(self.model)
        v2 = generate_random_sphere_point(self.model)
        v3 = generate_random_sphere_point(self.model)
        v4 = generate_random_sphere_point(self.model)

        self.coordinates = np.array([v1, v2, v3, v4]).T

    def check_point(self, p):
        u = np.linalg.solve(self.coordinates, p)
        if np.any(u < 0):
            return False
        else:
            return True

    def get_coordinates(self):
        return self.coordinates

def main():
    true_count = 0
    model = int(input("Com qual modelo devo calcular os tetraedros aleatórios? \n\
        Modelo 1 - Usando coordenadas esféricas \n\
        Modelo 2 - Uniforme dentro da esfera \n\
        (Digite apenas o número do modelo) "))
    for i in tqdm(range(ITERATIONS)):
        t = Tetrahedron(model=model)
        v = t.get_coordinates()

        if t.check_point(center):
            true_count += 1

    prob = true_count/ITERATIONS    
    print(prob)

if __name__ == '__main__':
    main()





