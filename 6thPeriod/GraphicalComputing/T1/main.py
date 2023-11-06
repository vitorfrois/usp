import glfw
from OpenGL.GL import *
import OpenGL.GL.shaders
import numpy as np
import math
import logging
from PIL import Image

# Defines
FORMAT = '|%(asctime)s| %(message)s'
logging.basicConfig(level = logging.INFO, format=FORMAT)
logger = logging.getLogger('cg')
offset = ctypes.c_void_p(0)
polygonal_mode = True


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

object_selection = 1

mat_identidade = np.array([  1.0, 0.0, 0.0, 0.0, 
                                  0.0, 1.0, 0.0, 0.0, 
                                  0.0, 0.0, 1.0, 0.0, 
                                  0.0, 0.0, 0.0, 1.0], np.float32)

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
    def load_texture_from_file(texture_id, img_textura):
        # glActiveTexture(GL_TEXTURE0)

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR)

        glBindTexture(GL_TEXTURE_2D, texture_id)
        img = Image.open(img_textura)
        img_width = img.size[0]
        img_height = img.size[1]
        image_data = img.tobytes("raw", "RGB", 0, -1)
        #image_data = np.array(list(img.getdata()), np.uint8)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img_width, img_height, 0, GL_RGB, GL_UNSIGNED_BYTE, image_data)
        glGenerateMipmap(GL_TEXTURE_2D)

class Object:
    name: str
    n_vertices: int
    list_vertices: np.array
    list_texture: np.array
    vertices: np.array
    texture: np.array
    start: int
    number: int

    def __init__(self, name, number):
        self.name = name
        self.texture = []
        self.vertices = []
        self.list_vertices = []
        self.list_texture = []
        self.number = number


    def __str__(self):
        return f'Object: {self.name}'

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

    def init_obj(self, texture_id: int):
        modelo = ObjHelper.read_file(f'resources/{self.name}.obj')

        ### inserindo vertices do modelo no vetor de vertices
        logger.info(f'Processando modelo {self.name}')
        for face in modelo['faces']:
            for vertice_id in face[0]:
                self.list_vertices.append( modelo['vertices'][vertice_id-1] )
            for texture_id in face[1]:
                self.list_texture.append( modelo['texture'][texture_id-1] )

        self.n_vertices = len(self.list_vertices)
        ### inserindo coordenadas de textura do modelo no vetor de texturas
        ObjHelper.load_texture_from_file(texture_id, f'resources/{self.name}.jpg')

        self.init_vertices(self.list_vertices)
        self.init_texture(self.list_texture)
        logger.info(f'Texture ID: {texture_id}, ')

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

        mat_translation = np.array([  1.0, 0.0, 0.0, -px, 
                                    0.0, 1.0, 0.0, -py, 
                                    0.0, 0.0, 1.0, -pz, 
                                    0.0, 0.0, 0.0, 1.0], np.float32)

        print(mat_translation)
        
        return mat_translation

    def draw_obj(self):
        glBindTexture(GL_TEXTURE_2D, self.number)
        glDrawArrays(GL_TRIANGLES, self.start, self.n_vertices) ## renderizando



class Environment:
    window: None
    program: None
    loc: None
    texture_loc: None
    buffer: None
    total_vertices: int
    n_objects: int
    obj_list: list[Object]
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
        self.window = glfw.create_window(1600, 1200, "Trabalho 1", None, None)
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
        qtd_texturas = 10
        textures = glGenTextures(qtd_texturas)

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

    def add_object(self, obj: Object):
        obj.start = self.total_vertices

        # for i in obj.vertices:
        #     self.list_vertices.append(i) 

        # if obj.texture is not None:
        #     for i in obj.texture:
        #         self.list_texture.append(i)

        self.obj_list.append(obj)
        self.n_objects += 1

        self.send_obj_vertices(obj)
        self.send_obj_texture(obj)

    def send_obj_vertices(self, obj: Object):
        self.total_vertices += obj.n_vertices
        vertices = obj.vertices

        glBufferData(GL_ARRAY_BUFFER, vertices.nbytes, vertices, GL_STATIC_DRAW)
        glBindBuffer(GL_ARRAY_BUFFER, self.buffer[0])
        stride = vertices.strides[0]

        loc = self.get_loc()
        glEnableVertexAttribArray(loc)
        glVertexAttribPointer(loc, 3, GL_FLOAT, False, stride, offset)

    def send_obj_texture(self, obj: Object):
        texture = obj.texture
        if len(texture) == 0:
            logger.info('No texture list!')
            return

        glBindBuffer(GL_ARRAY_BUFFER, self.buffer[1])
        glBufferData(GL_ARRAY_BUFFER, texture.nbytes, texture, GL_STATIC_DRAW)
        stride = texture.strides[0]    

        texture_loc = self.get_texture_loc()
        glEnableVertexAttribArray(texture_loc)
        glVertexAttribPointer(texture_loc, 2, GL_FLOAT, False, stride, offset)


