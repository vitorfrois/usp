/* para linux, instalar os pacotes libglfw3-dev mesa-common-dev libglew-dev */
/* para compilar no linux: gcc main.c -lglfw -lGL -lGLEW -lm */

/* para windows, instalar bibliotecas compiladas do glfw3 e glew no ambiente mingw */
/* para compilar no windows: gcc main.c -lglfw3dll -lglew32 -lopengl32 */


#include <GL/glew.h>  

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h> /* verifique no seu SO onde fica o glfw3.h */
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>

 

// variaveis globais
typedef struct{
    float x, y;
} coordenadas;

float t_x = 0.0f; 
float t_y = 0.0f;
float angulo = 0.0f;

float t_x_inc = 0.0f; 
float t_y_inc = 0.0f;
float angulo_inc = 0.0f;

float c = 1.0f; // armazenar cosseno (da matriz de rotacao)
float s = 0.0f; // armazenar seno  (da matriz de rotcao)
 
// armazena o tamanho da nave
float size = 1.0f;

bool projetile = false;
bool lastProjetile = false;
float p_x = 0.0f;
float p_y = 0.0f;

 
// funcao para processar eventos de teclado
static void key_event(GLFWwindow* window, int key, int scancode, int action, int mods){
    printf("Pressionando tecla %d\n", key);

    if(key==262) t_x_inc += 0.001; // tecla para direita
    if(key==263) t_x_inc -= 0.001; // tecla para esquerda

    if(key==265) t_y_inc += 0.001; // tecla para cima
    if(key==264) t_y_inc -= 0.001; // tecla para baixo

    if(key==65) angulo_inc += 0.1; // tecla a
    if(key==83) angulo_inc -= 0.1; // tecla s

    if(key==68) size -= 0.1; //tecla d
    if(key==70) size += 0.1; //tecla f

    if(key==32) projetile = true;


}

// funcao para multiplicar duas "matrizes 4x4" (na realidade sao vetores de 16 elementos)
void multiplica(float *m1, float *m2, float *m_resultado){

    // OpenGL lida recebe vetores de 16 elementos e interpreta como matrizes 4x4.
    // Nessa funcao, transformamos as matrizes de volta para float[4][4] para facilitar a multiplicacao

    float m_a[4][4];
    float m_b[4][4];
    float m_c[4][4]; // m_c = m_a * m_b

    int n = 0;
    for(int i=0; i < 4; i++){
        for(int j=0; j < 4; j++){
            m_a[i][j] = m1[n];
            m_b[i][j] = m2[n];
            n += 1;
        }
    }


    for(int i=0;i<4;i++){    
        for(int j=0;j<4;j++){
            m_c[i][j]=0.0;
            for(int k=0; k < 4; k++){
                m_c[i][j] += m_a[i][k]*m_b[k][j];    
            }
        }
    }

    // voltando a resposta para o formato do OpenGL
    n = 0;
    for(int i=0; i < 4; i++){
        for(int j=0; j < 4; j++){
            m_resultado[n] = m_c[i][j];
            printf("%f \t",m_c[i][j]);
            n += 1;
        }
        printf("\n");
    }
    printf("-----------------------------------\n");


}


void create_projetile(){

}
 
