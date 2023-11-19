import math
import logging

import numpy as np

from OpenGL.GL import *
from PIL import Image
from logger_helper import LoggerHelper

logger = LoggerHelper.get_logger(__name__)



class ObjHelper:
    @staticmethod
    def read_file(filename) -> dict:
        """Loads a Wavefront OBJ file. """
        objects = {}
        vertices = []
        texture_coords = []
        faces = []

        material = None

        # abre o arquivo obj para leitura
        for line in open(filename, "r"): ## para cada linha do arquivo .obj
            if line.startswith('#'): continue ## ignora comentarios
            values = line.split() # quebra a linha por espaço
            if not values: continue


            ### recuperando vertices
            if values[0] == 'v':
                vertices.append(values[1:4])


            ### recuperando coordenadas de textura
            elif values[0] == 'vt':
                texture_coords.append(values[1:3])

            ### recuperando faces 
            elif values[0] in ('usemtl', 'usemat'):
                material = values[1]
            elif values[0] == 'f':
                face = []
                face_texture = []
                for v in values[1:]:
                    w = v.split('/')
                    face.append(int(w[0]))
                    if len(w) >= 2 and len(w[1]) > 0:
                        face_texture.append(int(w[1]))
                    else:
                        face_texture.append(0)

                faces.append((face, face_texture, material))

        model = {}
        model['vertices'] = vertices
        model['texture'] = texture_coords
        model['faces'] = faces

        return model

    @staticmethod
    def load_texture_from_file(img_textura, texture_id, linear_magnification = True):
        logger.info(f"tid: {texture_id}")
        glBindTexture(GL_TEXTURE_2D, texture_id)
        
        img = Image.open(img_textura)
        img_width = img.size[0]
        img_height = img.size[1]
        img_format = GL_RGB if img.mode == "RGB" else GL_RGBA
        image_data = img.tobytes("raw", "RGB", 0, -1)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img_width, img_height, 0, img_format, GL_UNSIGNED_BYTE, image_data)
        glGenerateMipmap(GL_TEXTURE_2D)

        if linear_magnification:
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR)
        else:
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST)
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR)

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT)

        return texture_id