def key_event(window,key,scancode,action,mods):
    global x_inc, y_inc, r_inc, s_inc, object_selection
    
    if key == 263: x_inc -= 0.0001
    if key == 262: x_inc += 0.0001

    if key == 265: y_inc += 0.0001
    if key == 264: y_inc -= 0.0001
        
    if key == 65: r_inc += 0.1
    if key == 83: r_inc -= 0.1
        
    if key == 90: s_inc += 0.1
    if key == 88: s_inc -= 0.1

    # if key == 48: object_selection = 0
    if key == 49: object_selection = 1
    if key == 50: object_selection = 2
    
    info_message = f"Pressed key: {key}"
    logging.info(info_message)


env = Environment()
env.set_key_callback(key_event)
window = env.get_window()

# logger.info(f'{triangle.start}, {triangle.n_vertices}')

basset = Object('basset', 0)
basset.init_obj(0)
env.add_object(basset)
basset.draw_obj()

box = Object('caixa', 1)
box.init_obj(1)
env.add_object(box)
box.draw_obj()

env.show_window()
center_basset_mat = basset.center_obj()
glUniformMatrix4fv(env.loc, 1, GL_FALSE, center_basset_mat)
basset.draw_obj()
logger.info(f'{basset.start}, {basset.n_vertices}')


# env.send_vertices()
# env.send_texture()

# translacao
x_inc = 0.0
y_inc = 0.0

# rotacao
r_inc = 0.0

# coeficiente de escala
s_inc = 1.0


t_x = 0.0
t_y = 0.0
t_z = 0.0
angulo = 0.0
s_x = 1.0
s_y = 1.0

object_selection = 1

def multiplica_matriz(a,b):
    m_a = a.reshape(4,4)
    m_b = b.reshape(4,4)
    m_c = np.dot(m_a,m_b)
    c = m_c.reshape(1,16)
    return c

while not glfw.window_should_close(env.window):

    t_x += x_inc
    t_y += y_inc
    t_z += x_inc
    angulo += r_inc
    
    s_x = s_inc
    s_y = s_inc
        
    c = math.cos( math.radians(angulo) )
    s = math.sin( math.radians(angulo) )
    

    glfw.poll_events() 

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    
    glClearColor(1.0, 1.0, 1.0, 1.0)
    
    if polygonal_mode==True:
        glPolygonMode(GL_FRONT_AND_BACK,GL_LINE)
    if polygonal_mode==False:
        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL)

    
    #Draw Triangle
    
    x_axis_rotation = np.array([  c  , -s , 0.0, 0.0, 
                               s  , c  , 0.0, 0.0, 
                               0.0, 0.0, 1.0, 0.0, 
                               0.0, 0.0, 0.0, 1.0], np.float32)

    y_axis_rotation = np.array([  c  , 0.0, s, 0.0, 
                               0  , 1  , 0.0, 0.0, 
                               -s, 0.0, c, 0.0, 
                               0.0, 0.0, 0.0, 1.0], np.float32)

    z_axis_rotation = np.array([ 1.0  , 0.0, 0.0, 0.0, 
                               0  , c  , -s, 0.0, 
                               0, s, c, 0.0, 
                               0.0, 0.0, 0.0, 1.0], np.float32)
    
    mat_scale =    np.array([  s_x  , 0.0 , 0.0, 0.0, 
                               0.0  , s_y  , 0.0, 0.0, 
                               0.0, 0.0, 1.0, 0.0, 
                               0.0, 0.0, 0.0, 1.0], np.float32)
    
    mat_translation = np.array([  1.0, 0.0, 0.0, 1, 
                                  0.0, 1.0, 0.0, 1, 
                                  0.0, 0.0, 1.0, 1, 
                                  0.0, 0.0, 0.0, 1.0], np.float32)

    mat_transform = multiplica_matriz(mat_translation,x_axis_rotation)
    mat_transform = multiplica_matriz(mat_transform,y_axis_rotation)
    mat_transform = multiplica_matriz(mat_transform,z_axis_rotation)
    mat_transform = multiplica_matriz(mat_transform,mat_scale)

    list_obj = env.get_list_objects()

    # loc = glGetUniformLocation(program, "mat")
    # glUniformMatrix4fv(env.loc, 1, GL_TRUE, x_axis_rotation)
    # glDrawArrays(GL_TRIANGLES, basset.start, basset.n_vertices)

    
    try:
        obj_to_render = list_obj[object_selection-1]
        other_objects = [obj for obj in list_obj if obj != obj_to_render]

        # Render current object
        loc = env.get_loc()
        glUniformMatrix4fv(loc, 1, GL_FALSE, mat_transform)
        obj_to_render.draw_obj()
        # glDrawArrays(GL_TRIANGLES, obj_to_render.start, obj_to_render.n_vertices)

        # Render other objects
        # for obj in other_objects:
        #     # loc = glGetUniformLocation(program, "mat")
        #     glUniformMatrix4fv(env.loc, 1, GL_TRUE, x_axis_rotation)
        #     glDrawArrays(GL_TRIANGLES, obj.start, obj.n_vertices)

    except IndexError:
        logger.error(f'There are only {len(list_obj)} objects!')


    glfw.swap_buffers(env.window)

glfw.terminate()