int main(void){
 
    // inicicializando o sistema de\ janelas
    glfwInit();

    // deixando a janela invisivel, por enquanto
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

 
    // criando uma janela
    GLFWwindow* window = glfwCreateWindow(800, 800, "Minha Janela", NULL, NULL);

    
    // tornando a janela como principal 
    glfwMakeContextCurrent(window);

    // inicializando Glew (para lidar com funcoes OpenGL)
    GLint GlewInitResult = glewInit();
    printf("GlewStatus: %s", glewGetErrorString(GlewInitResult));


    // GLSL para Vertex Shader
    char* vertex_code =
    "attribute vec2 position;\n"
    "uniform mat4 mat_transformation;\n"
    "void main()\n"
    "{\n"
    "    gl_Position = mat_transformation * vec4(position, 0.0, 1.0);\n"
    "}\n";

    // GLSL para Fragment Shader
    char* fragment_code =
    "uniform vec4 color;\n"
    "void main()\n"
    "{\n"
    "    gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);\n"
    "}\n";

    // Requisitando slot para a GPU para nossos programas Vertex e Fragment Shaders
    GLuint program = glCreateProgram();
    GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

    // Associando nosso código-fonte GLSL aos slots solicitados
    glShaderSource(vertex, 1, &vertex_code, NULL);
    glShaderSource(fragment, 1, &fragment_code, NULL);

    // Compilando o Vertex Shader e verificando erros
    glCompileShader(vertex);

    GLint isCompiled = 0;
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &isCompiled);
    if(isCompiled == GL_FALSE){

        //descobrindo o tamanho do log de erro
        int infoLength = 512;
        glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &infoLength);

        //recuperando o log de erro e imprimindo na tela
        char info[infoLength];
        glGetShaderInfoLog(vertex, infoLength, NULL, info);

        printf("Erro de compilacao no Vertex Shader.\n");
        printf("--> %s\n",&info);

    }

    

    // Compilando o Fragment Shader e verificando erros
    glCompileShader(fragment);

    isCompiled = 0;
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &isCompiled);
    if(isCompiled == GL_FALSE){

        //descobrindo o tamanho do log de erro
        int infoLength = 512;
        glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &infoLength);

        //recuperando o log de erro e imprimindo na tela
        char info[infoLength];
        glGetShaderInfoLog(fragment, infoLength, NULL, info);

        printf("Erro de compilacao no Fragment Shader.\n");
        printf("--> %s\n",&info);

    }

    // Associando os programas compilado ao programa principal
    glAttachShader(program, vertex);
    glAttachShader(program, fragment);

    // Linkagem do programa e definindo como default
    glLinkProgram(program);
    glUseProgram(program);
 

    // Preparando dados para enviar a GPU
    coordenadas vertices[6] = { // criando tres vertices e preenchendo
        {  0.00f, +0.05f },
        { -0.05f, -0.05f },
        { +0.05f, -0.05f },
        {  0.00f, +0.05f },
        { -0.05f, -0.05f },
        { +0.05f, -0.05f },
    };


    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);


    // Abaixo, nós enviamos todo o conteúdo da variável vertices.
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);


    // Associando variáveis do programa GLSL (Vertex Shaders) com nossos dados
    GLint loc = glGetAttribLocation(program, "position");
    glEnableVertexAttribArray(loc);
    glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), (void*) 0); // https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glVertexAttribPointer.xhtml
 

    // Associando nossa janela com eventos de teclado
    glfwSetKeyCallback(window, key_event); // teclado


    // Exibindo nossa janela
    glfwShowWindow(window);

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(1.0, 1.0, 1.0, 1.0);


        // acumulando incrementos
        t_x += t_x_inc;
        t_y += t_y_inc;

        // permite ao ponto passar para o outro lado
        if(t_x > 1 | t_x < -1) t_x *= -1;
        if(t_y > 1 | t_y < -1) t_y *= -1;

        angulo += angulo_inc;

        // definindo a matriz de translacao (na realidade eh um vetor, mas o OpenGl processa como matriz 4x4)
        float mat_translation[16] = {
            1.0f, 0.0f, 0.0f, t_x ,
            0.0f, 1.0f, 0.0f, t_y ,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        };

        // definindo a matriz de rotacao (na realidade eh um vetor, mas o OpenGl processa como matriz 4x4)
        c = cos( ((angulo) * M_PI / 180.0) ); // cos considerando conversao para radianos
        s = sin( ((angulo) * M_PI / 180.0) );

        float mat_rotation[16] = {
            c   , -s  , 0.0f, 0.0f,
            s   ,  c  , 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        };

        float mat_scale[16] = {
            size, 0.0f, 0.0f, 0.0f,
            0.0f, size, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        };

        float mat_transformation[16] = {
            0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f
        };

        float mat_projetile[16] = {
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        };



        multiplica(mat_translation, mat_rotation, &mat_transformation);
        multiplica(mat_transformation, mat_scale, &mat_transformation);

        if(projetile == true){
            if(lastProjetile == false){
                p_x = t_x; p_y = t_y;
                for(int i = 0; i < 16; i++)
                    mat_projetile[i] = mat_transformation[i];
            } else{
                p_y += 0.05;
                float proj_translation[16] = {
                    1.0f, 0.0f, 0.0f, p_x ,
                    0.0f, 1.0f, 0.0f, p_y ,
                    0.0f, 0.0f, 1.0f, 0.0f,
                    0.0f, 0.0f, 0.0f, 1.0f
                };
                multiplica(mat_projetile, proj_translation, &mat_projetile);
                loc = glGetUniformLocation(program, "mat_transformation");
                glUniformMatrix4fv(loc, 1, GL_TRUE, mat_projetile);
                glDrawArrays(GL_TRIANGLES, 3, 3);
            }

            if(p_y > 1) projetile = false;
        } 



        // enviando a matriz de transformacao para a GPU
        loc = glGetUniformLocation(program, "mat_transformation");
        glUniformMatrix4fv(loc, 1, GL_TRUE, mat_transformation);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        


 
        glfwSwapBuffers(window);
        
        lastProjetile = projetile;
    }
 
    glfwDestroyWindow(window);
 
    glfwTerminate();
    exit(EXIT_SUCCESS);
}
