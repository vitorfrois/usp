import math 
import glfw
import OpenGL.GL.shaders
import math
import logging

import numpy as np

from OpenGL.GL import *
from globject import GLObject
from objhelper import ObjHelper
from logger_helper import LoggerHelper

logger = LoggerHelper.get_logger(__name__)

vertex_code = """
        attribute vec3 position;
        attribute vec2 texture_coord;
        varying vec2 out_texture;
                
        uniform mat4 mat_transform;        
        
        void main(){
            gl_Position = mat_transform * vec4(position,1.0);
            out_texture = vec2(texture_coord);
        }
        """

fragment_code = """
        uniform vec4 color;
        varying vec2 out_texture;
        uniform sampler2D samplerTexture;
        
        void main(){
            vec4 texture = texture2D(samplerTexture, out_texture);
            gl_FragColor = texture;
        }
        """

class Environment:
    window: None
    program: None
    loc: None
    texture_loc: None
    buffer: None
    total_vertices: int
    n_objects: int
    obj_list: list[GLObject]
    list_vertices: list
    list_texture: list

    def __init__(self):
        self.n_objects = 0
        self.total_vertices = 0
        self.obj_list = []
        self.list_vertices = []
        self.list_texture = []

        glfw.init()
        glfw.window_hint(glfw.VISIBLE, glfw.FALSE);
        self.window = glfw.create_window(600, 480, "Trabalho 1", None, None)
        glfw.make_context_current(self.window)

        # Request a program and shader slots from GPU
        self.program  = glCreateProgram()
        vertex   = glCreateShader(GL_VERTEX_SHADER)
        fragment = glCreateShader(GL_FRAGMENT_SHADER)

        # Set shaders source
        glShaderSource(vertex, vertex_code)
        glShaderSource(fragment, fragment_code)

        self.compile_shader(vertex)
        self.compile_shader(fragment)

        # Attach shader objects to the program
        glAttachShader(self.program, vertex)
        glAttachShader(self.program, fragment)

        # Build program
        glLinkProgram(self.program)
        if not glGetProgramiv(self.program, GL_LINK_STATUS):
            logger.error(glGetProgramInfoLog(self.program))
            raise RuntimeError('Linking error')

        # Make program the default program
        glUseProgram(self.program)

        # Init textures
        glEnable(GL_TEXTURE_2D)
        qtd_texturas = 2
        # textures = glGenTextures(qtd_texturas)

        # Request a buffer slot from GPU
        self.buffer = glGenBuffers(2)
        # Make this buffer the default one
        glBindBuffer(GL_ARRAY_BUFFER, self.buffer[0])

        self.loc = glGetAttribLocation(self.program, "position")
        glEnableVertexAttribArray(self.loc)

        self.texture_loc = glGetAttribLocation(self.program, "texture_coord")
        glEnableVertexAttribArray(self.texture_loc)

        glEnable(GL_DEPTH_TEST) 

    @staticmethod
    def compile_shader(shader):
        # Compile shaders
        glCompileShader(shader)
        if not glGetShaderiv(shader, GL_COMPILE_STATUS):
            error = glGetShaderInfoLog(shader).decode()
            print(error)
            raise RuntimeError("Erro de compilacao do Shader")

    def get_window(self):
        return self.window

    def get_program(self):
        return self.program

    def get_loc(self):
        return self.loc

    def get_texture_loc(self):
        return self.texture_loc

    def get_list_objects(self):
        return self.obj_list

    def get_vertices(self):
        return self.list_vertices

    def get_texture(self):
        return self.list_texture

    def get_total_vertices(self):
        return self.total_vertices

    def set_key_callback(self, key_event_function):
        glfw.set_key_callback(self.window, key_event_function)

    def show_window(self):
        glfw.show_window(self.window)

    def add_object(self, obj: GLObject):
        obj.start = self.total_vertices

        obj.send_obj_vertices(self)
        obj.send_obj_texture(self)

        center_obj_mat = obj.center_obj()
        glUniformMatrix4fv(self.loc, 1, GL_FALSE, center_obj_mat)
        obj.draw_obj()
        logger.info(f'{obj.start}, {obj.n_vertices}')
        
        self.obj_list.append(obj)
        self.total_vertices += obj.n_vertices
        self.n_objects += 1
