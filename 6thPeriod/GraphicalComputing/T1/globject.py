import math
import glfw
import OpenGL.GL.shaders
import numpy as np
import logging

from OpenGL.GL import *
from matrix import Matrix
from logger_helper import LoggerHelper


TEXTURES_EXT = ["tif", "jpg"]
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

    def __init__(self, name):
        self.name = name
        self.texture = []
        self.vertices = []
        self.list_vertices = []
        self.list_texture = []


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

    def init_obj(self):
        modelo = ObjHelper.read_file(f'resources/{self.name}.obj')

        ### inserindo vertices do modelo no vetor de vertices
        logger.info(f'Processando modelo {self.name}')
        for face in modelo['faces']:
            for vertice_id in face[0]:
                self.list_vertices.append( modelo['vertices'][vertice_id-1] )
            for texture_coord in face[1]:
                self.list_texture.append( modelo['texture'][texture_coord-1] )

        self.n_vertices = len(self.list_vertices)
        ### inserindo coordenadas de textura do modelo no vetor de texturas
        self.number = glGenTextures(1)
        for extension in TEXTURES_EXT:
            try:
                ObjHelper.load_texture_from_file(f'resources/{self.name}.{extension}', self.number)
                break
            except FileNotFoundError:
                logger.error(f"Did not found {extension} texture file")


        self.init_vertices(self.list_vertices)
        self.init_texture(self.list_texture)
        logger.info(f'Texture ID: {self.number}, ')

    def send_obj_vertices(self, env):
        glBindBuffer(GL_ARRAY_BUFFER, env.buffer[0])
        glBufferData(GL_ARRAY_BUFFER, self.vertices.nbytes, self.vertices, GL_STATIC_DRAW)
        stride = self.vertices.strides[0]

        loc = env.get_loc()
        glEnableVertexAttribArray(loc)
        glVertexAttribPointer(loc, 3, GL_FLOAT, False, stride, offset)

    def send_obj_texture(self, env):
        if len(self.texture) == 0:
            logger.info('No texture list!')
            return

        glBindBuffer(GL_ARRAY_BUFFER, env.buffer[1])
        glBufferData(GL_ARRAY_BUFFER, self.texture.nbytes, self.texture, GL_STATIC_DRAW)
        stride = self.texture.strides[0]    

        texture_loc = env.get_texture_loc()
        glEnableVertexAttribArray(texture_loc)
        glVertexAttribPointer(texture_loc, 2, GL_FLOAT, GL_FALSE, stride, offset)

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

        px = (minx+maxx) / 2
        py = (miny+maxy) / 2
        pz = (minz+maxz) / 2

        mat_translation = Matrix.get_translation(-px, -py)

        return mat_translation

    def draw_obj(self):
        # print(self.name)
        # glActiveTexture(GL_TEXTURE0)
        glBindTexture(GL_TEXTURE_2D, self.number)
        glDrawArrays(GL_TRIANGLES, self.start, self.n_vertices) ## renderizando
        glBindTexture(GL_TEXTURE_2D, 0)
        # logger.info(f"{self.start}, {self.n_vertices}")
        