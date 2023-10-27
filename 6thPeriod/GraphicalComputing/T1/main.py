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

vertex_code = """
        attribute vec2 position;
        uniform mat4 mat;
        void main(){
            gl_Position = mat * vec4(position,0.0,1.0);
        }
        """

fragment_code = """
        void main(){
            gl_FragColor = vec4(0.0,1.0,0.0,1.0);
        }
        """

object_selection = 0

mat_identidade = np.array([  1.0, 0.0, 0.0, 0.0, 
                                  0.0, 1.0, 0.0, 0.0, 
                                  0.0, 0.0, 1.0, 0.0, 
                                  0.0, 0.0, 0.0, 1.0], np.float32)


glEnable(GL_TEXTURE_2D)
qtd_texturas = 10
textures = glGenTextures(qtd_texturas)


vertices_list = []    
textures_coord_list = []

modelo = load_model_from_obj_file('resources/basset.obj')

### inserindo vertices do modelo no vetor de vertices
print('Processando modelo cube.obj. Vertice inicial:',len(vertices_list))
for face in modelo['faces']:
    for vertice_id in face[0]:
        vertices_list.append( modelo['vertices'][vertice_id-1] )
    for texture_id in face[1]:
        textures_coord_list.append( modelo['texture'][texture_id-1] )
print('Processando modelo cube.obj. Vertice final:',len(vertices_list))

### inserindo coordenadas de textura do modelo no vetor de texturas
load_texture_from_file(0,'resources/basset.jpg')


### carregando textura equivalente e definindo um id (buffer): use um id por textura!




class Object:
    name: str
    start_vertice: int
    n_vertices: int
    vertices: np.array
    texture: np.array

    def __init__(self, loc, list_vertices, name, list_texture = None):
        self.name = name
        self.n_vertices = len(list_vertices)
        self.vertices = list_vertices
        self.texture = list_texture

    @staticmethod
    def load_model_from_obj_file(filename: str):
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

        
        print('Processando modelo cube.obj. Vertice inicial:',len(vertices_list))
        for face in modelo['faces']:
            for vertice_id in face[0]:
                vertices_list.append( modelo['vertices'][vertice_id-1] )
            for texture_id in face[1]:
                textures_coord_list.append( modelo['texture'][texture_id-1] )
        print('Processando modelo cube.obj. Vertice final:',len(vertices_list))

        return model

    @staticmethod
    def load_texture_from_file(texture_id, img_textura):
        glBindTexture(GL_TEXTURE_2D, texture_id)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR)
        img = Image.open(img_textura)
        img_width = img.size[0]
        img_height = img.size[1]
        image_data = img.tobytes("raw", "RGB", 0, -1)
        #image_data = np.array(list(img.getdata()), np.uint8)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img_width, img_height, 0, GL_RGB, GL_UNSIGNED_BYTE, image_data)

    def load_vertices():

    def __str__(self):
        return f'Object: {self.name}'



class Environment:
    window: None
    program: None
    loc: None
    buffer: None
    total_vertices: int
    n_objects: int
    obj_list: dict[str, Object]
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
        window = glfw.create_window(800, 800, "Trabalho 1", None, None)
        glfw.make_context_current(window)

        # Request a program and shader slots from GPU
        program  = glCreateProgram()
        vertex   = glCreateShader(GL_VERTEX_SHADER)
        fragment = glCreateShader(GL_FRAGMENT_SHADER)

        # Set shaders source
        glShaderSource(vertex, vertex_code)
        glShaderSource(fragment, fragment_code)

        self.compile_shader(vertex)
        self.compile_shader(fragment)

        # Attach shader objects to the program
        glAttachShader(program, vertex)
        glAttachShader(program, fragment)

        # Build program
        glLinkProgram(program)
        if not glGetProgramiv(program, GL_LINK_STATUS):
            print(glGetProgramInfoLog(program))
            raise RuntimeError('Linking error')

        # Make program the default program
        glUseProgram(program)

        # Request a buffer slot from GPU
        self.buffer = glGenBuffers(2)
        # Make this buffer the default one
        glBindBuffer(GL_ARRAY_BUFFER, self.buffer[0])

        loc = glGetAttribLocation(program, "position")
        glEnableVertexAttribArray(loc)

        self.window = window
        self.program = program
        self.loc = loc

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
        try:
            self.obj_list[obj.name] = obj
        except KeyError:
            logger.error(f'There is already an object named {obj.name}')
            return 
            
        for i in obj.vertices:
            self.list_vertices.append(i) 

        if obj.texture is not None:
            for i in obj.texture:
                self.list_texture.append(i)
        
        self.total_vertices += obj.n_vertices
        self.n_objects += 1

    def send_object_vertices(self, obj: Object):
        list_vertices = obj.vertices

        vertices = np.zeros(obj.n_vertices, [("position", np.float32, 3)])
        vertices['position'] = list_vertices
        stride = vertices.strides[0]
        loc = glGetAttribLocation(self.program, obj.name)

        glVertexAttribPointer(loc, 3, GL_FLOAT, False, stride, offset)
        glBufferData(GL_ARRAY_BUFFER, vertices.nbytes, vertices, GL_DYNAMIC_DRAW)
        glBindBuffer(GL_ARRAY_BUFFER, self.buffer[0])

    def send_texture(self):
        list_texture = self.get_texture()

        texture = np.zeros(len(list_texture), [("position", np.float32, 2)])
        texture['position'] = list_texture

        glBindBuffer(GL_ARRAY_BUFFER, self.buffer[1])
        glBufferData(GL_ARRAY_BUFFER, texture.nbytes, texture, GL_STATIC_DRAW)
        stride = texture.strides[0]    

        loc_texture_coord = glGetAttribLocation(self.program, "texture_coord")
        glEnableVertexAttribArray(loc_texture_coord)
        glVertexAttribPointer(loc_texture_coord, 2, GL_FLOAT, False, stride, offset)


    def send_texture(self):
        list_texture = self.get_texture()

        texture = np.zeros(len(list_texture), [("position", np.float32, 2)])
        texture['position'] = list_texture

        glBindBuffer(GL_ARRAY_BUFFER, self.buffer[1])
        glBufferData(GL_ARRAY_BUFFER, texture.nbytes, texture, GL_STATIC_DRAW)
        stride = texture.strides[0]    

        loc_texture_coord = glGetAttribLocation(self.program, "texture_coord")
        glEnableVertexAttribArray(loc_texture_coord)
        glVertexAttribPointer(loc_texture_coord, 2, GL_FLOAT, False, stride, offset)



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

    if key == 48: object_selection = 0
    if key == 49: object_selection = 1
    if key == 50: object_selection = 2
    
    info_message = f"Pressed key: {key}"
    logging.info(info_message)

