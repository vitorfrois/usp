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
list_obj = []

object_selection = 1
old_object_selection = 1

mat_identidade = Matrix.get_identity()

def key_event(window,key,scancode,action,mods):
    global x_inc, y_inc, yr_inc, zr_inc, s_inc
    global object_selection
    global list_obj
    
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

    if key >= 49 and key <= 53:
        
        x_inc = 0
        y_inc = 0
        yr_inc = 0
        zr_inc = 0
        s_inc = 1

    info_message = f"Pressed key: {key}"
    logging.info(info_message)


env = Environment()
env.set_key_callback(key_event)
window = env.get_window()


env.show_window()

loc = env.get_loc()

basset = GLObject('basset')
basset.init_obj()
env.add_object(basset)

box = GLObject('caixa')
box.init_obj()
env.add_object(box)

cat = GLObject('cat')
cat.init_obj()
env.add_object(cat)

geladeira = GLObject('geladeira')
geladeira.init_obj()
env.add_object(geladeira)

monstro = GLObject('monstro')
monstro.init_obj()
env.add_object(monstro)



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

for obj in env.get_list_objects():
    logger.info(obj)
    logger.info(f"{obj.start}, {obj.n_vertices}")

env.send_vertices()
env.send_texture()

while not glfw.window_should_close(env.window):
    glfw.poll_events() 
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    glClearColor(1.0, 1.0, 1.0, 1.0)
    if polygonal_mode==True:
        glPolygonMode(GL_FRONT_AND_BACK,GL_LINE)
    if polygonal_mode==False:
        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL)

    
    # Update increases
    if x_inc > 0.01: x_inc = 0.01
    if y_inc > 0.01: y_inc = 0.01
    if x_inc < -0.01: x_inc = -0.01
    if y_inc < -0.01: y_inc = -0.01

    if yr_inc > 10: yr_inc = 10
    if zr_inc > 10: zr_inc = 10
    if yr_inc < -10: yr_inc = -10
    if zr_inc < -10: zr_inc = -10



    # Get All Objects
    list_obj = env.get_list_objects()
    
    try:
        obj_to_render = list_obj[object_selection-1]
        other_objects = [obj for obj in list_obj if obj != obj_to_render]

        loc = env.get_loc()

        obj_to_render.update_position(t_x, t_y, yr_inc, zr_inc, s_inc)
        # obj_to_render.position.t_x += x_inc * s_inc
        # obj_to_render.position.t_y += y_inc * s_inc
        # obj_to_render.position.y_angle += yr_inc
        # obj_to_render.position.z_angle += zr_inc
        # obj_to_render.position.s_inc = s_inc

        center = obj_to_render.get_center()
        y_rotation = Matrix.get_y_inplace_rotation(center, obj_to_render.position.y_angle)
        z_rotation = Matrix.get_x_inplace_rotation(center, obj_to_render.position.z_angle)
        scale = Matrix.get_scale(center, obj_to_render.position.s_inc)
        translation = Matrix.get_translation(obj_to_render.position.t_x, obj_to_render.position.t_y)
        
        mat_transform = Matrix.multiply(y_rotation, z_rotation, scale, translation)

        logger.info(mat_transform)

        glUniformMatrix4fv(loc, 1, GL_TRUE, mat_transform)
        obj_to_render.draw_obj()
        obj_to_render.move_center(x_inc, y_inc)
        logger.info(obj_to_render.get_center())
        logger.info(f"{obj_to_render.start} {obj_to_render.n_vertices}")

        for obj in other_objects:
            obj.position.t_x = 0
            obj.position.t_y = 0
            obj.position.y_angle = 0
            obj.position.z_angle = 0
            obj.position.s_inc = 0.5
            obj_to_render.move_center(0, 0)



    except IndexError:
        logger.error(f'There are only {len(list_obj)} objects!')

    old_object_selection = object_selection

    glfw.swap_buffers(env.window)

glfw.terminate()