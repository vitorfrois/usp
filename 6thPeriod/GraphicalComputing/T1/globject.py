import math
import glfw
import OpenGL.GL.shaders
import numpy as np
import logging

from dataclasses import dataclass
from OpenGL.GL import *
from matrix import Matrix
from logger_helper import LoggerHelper


TEXTURES_EXT = ["tif", "jpg", "png"]
logger = LoggerHelper.get_logger(__name__)
offset = ctypes.c_void_p(0)

from objhelper import ObjHelper

class GLObject:
    name: str
    n_vertices: int
    list_vertices: np.array
    list_texture: np.array
    vertices: np.array
    texture: np.array
    start: int
    number: int
    center: dict
    surrounding_polygon: list
    matrix: np.array

    def __init__(self, name):
        self.name = name
        self.texture = []
        self.vertices = []
        self.list_vertices = []
        self.list_texture = []
        self.center = [0, 0, 0]
        self.matrix = Matrix.get_identity()


    def __str__(self):
        return f'Object: {self.name}'

    def set_number(self, number):
        self.number = number

    def init_vertices(self, list_vertices):
        total_vertices = len(list_vertices)
        self.vertices = np.zeros(total_vertices, [("position", np.float32, 3)])
        self.vertices['position'] = list_vertices

    def init_texture(self, list_texture):
        total_textures = len(list_texture)
        self.texture = np.zeros(total_textures, [("position", np.float32, 2)])
        self.texture['position'] = list_texture

    def init_random_triangle(self):
        self.list_vertices = np.random.rand(6, 3)
        self.n_vertices = len(self.list_vertices)
        self.init_vertices(self.list_vertices)

    def init_obj(self, linear_magnification = True):
        modelo = ObjHelper.read_file(f'resources/{self.name}.obj')

        ### inserindo vertices do modelo no vetor de vertices
        logger.info(f'Processando modelo {self.name}')
        for face in modelo['faces']:
            for vertice_id in face[0]:
                self.list_vertices.append( modelo['vertices'][vertice_id-1] )
            for texture_coord in face[1]:
                self.list_texture.append( modelo['texture'][texture_coord-1] )

        self.number = glGenTextures(1)
        self.n_vertices = len(self.list_vertices)
        ### inserindo coordenadas de textura do modelo no vetor de texturas
        for extension in TEXTURES_EXT:
            try:
                ObjHelper.load_texture_from_file(f'resources/{self.name}.{extension}', self.number, linear_magnification)
                break
            except FileNotFoundError:
                logger.error(f"Did not found {extension} texture file")

        self.init_vertices(self.list_vertices)
        self.init_texture(self.list_texture)
        logger.info(f'Texture ID: {self.number}, ')

    def send_obj_vertices(self, env):
        logger.info(f'buffer = {env.buffer_counter}')
        glBindBuffer(GL_ARRAY_BUFFER, env.buffer[0])
        glBufferData(GL_ARRAY_BUFFER, self.vertices.nbytes, self.vertices, GL_STATIC_DRAW)
        stride = self.vertices.strides[0]

        loc = env.get_loc()
        glVertexAttribPointer(loc, 3, GL_FLOAT, False, stride, offset)
        glEnableVertexAttribArray(loc)

    def send_obj_texture(self, env):
        if len(self.texture) == 0:
            logger.info('No texture list!')
            return

        glBindBuffer(GL_ARRAY_BUFFER, env.buffer[1])
        glBufferData(GL_ARRAY_BUFFER, self.texture.nbytes, self.texture, GL_STATIC_DRAW)
        stride = self.texture.strides[0]    

        texture_loc = env.get_texture_loc()
        glVertexAttribPointer(texture_loc, 2, GL_FLOAT, False, stride, offset)
        glEnableVertexAttribArray(texture_loc)

    def center_obj(self) -> np.array:
        x = []
        y = []
        z = []

        for v in self.list_vertices:
            x.append(float(v[0]))
            y.append(float(v[1]))
            z.append(float(v[2]))
        
        minx = min(x)
        miny = min(y)
        minz = min(z)

        maxx = max(x)
        maxy = max(y)
        maxz = max(z)

        # Center Surrounding Polygon Vertices
        self.center = [np.mean(x), np.mean(y), np.mean(z), 1]

        # Center OpenGL Object
        mat_translation = Matrix.get_translation(-self.center[0], -self.center[1], -self.center[2])
        self.move_center(-self.center[0], -self.center[1], -self.center[2])

        
        self.surrounding_polygon = [
            [minx, miny, minz, 1],
            [minx, miny, maxz, 1],
            [minx, maxy, minz, 1],
            [minx, maxy, maxz, 1],
            [maxx, miny, minz, 1],
            [maxx, miny, maxz, 1],
            [maxx, maxy, minz, 1],
            [maxx, maxy, maxz, 1]
        ]

        logger.info(f"surrounding before = {self.surrounding_polygon}")

        
        scale_factor = np.max(np.abs(self.surrounding_polygon)) * 1.5
        mat_scale = Matrix.get_scale(self.center, 1/scale_factor)

        center_matrix = Matrix.multiply(mat_scale, mat_translation)
        logger.info(f"center matrix: {center_matrix}")


        if self.valid_transformation(center_matrix):
            logger.info("valid!")
        else:
            logger.info("not valid!")
        logger.info(f'center = {self.center}')

        logger.info(f"surrouding after transfor = {self.surrounding_polygon}")

        self.matrix = center_matrix
        return center_matrix

    def draw_obj(self):
        glEnableVertexAttribArray(0)    
        glBindTexture(GL_TEXTURE_2D, self.number)
        glDrawArrays(GL_TRIANGLES, self.start, self.n_vertices) ## renderizando

    def move_center(self, x, y, z = 0):
        self.center[0] += x
        self.center[1] += y
        self.center[2] += z

    def get_center(self):
        return self.center

    def valid_transformation(self, mat_transform):
        list_vertices = self.surrounding_polygon
        reshaped_transform = mat_transform.reshape(4,4)

        new_list_vertices = []
        for v in list_vertices:
            new_v = reshaped_transform @ v
            new_list_vertices.append(new_v)

        maxv = np.max(new_list_vertices)
        minv = np.min(new_list_vertices)
        if (maxv-1) >= 0.001 or (minv + 1.0) <= 0:
            return False
        
        # if the transformation is valid
        self.center = reshaped_transform @ self.center # move center
        self.surrounding_polygon = new_list_vertices # move surrounding polygon
        return True
        
    def set_matrix(self, matrix):
        self.matrix = matrix
    
    def get_matrix(self):
        return self.matrix
    