env = Environment()
env.set_key_callback(key_event)
env.show_window()
window = env.get_window()
loc = env.get_loc()
program = env.get_program()


list_vertices = [
    ( 0.05, +0.05, 0.05), 
    (-0.05, -0.05, 0.01), 
    (+0.00, -0.05, -0.01)
]
env.add_object(Object(loc, list_vertices, 'triangle'))
env.add_object(Object(loc, vertices_list, 'basset', textures_coord_list))

env.send_vertices()
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
angulo = 0.0
s_x = 1.0
s_y = 1.0

object_selection = 0

def multiplica_matriz(a,b):
    m_a = a.reshape(4,4)
    m_b = b.reshape(4,4)
    m_c = np.dot(m_a,m_b)
    c = m_c.reshape(1,16)
    return c


loc = glGetUniformLocation(program, "mat")
glUniformMatrix4fv(loc, 1, GL_TRUE, mat_identidade)


while not glfw.window_should_close(window):

    t_x += x_inc
    t_y += y_inc
    angulo += r_inc
    
    s_x = s_inc
    s_y = s_inc
    
    c = math.cos( math.radians(angulo) )
    s = math.sin( math.radians(angulo) )
    

    glfw.poll_events() 

    
    glClear(GL_COLOR_BUFFER_BIT) 
    glClearColor(1.0, 1.0, 1.0, 1.0)
    
    
    #Draw Triangle
    
    mat_rotation = np.array([  c  , -s , 0.0, 0.0, 
                               s  , c  , 0.0, 0.0, 
                               0.0, 0.0, 1.0, 0.0, 
                               0.0, 0.0, 0.0, 1.0], np.float32)

    mat_rotation2 = np.array([  c  , 0.0, s, 0.0, 
                               0  , 1  , 0.0, 0.0, 
                               -s, 0.0, c, 0.0, 
                               0.0, 0.0, 0.0, 1.0], np.float32)
    
    mat_scale =    np.array([  s_x  , 0.0 , 0.0, 0.0, 
                               0.0  , s_y  , 0.0, 0.0, 
                               0.0, 0.0, 1.0, 0.0, 
                               0.0, 0.0, 0.0, 1.0], np.float32)
    
    mat_translation = np.array([  1.0, 0.0, 0.0, t_x, 
                                  0.0, 1.0, 0.0, t_y, 
                                  0.0, 0.0, 1.0, 0.0, 
                                  0.0, 0.0, 0.0, 1.0], np.float32)

    
    
    
    #print(mat_rotation,"\n\n")

    mat_transform = multiplica_matriz(mat_translation,mat_rotation2)
    mat_transform = multiplica_matriz(mat_transform,mat_scale)

    list_obj = env.get_list_objects()

    try:
        obj_to_render = list_obj[object_selection-1]
        other_objects = [obj for obj in list_obj if obj != obj_to_render]
        print(object_selection)
        print(obj_to_render.obj)

        # Render current object
        loc = glGetUniformLocation(program, "mat")
        glUniformMatrix4fv(loc, 1, GL_TRUE, mat_transform)
        glDrawArrays(GL_TRIANGLES, obj_to_render.start, obj_to_render.n_vertices)

        # Render other objects
        for obj in other_objects:
            loc = glGetUniformLocation(program, "mat")
            glUniformMatrix4fv(loc, 1, GL_TRUE, mat_rotation)
            glDrawArrays(GL_TRIANGLES, obj.start, obj.n_vertices)

    except IndexError:
        logger.error(f'There are only {len(list_obj)} objects!')


    glfw.swap_buffers(window)

glfw.terminate()