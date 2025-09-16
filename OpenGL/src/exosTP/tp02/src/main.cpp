#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "tp02/config.hpp"


void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

GLFWwindow* handleWindow()
{
    // Create a graphic window
    GLFWwindow* window = glfwCreateWindow(800, 600, "Rectangle!", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // Instanciate GLAD function pointer manager
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Set the size of the window for rendering
    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, 
        [](GLFWwindow* window, int width, int height)
        {
            glViewport(0, 0, width, height);
        }
    );

    return window;
}

unsigned handleShader(std::string filename, int layer, int shader_type)
{
    // Récupération du shader
    std::string shader_code;
    std::ifstream shader_file;

    const char * path = std::string(_resources_directory).append(filename).c_str();
    shader_file.open(path);

    // Lecture du fichier
    std::stringsteam iss;
    iss << shader_file.rdbuf()
    shader_file.close()
    shader_code = iss.str()

    const char* shaderSource = shader_code.c_str();

    // Compilation du shader
    unsigned shader;
    shader = glCreateShader(shader_type);

    glShaderSource(shader, layer, &shaderSource, NULL);
    glCompileShader(shader);

    // Vérifier l'état de la compilation du shader
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::"
                << (shader_type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT")  // TODO: handle other cases
                << "::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    return shader;
}

unsigned handleProgram(const std::vector<unsigned>& shaders)
{
    unsigned shaderProgram = glCreateProgram();
    
    for (unsigned shader : shaders)
        glAttachShader(shaderProgram, shader);
    
    glLinkProgram(shaderProgram);

    // Vérifier l'état de la compilation du programme
    int success;
    char infoLog[512];    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    return shaderProgram;
}

void handleTermination(const std::vector<unsigned>& shaders)
{
    for (unsigned shader : shaders)
        glDeleteShader(shader);
    
    glfwTerminate();
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////


int main() {
    // ça part de là !
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow* window = handleWindow();

    std::vector<float> vertices = {
    // position            // colors
    -0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 0.0f,
    0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 0.0f,
    0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 0.0f,
    0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,   0.0f, 1.0f, 0.0f,
    0.5f, -0.5f,  0.5f,   0.0f, 1.0f, 0.0f,
    0.5f,  0.5f,  0.5f,   0.0f, 1.0f, 0.0f,
    0.5f,  0.5f,  0.5f,   0.0f, 1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,   0.0f, 1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,   0.0f, 1.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,   0.0f, 0.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,   0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,   0.0f, 0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,   0.0f, 0.0f, 1.0f,

    0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 0.0f,
    0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 0.0f,
    0.5f, -0.5f, -0.5f,   1.0f, 1.0f, 0.0f,
    0.5f, -0.5f, -0.5f,   1.0f, 1.0f, 0.0f,
    0.5f, -0.5f,  0.5f,   1.0f, 1.0f, 0.0f,
    0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 1.0f,
    0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 1.0f,
    0.5f, -0.5f,  0.5f,   0.0f, 1.0f, 1.0f,
    0.5f, -0.5f,  0.5f,   0.0f, 1.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,   0.0f, 1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 1.0f,
    0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 1.0f,
    0.5f,  0.5f,  0.5f,   1.0f, 0.0f, 1.0f,
    0.5f,  0.5f,  0.5f,   1.0f, 0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,   1.0f, 0.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 1.0f
    };

    // vertices.data()

    unsigned VBO;
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    unsigned vertexShader = handleShader("shader/vertexShader.vert", 1, GL_VERTEX_SHADER);
    unsigned fragmentShader = handleShader("shader/fragmentShader.frag", 1, GL_FRAGMENT_SHADER);

    std::vector<unsigned> shaders = {vertexShader, fragmentShader};
    unsigned shaderProgram = handleProgram(shaders);

    glUseProgram(shaderProgram);

    // Render loop
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        // Rendering


        // Final steps
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    handleTermination();
    return 0;
}
