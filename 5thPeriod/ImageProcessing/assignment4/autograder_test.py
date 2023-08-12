# Assignment 3 - PDI
# 2023.04.21
# Vítor Amorim Fróis
# 12543440
# @undergrad-SCC0251

import numpy as np
np.seterr(divide='ignore', invalid='ignore')
import imageio
import sys


class Image:
    image: np.array
    P: int
    Q: int
    color: float
    fill_color: float
    neighborhood: int
    fill_point_list: list[tuple] = []

    def __init__(self, image_path, neighborhood):
        image = (imageio.v3.imread(image_path) > 127).astype(np.uint8)
        self.image = image
        P, Q = image.shape
        self.P = P
        self.Q = Q
        self.neighborhood = neighborhood

    def valid_borders(self, x, y):
        if (x > self.P) or (x < 0):
            return False
        if (y > self.Q) or (y < 0):
            return False
        return True

    def set_fill_color(self, x, y):
        color = self.image[x, y]
        self.fill_color = not color

    def recursive_fill(self, x, y):
        if self.image[x, y] == self.fill_color:
            return

        if not self.valid_borders(x, y):
            return

        self.image[x, y] = self.fill_color
        self.fill_point_list.append((x, y))

        self.recursive_fill(x, y + 1)
        self.recursive_fill(x + 1, y)
        self.recursive_fill(x, y - 1)
        self.recursive_fill(x - 1, y)

        if self.neighborhood == 8:
            self.recursive_fill(x + 1, y + 1)
            self.recursive_fill(x + 1, y - 1)
            self.recursive_fill(x - 1, y + 1)
            self.recursive_fill(x - 1, y - 1)

    def get_fill_points(self):
        return self.fill_point_list

def main():
    stdin_input = sys.stdin.read()
    lines = stdin_input.split('\n')
    image_path = lines[0]
    x = int(lines[1])
    y = int(lines[2])
    neighboorhood = int(lines[3])
    image = Image(image_path, neighboorhood)
    image.set_fill_color(x, y)
    image.recursive_fill(x, y)
    list_tuples = image.get_fill_points()
    list_tuples.sort()
    for x in list_tuples:
        print(f'({x[0]} {x[1]}) ', end='')

main()
