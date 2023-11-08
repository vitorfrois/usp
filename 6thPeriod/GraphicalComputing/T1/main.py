import glfw
import OpenGL.GL.shaders
import math
import logging

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

object_selection = 1
old_object_selection = 1

mat_identidade = Matrix.get_identity()

def key_event(window,key,scancode,action,mods):
    global x_inc, y_inc, yr_inc, zr_inc, s_inc, object_selection
    
    # MOVE
    if key == 263: x_inc -= 0.0001 #left
    if key == 262: x_inc += 0.0001 #right
    if key == 265: y_inc += 0.0001 #up
    if key == 264: y_inc -= 0.0001 #down
    
    # ROTATE
    if key == 65: yr_inc -= 0.1 # a
    if key == 68: yr_inc += 0.1 # d
    if key == 87: zr_inc += 0.1 # w
    if key == 83: zr_inc -= 0.1 # s

    # SCALE
    if key == 90: s_inc += 0.1 # z
    if key == 88: s_inc -= 0.1 # x

    # SELECT OBJECT
    if key == 49: object_selection = 1
    if key == 50: object_selection = 2
    if key == 51: object_selection = 3
    if key == 52: object_selection = 4
    if key == 53: object_selection = 5

    info_message = f"Pressed key: {key}"
    logging.info(info_message)


env = Environment()
env.set_key_callback(key_event)
window = env.get_window()

# logger.info(f'{triangle.start}, {triangle.n_vertices}')

basset = GLObject('basset')
basset.init_obj()
env.add_object(basset)
basset.draw_obj()

# box = GLObject('caixa')
# box.init_obj()
# env.add_object(box)
# box.draw_obj()

env.show_window()


print(env.get_list_objects())


# env.send_vertices()
# env.send_texture()

# MOVE
x_inc = 0.0
y_inc = 0.0

# ROTATE
yr_inc = 0.0
zr_inc = 0.0

# SCALE
s_inc = 1.0

t_x = 0.0
t_y = 0.0
y_angle = 0.0
z_angle = 0.0

object_selection = 1


while not glfw.window_should_close(env.window):
    glfw.poll_events() 

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    
    glClearColor(1.0, 1.0, 1.0, 1.0)
    
    if polygonal_mode==True:
        glPolygonMode(GL_FRONT_AND_BACK,GL_LINE)
    if polygonal_mode==False:
        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL)

    
    #Draw Triangle

    t_x += x_inc
    t_y += y_inc    
    z_angle += zr_inc
    y_angle += yr_inc

    y_rotation = Matrix.get_y_rotation(y_angle)
    z_rotation = Matrix.get_z_rotation(z_angle)
    scale = Matrix.get_scale(s_inc)
    translation = Matrix.get_translation(t_x, t_y)
    
    mat_transform = Matrix.multiply(y_rotation, z_rotation, scale, translation)

    list_obj = env.get_list_objects()
    
    try:
        obj_to_render = list_obj[object_selection-1]
        other_objects = [obj for obj in list_obj if obj != obj_to_render]

        loc = env.get_loc()

        if object_selection != old_object_selection:
            logger.info('HERE')
            print(old_object_selection, object_selection)
            x_inc = 0
            y_inc = 0
            yr_inc = 0
            zr_inc = 0
            s_inc = 1
            for obj in list_obj:
                center_matrix = obj.center_obj()
                glUniformMatrix4fv(loc, 1, GL_TRUE, center_matrix)
                obj.draw_obj()

        else:
            # Render current object
            glUniformMatrix4fv(loc, 1, GL_TRUE, mat_transform)
            obj_to_render.draw_obj()

    except IndexError:
        logger.error(f'There are only {len(list_obj)} objects!')

    old_object_selection = object_selection

    glfw.swap_buffers(env.window)

glfw.terminate()