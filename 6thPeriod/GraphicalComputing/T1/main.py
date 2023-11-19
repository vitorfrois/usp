import glfw
import OpenGL.GL.shaders
import math
import logging
import time

import numpy as np

from OpenGL.GL import *
from PIL import Image
from matrix import Matrix
from globject import GLObject
from objhelper import ObjHelper
from environment import Environment
from logger_helper import LoggerHelper

# Defines
logger = LoggerHelper.get_logger(__name__)
offset = ctypes.c_void_p(0)
polygonal_mode = False
list_obj = []
GLFW_PRESS = 1

linear_magnification = True
object_selection = 1

def key_event(window,key,scancode,action,mods):
    global x_inc, y_inc, yr_inc, zr_inc, s_inc
    global object_selection
    global list_obj
    global polygonal_mode
    global linear_magnification

    
    # MOVE
    if key == 263: x_inc -= 0.001 #left
    if key == 262: x_inc += 0.001 #right
    if key == 265: y_inc += 0.001 #up
    if key == 264: y_inc -= 0.001 #down
    
    # ROTATE
    if key == 65: yr_inc -= 0.1 # a
    if key == 68: yr_inc += 0.1 # d
    if key == 87: zr_inc += 0.1 # w
    if key == 83: zr_inc -= 0.1 # s

    # SCALE
    if key == 90: s_inc += 0.001 # z
    if key == 88: s_inc -= 0.001 # x

    # SELECT OBJECT
    if key == 49: object_selection = 1
    if key == 50: object_selection = 2
    if key == 51: object_selection = 3
    if key == 52: object_selection = 4
    if key == 53: object_selection = 5

    if key >= 49 and key <= 53:
        
        x_inc = 0
        y_inc = 0
        yr_inc = 0
        zr_inc = 0
        s_inc = 1

    if key == 80 and action == GLFW_PRESS:
        polygonal_mode = not polygonal_mode

    if key == 86 and action == GLFW_PRESS:
        linear_magnification = not linear_magnification

    info_message = f"Pressed key: {key}"
    logging.info(info_message)



def main():
    env = Environment(1200, 900)
    env.set_key_callback(key_event)
    window = env.get_window()

    loc = env.get_loc()

    # Adding objects
    basset = GLObject('basset')
    basset.init_obj()
    env.add_object(basset)

    box = GLObject('caixa')
    box.init_obj()
    env.add_object(box)

    container = GLObject('container')
    container.init_obj()
    env.add_object(container)

    geladeira = GLObject('coffee')
    geladeira.init_obj()
    env.add_object(geladeira)

    monstro = GLObject('monstro')
    monstro.init_obj()
    env.add_object(monstro)

    global x_inc, y_inc, yr_inc, zr_inc, s_inc
    global object_selection
    global list_obj
    global polygonal_mode
    global linear_magnification

    # MOVE
    x_inc = 0.0
    y_inc = 0.0

    # ROTATE
    yr_inc = 0.0
    zr_inc = 0.0

    # SCALE
    s_inc = 1.0

    object_selection = 1

    for obj in env.get_list_objects():
        logger.info(obj)

    env.send_vertices()
    env.send_texture()


    while not glfw.window_should_close(env.window):
        glfw.poll_events() 
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
        glClearColor(1.0, 1.0, 1.0, 1.0)


        if polygonal_mode:
            glPolygonMode(GL_FRONT_AND_BACK,GL_LINE)
        else:
            glPolygonMode(GL_FRONT_AND_BACK,GL_FILL)

        if linear_magnification:
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR)
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR)
        else:
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST)
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST)


        # Bound increases
        if x_inc > 0.05: x_inc = 0.05
        if y_inc > 0.05: y_inc = 0.05
        if x_inc < -0.05: x_inc = -0.05
        if y_inc < -0.05: y_inc = -0.05

        if yr_inc > 20: yr_inc = 20
        if zr_inc > 20: zr_inc = 20
        if yr_inc < -20: yr_inc = -20
        if zr_inc < -20: zr_inc = -20

        # Get All Objects
        list_obj = env.get_list_objects()
        
        try:
            obj_to_render = list_obj[object_selection-1]
            other_objects = [obj for obj in list_obj if obj != obj_to_render]

            loc = env.get_loc()

            center = obj_to_render.get_center()
            y_rotation = Matrix.get_y_inplace_rotation(center, yr_inc)
            z_rotation = Matrix.get_x_inplace_rotation(center, zr_inc)
            scale = Matrix.get_scale(center, s_inc)
            translation = Matrix.get_translation(x_inc, y_inc)
            mat_transform = Matrix.multiply(y_rotation, z_rotation, scale, translation)

            final_matrix = obj_to_render.get_matrix()
            if obj_to_render.valid_transformation(mat_transform):
                final_matrix = Matrix.multiply(mat_transform, final_matrix)
                obj_to_render.set_matrix(final_matrix)
            else:
                x_inc *= -0.5
                y_inc *= -0.5
                yr_inc *= -1
                zr_inc *= -1
                s_inc = 1

            glUniformMatrix4fv(loc, 1, GL_TRUE, final_matrix)
            obj_to_render.draw_obj()

        except IndexError as e:
            logger.error(f'Error: {e}')
            logger.error(f'There are only {len(list_obj)} objects!')

        glfw.swap_buffers(env.window)

    glfw.terminate()

if __name__ == '__main__':
    main()